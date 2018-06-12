#include "Suspend.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Suspend w;
	w.show();
	return a.exec();
}
