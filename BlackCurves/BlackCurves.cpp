#include "BlackCurves.h"


BlackCurves::BlackCurves(QWidget *parent)
	: QMainWindow(parent)
{

	ui.setupUi(this);
	QWidget* widget = new QWidget;
	//QSpinBox* spinboxx = new QSpinBox();
	//QSlider* slider = new QSlider(Qt::Horizontal);
	QLineEdit* fields[7];
	QLabel* labels[7];
	label = new QLabel("");
	for (int i = 0; i < 6; i++)
	{
		fields[i] = new QLineEdit();
		fields[i]->setFixedWidth(50);
		fields[i]->setValidator(new QRegExpValidator(QRegExp("[0-9]*")));
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
	QGridLayout* layout = new QGridLayout;
	for (int i = 0; i < 6; i++)
	{
		fields[i]->setFont(font);
		labels[i]->setFont(font);
		layout->addWidget(fields[i], 0, 2*i);
		layout->addWidget(labels[i], 0, 2*i + 1);
	}
	QPushButton* run = new QPushButton("Run");
	layout->addWidget(run, 1, 5);
	label->setFont(font);
	layout->addWidget(label, 2, 2);
	widget->setLayout(layout);

	setWindowTitle("BlackCurves");
	setCentralWidget(widget);
	show();
}
