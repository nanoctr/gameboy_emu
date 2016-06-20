//
// Created by michi on 19.06.16.
//

#ifndef CHIP8_EMULATOR_GAMEBOY_DISPLAY_H
#define CHIP8_EMULATOR_GAMEBOY_DISPLAY_H


using u8 = unsigned char;
using u16 = unsigned short;

class Gameboy_Display {
	//struct Colour {
	//	u8 r;
	//	u8 g;
	//	u8 b;
	//};
private:
	//const Colour colours[4] = {
	//		{255, 255, 255},
	//		{192, 192, 192},
	//		{96, 96, 96},
	//		{0, 0, 0}
	//};
	static const u8 SCREEN_WIDTH = 160;
	static const u8 SCREEN_HEIGHT = 144;
	static const u8 MODIFIER = 4;
	u16 display_width = SCREEN_WIDTH * MODIFIER;
	u16 display_height = SCREEN_HEIGHT * MODIFIER;

	u8 screen[SCREEN_HEIGHT][SCREEN_WIDTH][3];

	u8 tiles[384][8][8];

	u8 mode;
	u16 clock;
	u8 line;

	// top left corner
	u16 scroll_x;
	u16 scroll_y;


	// display func
	static void display();
	// render a scanline and write to framebuffer
	void render_line();
	// render framebuffer
	void render_buffer();



public:
	void test_screen(int argc, char **argv);
	void test_screen();

	// update tiles from VRAM (passed)
	void update_tiles(u8 (&vram)[0x2000], u16 addr);
	void gpu_step(u8 t_cycles);
	Gameboy_Display();
};


#endif //CHIP8_EMULATOR_GAMEBOY_DISPLAY_H
