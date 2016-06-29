//
// Created by michi on 19.06.16.
//

#ifndef GAMEBOY_DISPLAY_H
#define GAMEBOY_DISPLAY_H

#include <memory>

using namespace std;

using u8 = unsigned char;
using u16 = unsigned short;

//struct Colour {
//	u8 r, g, b;
//};

class Gameboy_Cpu;
class Gameboy_Memory;
class Gameboy_Debugger;

class Gameboy_Display {
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

	u8 palette[4] = {255, 192, 96, 0};

	u8 tiles[384][8][8];

	u8 mode;
	u16 clock;
	u8 line;

	// top left corner
	u16 scroll_x;
	u16 scroll_y;

	// LCD control register
	u8 lcdc;
	// u8 LCDC_ENABLE_DISPLAY = 7;
	u8 LCDC_ENABLE_BACKGROUND = 0;
	u8 LCDC_TILEMAP_SELECT = 3;

	u8 get_lcdc(u8 pos);
	void set_lcdc(u8 pos);
	void reset_lcdc(u8 pos);

	// Gameboy_Cpu *cpu;

	// display func
	static void display();
	// render a scanline and write to framebuffer
	void render_line();
	// render framebuffer
	void render_buffer();
	void draw_background();
	void setup_texture();
	void update_texture();



public:
	void test_screen(int argc, char **argv, Gameboy_Debugger * debugger);
	void test_screen();

	// update tiles from VRAM (passed)
	void update_tiles(u8 (&vram)[0x2000], u16 addr);
	void gpu_step(u8 t_cycles);
	//Gameboy_Display(Gameboy_Cpu *gb_cpu);
	Gameboy_Display();

	// TODO: move this to private, make setter
	shared_ptr<Gameboy_Memory> memory;

};

#endif //CHIP8_EMULATOR_GAMEBOY_DISPLAY_H
