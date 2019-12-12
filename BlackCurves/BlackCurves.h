#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_BlackCurves.h"
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QRegExpValidator>
#include <QGridLayout>
#include <Curves.h>

class BlackCurves : public QMainWindow
{
	Q_OBJECT

public:
	BlackCurves(QWidget *parent = Q_NULLPTR);

private slots:
	void handleButton();

private:
	Curves* curves;
	Ui::BlackCurvesClass ui;
	QPushButton* run;
	QLineEdit* fields[7];
	QLabel* labels[7];
	QLabel* label;
	QWidget* widget;
	QGridLayout* layout;
};
