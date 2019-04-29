#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cmath>
#include <functional>
#include <vector>
#include <utility>
#include <exception>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    func = [](double x) {
        return cos(x) * cos(x);
    };
}

MainWindow::~MainWindow() {
    delete ui;
}

// Generates a vector of <double, double> pairs using the provided function with x within the range
std::vector<std::pair<double, double>> MainWindow::generateFunction(std::function<double(double)> function, std::pair<double, double> range) {
    if (range.first > range.second) {
        throw std::invalid_argument("range.first must not be greater than range.second");
    }

    auto [from, to] = range;
    std::vector<std::pair<double, double>> funcVec;

    for (double i = from; i <= to; i += (to - from) / (ui->spinBoxApproxIntervals->value())) {
        funcVec.push_back(std::make_pair(i, function(i)));
    }

    return funcVec;
}

// Returns an interpolated value for x
// TODO: caching
double MainWindow::interpolate(double x) {
    if (x <= functionValues.front().first) {
        return functionValues.front().second;
    }
    if (x >= functionValues.back().first) {
        return functionValues.back().second;
    }

    std::vector<double> xs;
    std::transform(functionValues.begin(), functionValues.end(), std::back_inserter(xs),
        [](const std::pair<double, double> &p) {
            return p.first;
        }
    );

    size_t fromPol;
    size_t toPol;

    fromPol = std::distance(xs.begin(), std::upper_bound(xs.begin(), xs.end(), x)) - 1;
    toPol = fromPol + 1;

    double result = 0;

    double oldPolynomial = functionValues.at(fromPol).second;
    double curPolynomial = getLagrangePolynomial(std::make_pair(fromPol, toPol))(x);

    double curDistance = abs(curPolynomial - oldPolynomial);
    double oldDistance = curDistance + 1;

    while (oldDistance > curDistance && toPol <= functionValues.size() - 1) {
        oldPolynomial = curPolynomial;
        curPolynomial = getLagrangePolynomial(std::make_pair(fromPol, toPol))(x);

        oldDistance = curDistance;
        curDistance = abs(curPolynomial - oldPolynomial);

        result = curPolynomial;
        ++toPol;
    }

    return result;
}

// Returns Lagrange Polynomial function between points i and j within the range using values stored in functionValues
// TODO: checking functionValues vector's changes withoup copying
std::function<double(double)> MainWindow::getLagrangePolynomial(std::pair<size_t, size_t> range) {
    if (range.first > range.second) {
        throw std::invalid_argument("range.first must not be greater than range.second");
    }
    static std::map<std::pair<size_t, size_t>, std::function<double(double)>> cache;
    if (!isLagrangeCacheValid) {
        isLagrangeCacheValid = true;
        cache.clear();
    }
    if (cache.count(range) != 0) {
        return cache.at(range);
    }
    auto [i, j] = range;
    auto const &func = functionValues;
    if (i == j) {
        auto result = [=](double) {
            return func.at(i).second;
        };
        cache[range] = result;
        return result;
    } else {
        auto result = [=](double x) {
            return 1.0 / (func.at(j).first - func.at(i).first) * ((x - func.at(i).first) * getLagrangePolynomial(std::make_pair(i + 1, j))(x) - (x - func.at(j).first) * getLagrangePolynomial(std::make_pair(i, j - 1))(x));
        };
        cache[range] = result;
        return result;
    }
}

void MainWindow::on_pushButton_polynomial_clicked(){
    if (ui->doubleSpinBoxMinRange->value() == ui->doubleSpinBoxMaxRange->value()) {
        ui->doubleSpinBoxMaxRange->setValue(ui->doubleSpinBoxMinRange->value() + 1);
    }
    auto range = std::make_pair(ui->doubleSpinBoxMinRange->value(), ui->doubleSpinBoxMaxRange->value());

    functionValues = generateFunction(func, range);
    isLagrangeCacheValid = false;

    ui->label_real_f->setText(QString::number(func(ui->doubleSpinBoxPol->value()), 'f', 3));
    ui->label_polynomial_f->setText(QString::number(interpolate(ui->doubleSpinBoxPol->value()), 'f', 3));

    plot(range);
}

void MainWindow::plot(std::pair<double, double> range) {
    if (range.first > range.second) {
        throw std::invalid_argument("range.first must not be greater than range.second");
    }

    auto [from, to] = range;

    QLineSeries *seriesFunc = new QLineSeries(this);
    QLineSeries *seriesApprox = new QLineSeries(this);
    QLineSeries *seriesError = new QLineSeries(this);

    seriesFunc->setName("Function");
    seriesApprox->setName("Approximation");
    seriesError->setName("Error");

    for (double i = from; i <= to; i += (to - from) / 100) {
        auto f = func(i);
        auto a = interpolate(i);
        auto e = abs(f - a);
        seriesFunc->append(i, f);
        seriesApprox->append(i, a);
        seriesError->append(i, e);
    }

    QChart *chart = new QChart();
    chart->addSeries(seriesFunc);
    chart->addSeries(seriesApprox);
    chart->legend()->show();
    chart->createDefaultAxes();
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTitle("Function and its approximation");

    QChart *chartError = new QChart();
    chartError->addSeries(seriesError);
    chartError->legend()->hide();
    chartError->createDefaultAxes();
    chartError->setAnimationOptions(QChart::AllAnimations);
    chartError->setTitle("Error function");

    ui->graphicsView->setChart(chart);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    ui->graphicsViewError->setChart(chartError);
    ui->graphicsViewError->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::on_comboBox_currentIndexChanged(int index) {
    switch (index) {
        case 0:
            func = [](double x) {
                return cos(x) * cos(x);
            };
            break;
        case 1:
            func = [](double x) {
                return x * x;
            };
            break;
        case 2:
            func = [](double x) {
                return sin(x);
            };
            break;
        case 3:
            func = [](double x) {
                return log(x);
            };
            break;
        case 4:
            func = [](double x) {
                return x * sin(x);
            };
            break;
        case 5:
            func = [](double x) {
                return exp(x);
            };
            break;
        case 6:
            func = [](double x) {
                return exp(x) / x;
            };
            break;
        case 7:
            func = [](double x) {
                return 2 * log10(x) - x / 2 + 1;
            };
            break;
        default:
            func = [](double x) {
                return cos(x) * cos(x);
            };
    }
    isLagrangeCacheValid = false;
}

void MainWindow::on_doubleSpinBoxMaxRange_valueChanged(double arg1) {
    ui->doubleSpinBoxMinRange->setMaximum(arg1);
    ui->doubleSpinBoxPol->setMaximum(arg1);
}

void MainWindow::on_doubleSpinBoxMinRange_valueChanged(double arg1) {
    ui->doubleSpinBoxMaxRange->setMinimum(arg1);
    ui->doubleSpinBoxPol->setMinimum(arg1);
}
