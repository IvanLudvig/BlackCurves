#include "BlackCurves.h"


BlackCurves::BlackCurves(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	widget = new QWidget;
	label = new QLabel("Description", this);
	for (int i = 0; i < 6; i++)
	{
		fields[i] = new QLineEdit("1");
		fields[i]->setFixedWidth(50);
		fields[i]->setValidator(new QRegExpValidator(QRegExp("[+-]?([0-9]*[.])?[0-9]+")));
		labels[i] = new QLabel();
	}
	labels[0]->setText("x^2 + ");
	labels[1]->setText("xy + ");
	labels[2]->setText("y^2 + ");
	labels[3]->setText("x + ");
	labels[4]->setText("y + ");
	labels[5]->setText("= 0");

	QFont font = labels[0]->font();
	font.setPointSizeF(14);
	layout = new QGridLayout();
	for (int i = 0; i < 6; i++)
	{
		fields[i]->setFont(font);
		labels[i]->setFont(font);
		layout->addWidget(fields[i], 0, 2*i);
		layout->addWidget(labels[i], 0, 2*i + 1);
	}
	run = new QPushButton("Run", this);
	layout->addWidget(run, 0, 12);
	label->setFont(font);
	layout->addWidget(label, 1, 0, 1, 12);
	widget->setLayout(layout);

	setWindowTitle("BlackCurves");
	setCentralWidget(widget);
	show();

	connect(run, SIGNAL(clicked()), this, SLOT(handleButton()));
}


void BlackCurves::handleButton()
{
	for (int i = 0; i < 6; i++)
	{
		if (fields[i]->text().isEmpty())
		{
			label->setText("invalid arguments");
			return;
		}
	}

	this->label->setText("hey");
	this->run->setText("Example");

	Curves curves(fields[0]->text().toFloat(), fields[1]->text().toFloat(), fields[2]->text().toFloat(),
		fields[3]->text().toFloat(), fields[4]->text().toFloat(), fields[5]->text().toFloat());
	label->setText(QString::fromStdString(curves.getDescription()));
	// resize button
	//run->resize(100, 100);
	curves.open();
}
