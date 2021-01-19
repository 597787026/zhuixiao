#include "zhuixiao.h"
#include <QtWidgets/QApplication>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	zhuixiao w;

	w.show();
	return a.exec();
}
