//
// Created by michi on 30.06.16.
//

#include "Display.h"
#include <QApplication>

Display::Display(int argc, char **argv) {
	QApplication app(argc, argv);

	app.exec();
}