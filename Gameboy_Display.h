//
// Created by michi on 19.06.16.
//

#ifndef CHIP8_EMULATOR_GAMEBOY_DISPLAY_H
#define CHIP8_EMULATOR_GAMEBOY_DISPLAY_H

using u8 = unsigned char;
using u16 = unsigned short;

class Gameboy_Display {
	struct Colour {
		u8 r;
		u8 g;
		u8 b;
	};
private:
	const Colour colours[4] = {
			{255, 255, 255},
			{192, 192, 192},
			{96, 96, 96},
			{0, 0, 0}
	};
	static const u8 SCREEN_WIDTH = 160;
	static const u8 SCREEN_HEIGHT = 144;
	static const u8 MODIFIER = 4;
	u16 display_width = SCREEN_WIDTH * MODIFIER;
	u16 display_height = SCREEN_HEIGHT * MODIFIER;

	u8 screen[SCREEN_HEIGHT][SCREEN_WIDTH][3];

	// display func
	static void display();


public:
	void test_screen(int argc, char **argv);
	void test_screen();
	Gameboy_Display();
};


#endif //CHIP8_EMULATOR_GAMEBOY_DISPLAY_H
