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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_real_f;
    QLabel *label_polynomial;
    QLabel *label_polynomial_f;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_polynomial;
    QDoubleSpinBox *doubleSpinBoxPol;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(581, 465);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_real_f = new QLabel(centralWidget);
        label_real_f->setObjectName(QString::fromUtf8("label_real_f"));

        gridLayout->addWidget(label_real_f, 0, 1, 1, 1);

        label_polynomial = new QLabel(centralWidget);
        label_polynomial->setObjectName(QString::fromUtf8("label_polynomial"));

        gridLayout->addWidget(label_polynomial, 1, 0, 1, 1);

        label_polynomial_f = new QLabel(centralWidget);
        label_polynomial_f->setObjectName(QString::fromUtf8("label_polynomial_f"));

        gridLayout->addWidget(label_polynomial_f, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_polynomial = new QPushButton(centralWidget);
        pushButton_polynomial->setObjectName(QString::fromUtf8("pushButton_polynomial"));

        horizontalLayout->addWidget(pushButton_polynomial);

        doubleSpinBoxPol = new QDoubleSpinBox(centralWidget);
        doubleSpinBoxPol->setObjectName(QString::fromUtf8("doubleSpinBoxPol"));
        doubleSpinBoxPol->setMaximum(1.000000000000000);
        doubleSpinBoxPol->setSingleStep(0.050000000000000);

        horizontalLayout->addWidget(doubleSpinBoxPol);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 581, 20));
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
        label->setText(QApplication::translate("MainWindow", "cos(x)^2:", nullptr));
        label_real_f->setText(QString());
        label_polynomial->setText(QApplication::translate("MainWindow", "Polynomial:", nullptr));
        label_polynomial_f->setText(QString());
        pushButton_polynomial->setText(QApplication::translate("MainWindow", "Polynomial", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
