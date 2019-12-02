#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_BlackCurves.h"
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QRegExpValidator>
#include <QGridLayout>

class BlackCurves : public QMainWindow
{
	Q_OBJECT

public:
	BlackCurves(QWidget *parent = Q_NULLPTR);
	QLabel* label;

private:
	Ui::BlackCurvesClass ui;
};
