#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cmath>

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

void MainWindow::setSpinBoxBoundaries(double min, double max) {
    ui->doubleSpinBoxPol->setMinimum(min);
    ui->doubleSpinBoxPol->setMaximum(max);
}

// Generates a vector of <double, double> pairs using the formula with x from min to max
std::vector<std::pair<double, double>> MainWindow::generateFunc(double min, double max) {
    double step = (max - min) / ui->spinBoxApproxPoints->value();
    std::vector<std::pair<double, double>> funcVec;

    for (int i = 0; i < ui->spinBoxApproxPoints->value() + 1; ++i) {
        funcVec.push_back(std::make_pair(min + step * i, func(min + step * i)));
    }

    return funcVec;
}

// Returns an interpolated value for x
// TODO: caching
double MainWindow::interpolate(double x) {
    if (x <= realFunc.front().first) {
        return realFunc.front().second;
    }
    if (x >= realFunc.back().first) {
        return realFunc.back().second;
    }

    std::vector<double> xs;
    std::transform(realFunc.begin(), realFunc.end(), std::back_inserter(xs),
        [](const std::pair<double, double> &p) {
            return p.first;
        }
    );

    size_t fromPol;
    size_t toPol;

    fromPol = std::distance(xs.begin(), std::upper_bound(xs.begin(), xs.end(), x)) - 1;
    toPol = fromPol + 1;

    double result = 0;

    double oldPolynomial = realFunc.at(fromPol).second;
    double curPolynomial = getLagrangePolynomial(std::make_pair(fromPol, toPol))(x);

    double curDistance = abs(curPolynomial - oldPolynomial);
    double oldDistance = curDistance + 1;

    while (oldDistance > curDistance && toPol <= realFunc.size() - 1) {
        oldPolynomial = curPolynomial;
        curPolynomial = getLagrangePolynomial(std::make_pair(fromPol, toPol))(x);

        oldDistance = curDistance;
        curDistance = abs(curPolynomial - oldPolynomial);

        result = curPolynomial;
        ++toPol;
    }

    return result;
}

// Returns Lagrange Polynomial function between points i and j using values stored in realFunc
// TODO: checking realFunc vector's changes withoup copying
std::function<double(double)> MainWindow::getLagrangePolynomial(std::pair<size_t, size_t> range) {
    static std::map<std::pair<size_t, size_t>, std::function<double(double)>> cache;
    static auto realFuncBackup = realFunc;
    if (realFuncBackup != realFunc) {
        realFuncBackup = realFunc;
        cache.clear();
    }
    if (cache.count(range) != 0) {
        return cache.at(range);
    }
    auto [i, j] = range;
    if (i > j) {
        std::swap(i, j);
    }
    auto const &func = realFunc;
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
    range = std::make_pair(ui->doubleSpinBoxMinRange->value(), ui->doubleSpinBoxMaxRange->value());

    realFunc = generateFunc(range.first, range.second);
    setSpinBoxBoundaries(realFunc.at(0).first, realFunc.back().first);

    ui->label_real_f->setText(QString::number(func(ui->doubleSpinBoxPol->value()), 'f', 3));
    ui->label_polynomial_f->setText(QString::number(interpolate(ui->doubleSpinBoxPol->value()), 'f', 3));
    plot();
}

void MainWindow::plot() {
    QLineSeries *seriesFunc = new QLineSeries(this);
    QLineSeries *seriesApprox = new QLineSeries(this);
    QLineSeries *seriesError = new QLineSeries(this);

    seriesFunc->setName("Function");
    seriesApprox->setName("Approximation");
    seriesError->setName("Error");

    for (float i = range.first; i <= range.second; i += (range.second - range.first) / 100) {
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
}

void MainWindow::on_doubleSpinBoxMaxRange_valueChanged(double arg1) {
    ui->doubleSpinBoxMinRange->setMaximum(arg1);
    ui->doubleSpinBoxPol->setMaximum(arg1);
}

void MainWindow::on_doubleSpinBoxMinRange_valueChanged(double arg1) {
    ui->doubleSpinBoxMaxRange->setMinimum(arg1);
    ui->doubleSpinBoxPol->setMinimum(arg1);
}
