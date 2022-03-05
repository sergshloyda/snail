#include "snail.h"
#include <QtWidgets/QApplication>
#include <qlabel.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Snail w;
	
 
	w.show();
	return a.exec();
}
