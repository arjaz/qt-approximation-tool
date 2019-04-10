#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
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
    for (auto i : this->realFunc) {

    }

    for (int i = 0; i < 10; ++i) {
        std::cout << getLagrangePolynomial(0, i)(0.25) << std::endl;
    }
    return 0;
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
    this->realFunc = generateFunc(0, 1);
    setFuncText(this->realFunc);

    double resPol = interpolate(ui->doubleSpinBoxPol->value());
    QString res = "value for [" + QString::number(ui->doubleSpinBoxPol->value(), 'f', 3) + "] is [" + QString::number(resPol, 'f', 3) + "]";

    ui->label_polynomial_f->setText(res);
}
