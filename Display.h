//
// Created by michi on 30.06.16.
//

#ifndef GAMEBOY_EMU_DISPLAY_H
#define GAMEBOY_EMU_DISPLAY_H

#include <QImage>
#include <QLabel>

class Display {
private:
	QImage screen;
	QLabel screen_label;
public:
	Display(int argc, char **argv);
};


#endif //GAMEBOY_EMU_DISPLAY_H
