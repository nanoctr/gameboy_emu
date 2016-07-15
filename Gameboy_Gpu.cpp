//
// Created by michi on 19.06.16.
//

#include "Gameboy_Gpu.h"
#include "Gameboy_Cpu.h"
#include "Gameboy_Memory.h"
#include "Gameboy_Debugger.h"


//Gameboy_Debugger Gameboy_Gpu::*debugger;
//static void run_runner() {
//	Gameboy_Gpu::debugger-> run();
//}

// int i = 0;

using u8 = unsigned char;
using u16 = unsigned short;

void Gameboy_Gpu::gpu_step(u8 t_cycles) {
	clock += t_cycles;

	switch (mode)
	{
		case 2: // Scanline, accessing OAM
			// done with this phase? -> next phase (scanline, accessing vram)
			//     and reset clock
			if (clock >= 80) {
				mode = 3;
				clock = 0;
			}
			break;
		case 3: // Scanline, accessing VRAM
			if (clock >= 172) {
				mode = 0;
				clock = 0;

				render_line();
			}
			break;
		case 0: // HBlank
			if (clock >= 204) {
				clock = 0;
				++line;

				if (line == 143) {
					mode = 1;
					render_buffer();
				}
				else {
					mode = 2;
				}
			}
			break;
		case 1: // VBlank
			// VBlank done?
			if (clock >= 456) {
				clock = 0;
				++line;

				// all lines done, reset to beginning
				if (line > 153) {
					mode = 2;
					line = 0;
				}
			}
			break;
	}
}

void Gameboy_Gpu::render_line() {
	// god knows what this code does. just stick with it.
	u16 map_offset = (get_lcdc(LCDC_TILEMAP_SELECT)) ? 0x1C00 : 0x1800;
	map_offset += (((line + scroll_y) & 0xFF) >> 3) << 5;

	// some weird bitshifting magic going on here. division or whatever.
	u8 x_offset = scroll_x >> 3;
	u16 x = scroll_x & 7;
	u16 y = (line + scroll_y) & 7;

	u16 pixel_offset = line * 160;

	u8 *vram = memory-> vram;
	u8 *oam = memory-> oam;

	u16 tile = (u16)vram[map_offset + x_offset];

	u8 scanline_row[160];

	u16 i;
	if (get_lcdc(LCDC_ENABLE_BACKGROUND)) {
		for (i = 0; i < 160; ++i) {
			u8 colour = tiles[tile][y][x];

			scanline_row[i] = colour;

			screen[line][i][0] = screen[line][i][1] =
			screen[line][i][2] = palette[colour];


		}
	}

	// loop through OAM
	for (u16 sprite = 0xFE00; sprite <= 0xFE9F; ++sprite) {

	}
}

void Gameboy_Gpu::draw_background() {
}


void Gameboy_Gpu::render_buffer() {
}

// TODO: optimize this: it updates the whole tile, even though the CPU can only
// 	 write 1 byte at a time. Judging by the value, you should be able to find out
//   which row to update
void Gameboy_Gpu::update_tiles(u8 (&vram)[0x2000], u16 addr) {
	u16 tile = addr / 16; // 16 bits for each tile

	// Copy tile data at $addr to the tiles[] array
	for (int y = addr; y < 8; y += 2) {
		for (int x = 0; x < 8; ++x) {
			if (vram[y] & (0x80 >> x)) {
				tiles[tile][y][x] = 1;
			}
			if (vram[y + 1] & (0x80 >> x)) {
				tiles[tile][y][x] += 2;
			}
		}
	}
}


u8 Gameboy_Gpu::get_lcdc(u8 pos) {
	return (lcdc & (0x1 << pos));
}
void Gameboy_Gpu::set_lcdc(u8 pos) {
	lcdc |= (0x1 << pos);
}
void Gameboy_Gpu::reset_lcdc(u8 pos) {
	lcdc &= ~(0x1 << pos);
}




Gameboy_Gpu::Gameboy_Gpu() {
	//cpu = gb_cpu;
	mode = 0;
	clock = 0;
	line = 0;

	QImage my_image(160, 160, QImage::Format_RGB888);
	my_image.fill(0);

	QLabel my_label;
	my_label.setPixmap(QPixmap::fromImage(my_image));

	my_label.show();
};