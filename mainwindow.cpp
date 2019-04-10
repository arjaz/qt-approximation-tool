#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    this->realFunc = generateFunc(0, 1);
    setSpinBoxBoundaries(this->realFunc[0].first, this->realFunc.back().first);
    setFuncText(this->realFunc);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setSpinBoxBoundaries(double min, double max) {
    ui->doubleSpinBoxPol->setMinimum(min);
    ui->doubleSpinBoxPol->setMaximum(max);
}

// Generates a vector of 10 <double, double> pairs using the formula with x from min to max
std::vector<std::pair<double, double>> MainWindow::generateFunc(double min, double max) {
    double step = (max - min) / 10;
    std::vector<std::pair<double, double>> funcVec;

    for (int i = 0; i < 10; ++i) {
        funcVec.push_back(std::make_pair(min + step * i, pow(cos(min + step * i), 2)));
    }

    return funcVec;
}

// Sets the label_real_f's text to the resVec's values
void MainWindow::setFuncText(std::vector<std::pair<double, double>> resVec) {
    QString res = "";
    for (size_t i = 0; i < 10; ++i) {
        res += "[" + QString::number(resVec[i].first, 'f', 3) + ", " + QString::number(resVec[i].second, 'f', 3) + "], ";
    }

    ui->label_real_f->setText(res);
}

// Returns an interpolated value in x
double MainWindow::interpolate(double x) {
    // TODO: interpolation
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
    }
    if (i0 + 1 == i1) {
        return [=](double x) {
            return 1.0 / (func[i1].first - func[i0].first) * ((x - func[i0].first) * func[i1].second - (x - func[i1].first) * func[i0].second);
        };
    } else {
        return [=](double x) {
            return 1.0 / (func[i1].first - func[i0].first) * ((x - func[i0].first) * getLagrangePolynomial(i0 + 1, i1)(x) - (x - func[i1].first) * getLagrangePolynomial(i0, i1 - 1)(x));
        };
    }
}

void MainWindow::on_pushButton_polynomial_clicked(){

    double resPol = interpolate(ui->doubleSpinBoxPol->value());
    QString res = "value for [" + QString::number(ui->doubleSpinBoxPol->value(), 'f', 3) + "] is [" + QString::number(resPol, 'f', 3) + "]";

    ui->label_polynomial_f->setText(res);
}
