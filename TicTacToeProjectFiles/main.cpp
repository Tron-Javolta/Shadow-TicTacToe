#include "TicTacToeProject.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TicTacToeProject w;
	w.show();
	return a.exec();
}
