#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <iostream>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    this->func = [](double x) {
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
        funcVec.push_back(std::make_pair(min + step * i, this->func(min + step * i)));
    }

    return funcVec;
}

// Returns an interpolated value in x
double MainWindow::interpolate(double x) {
    size_t from_pol;
    size_t to_pol;

    if (x <= this->realFunc[0].first) {
        return getLagrangePolynomial(0, 0)(x);
    }
    if (x >= this->realFunc.back().first) {
        return getLagrangePolynomial(this->realFunc.size() - 1, this->realFunc.size() - 1)(x);
    }

    std::vector<double> xs(this->realFunc.size());
    std::transform(this->realFunc.begin(), this->realFunc.end(), xs.begin(), [=](std::pair<double, double> p) {
        return p.first;
    });
    from_pol = std::distance(xs.begin(), std::upper_bound(xs.begin(), xs.end(), x)) - 1;

    double result = 0;
    to_pol = from_pol + 1;

    double polynomial_prev = getLagrangePolynomial(from_pol, to_pol - 1)(x);
    double polynomial = getLagrangePolynomial(from_pol, to_pol)(x);
    double dist;

    do {
        dist = abs(polynomial - polynomial_prev);
        result = polynomial_prev;
        ++to_pol;
        polynomial_prev = polynomial;
        polynomial = getLagrangePolynomial(from_pol, to_pol)(x);
    } while (dist >= abs(polynomial - polynomial_prev) || to_pol == this->realFunc.size() - 1);

    return result;
}

// Returns Lagrange Polynomial function between points i0 and i1 using values stored in realFunc
std::function<double(double)> MainWindow::getLagrangePolynomial(size_t i0, size_t i1) {
    if (i0 > i1) {
        auto tmp = i0;
        i0 = i1;
        i1 = tmp;
    }
    auto const &func = this->realFunc;
    if (i0 == i1) {
        return [=](double) {
            return func[i0].second;
        };
    } else {
        return [=](double x) {
            return 1.0 / (func[i1].first - func[i0].first) * ((x - func[i0].first) * getLagrangePolynomial(i0 + 1, i1)(x) - (x - func[i1].first) * getLagrangePolynomial(i0, i1 - 1)(x));
        };
    }
}

void MainWindow::on_pushButton_polynomial_clicked(){
    if (ui->doubleSpinBoxMinRange->value() == ui->doubleSpinBoxMaxRange->value()) {
        ui->doubleSpinBoxMaxRange->setValue(ui->doubleSpinBoxMinRange->value() + 1);
    }
    this->range = std::make_pair(ui->doubleSpinBoxMinRange->value(), ui->doubleSpinBoxMaxRange->value());

    this->realFunc = generateFunc(this->range.first, this->range.second);
    setSpinBoxBoundaries(this->realFunc[0].first, this->realFunc.back().first);

    ui->label_real_f->setText(QString::number(this->func(ui->doubleSpinBoxPol->value()), 'f', 3));
    ui->label_polynomial_f->setText(QString::number(interpolate(ui->doubleSpinBoxPol->value()), 'f', 3));
    this->plot();
}

void MainWindow::plot() {
    QLineSeries *seriesFunc = new QLineSeries(this);
    QLineSeries *seriesApprox = new QLineSeries(this);
    QLineSeries *seriesError = new QLineSeries(this);

    seriesFunc->setName("Function");
    seriesApprox->setName("Approximation");
    seriesError->setName("Error");

    for (float i = this->range.first; i <= this->range.second; i += (this->range.second - this->range.first) / 100) {
        auto f = this->func(i);
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
            this->func = [](double x) {
                return cos(x) * cos(x);
            };
            break;
        case 1:
            this->func = [](double x) {
                return x * x;
            };
            break;
        case 2:
            this->func = [](double x) {
                return sin(x);
            };
            break;
        case 3:
            this->func = [](double x) {
                return log(x);
            };
            break;
        case 4:
            this->func = [](double x) {
                return x * sin(x);
            };
            break;
        case 5:
            this->func = [](double x) {
                return exp(x);
            };
            break;
        case 6:
            this->func = [](double x) {
                return exp(x) / x;
            };
            break;
        default:
            this->func = [](double x) {
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
