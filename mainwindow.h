#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;
    std::vector<std::pair<double, double>> realFunc;
    std::vector<std::pair<double, double>> generateFunc(double, double);
    void setSpinBoxBoundaries(double, double);
    void setFuncText(std::vector<std::pair<double, double>>);
    double interpolate(double);
    std::function<double(double)> getLagrangePolynomial(size_t, size_t);
};

#endif // MAINWINDOW_H
