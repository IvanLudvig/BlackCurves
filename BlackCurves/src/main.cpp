#include <iostream>
#include "BlackCurves.h"
#include <QtWidgets/QApplication>
#include "Curves.h"
#include <crtdbg.h>


int main(int argc, char *argv[])
{
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
	_set_error_mode(_OUT_TO_STDERR);
	QApplication a(argc, argv);
	BlackCurves w;
	w.show();

	return a.exec();
}

