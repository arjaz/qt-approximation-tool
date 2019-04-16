/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "QtCharts"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label_real_f;
    QLabel *label_polynomial;
    QDoubleSpinBox *doubleSpinBoxMaxRange;
    QLabel *label_2;
    QSpinBox *spinBoxApproxPoints;
    QDoubleSpinBox *doubleSpinBoxPol;
    QDoubleSpinBox *doubleSpinBoxMinRange;
    QComboBox *comboBox;
    QPushButton *pushButton_polynomial;
    QLabel *label_polynomial_f;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QChartView *graphicsView;
    QChartView *graphicsViewError;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1051, 650);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_real_f = new QLabel(centralWidget);
        label_real_f->setObjectName(QString::fromUtf8("label_real_f"));

        gridLayout->addWidget(label_real_f, 1, 1, 1, 2);

        label_polynomial = new QLabel(centralWidget);
        label_polynomial->setObjectName(QString::fromUtf8("label_polynomial"));

        gridLayout->addWidget(label_polynomial, 2, 0, 1, 1);

        doubleSpinBoxMaxRange = new QDoubleSpinBox(centralWidget);
        doubleSpinBoxMaxRange->setObjectName(QString::fromUtf8("doubleSpinBoxMaxRange"));
        doubleSpinBoxMaxRange->setMaximum(25.000000000000000);
        doubleSpinBoxMaxRange->setValue(1.000000000000000);

        gridLayout->addWidget(doubleSpinBoxMaxRange, 4, 2, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        spinBoxApproxPoints = new QSpinBox(centralWidget);
        spinBoxApproxPoints->setObjectName(QString::fromUtf8("spinBoxApproxPoints"));
        spinBoxApproxPoints->setMinimum(1);
        spinBoxApproxPoints->setMaximum(30);
        spinBoxApproxPoints->setValue(10);

        gridLayout->addWidget(spinBoxApproxPoints, 3, 1, 1, 2);

        doubleSpinBoxPol = new QDoubleSpinBox(centralWidget);
        doubleSpinBoxPol->setObjectName(QString::fromUtf8("doubleSpinBoxPol"));
        doubleSpinBoxPol->setMaximum(1.000000000000000);
        doubleSpinBoxPol->setSingleStep(0.050000000000000);

        gridLayout->addWidget(doubleSpinBoxPol, 5, 1, 1, 2);

        doubleSpinBoxMinRange = new QDoubleSpinBox(centralWidget);
        doubleSpinBoxMinRange->setObjectName(QString::fromUtf8("doubleSpinBoxMinRange"));
        doubleSpinBoxMinRange->setMaximum(1.000000000000000);

        gridLayout->addWidget(doubleSpinBoxMinRange, 4, 1, 1, 1);

        comboBox = new QComboBox(centralWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 1, 0, 1, 1);

        pushButton_polynomial = new QPushButton(centralWidget);
        pushButton_polynomial->setObjectName(QString::fromUtf8("pushButton_polynomial"));

        gridLayout->addWidget(pushButton_polynomial, 5, 0, 1, 1);

        label_polynomial_f = new QLabel(centralWidget);
        label_polynomial_f->setObjectName(QString::fromUtf8("label_polynomial_f"));

        gridLayout->addWidget(label_polynomial_f, 2, 1, 1, 2);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        graphicsView = new QChartView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout_2->addWidget(graphicsView, 0, 1, 1, 1);

        graphicsViewError = new QChartView(centralWidget);
        graphicsViewError->setObjectName(QString::fromUtf8("graphicsViewError"));

        gridLayout_2->addWidget(graphicsViewError, 0, 2, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1051, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label_real_f->setText(QString());
        label_polynomial->setText(QApplication::translate("MainWindow", "Polynomial:", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Range", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindow", "cos(x)^2", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindow", "x^2", nullptr));
        comboBox->setItemText(2, QApplication::translate("MainWindow", "sin(x)", nullptr));
        comboBox->setItemText(3, QApplication::translate("MainWindow", "log(x)", nullptr));
        comboBox->setItemText(4, QApplication::translate("MainWindow", "x*sin(x)", nullptr));
        comboBox->setItemText(5, QApplication::translate("MainWindow", "exp(x)", nullptr));
        comboBox->setItemText(6, QApplication::translate("MainWindow", "exp(x) / x", nullptr));

        pushButton_polynomial->setText(QApplication::translate("MainWindow", "Approximate", nullptr));
        label_polynomial_f->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Number of points", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
