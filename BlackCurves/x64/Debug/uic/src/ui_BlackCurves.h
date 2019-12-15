/********************************************************************************
** Form generated from reading UI file 'BlackCurves.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLACKCURVES_H
#define UI_BLACKCURVES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BlackCurvesClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BlackCurvesClass)
    {
        if (BlackCurvesClass->objectName().isEmpty())
            BlackCurvesClass->setObjectName(QString::fromUtf8("BlackCurvesClass"));
        BlackCurvesClass->resize(600, 400);
        menuBar = new QMenuBar(BlackCurvesClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        BlackCurvesClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BlackCurvesClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        BlackCurvesClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(BlackCurvesClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        BlackCurvesClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(BlackCurvesClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        BlackCurvesClass->setStatusBar(statusBar);

        retranslateUi(BlackCurvesClass);

        QMetaObject::connectSlotsByName(BlackCurvesClass);
    } // setupUi

    void retranslateUi(QMainWindow *BlackCurvesClass)
    {
        BlackCurvesClass->setWindowTitle(QApplication::translate("BlackCurvesClass", "BlackCurves", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BlackCurvesClass: public Ui_BlackCurvesClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLACKCURVES_H
