#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <utility>
#include <vector>
#include <functional>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_polynomial_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_doubleSpinBoxMaxRange_valueChanged(double arg1);
    void on_doubleSpinBoxMinRange_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    std::function<double(double)> func;
    std::pair<double, double> range;
    std::vector<std::pair<double, double>> realFunc;
    std::vector<std::pair<double, double>> generateFunc(std::pair<double, double>);
    void plot();
    double interpolate(double);
    std::function<double(double)> getLagrangePolynomial(std::pair<size_t, size_t>);
};

#endif // MAINWINDOW_H
