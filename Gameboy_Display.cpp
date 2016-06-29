//
// Created by michi on 19.06.16.
//

#include "Gameboy_Display.h"
#include <GL/glut.h>

int i = 0;

void Gameboy_Display::gpu_step(u8 t_cycles) {
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

void Gameboy_Display::render_line() {
	// god knows what this code does. just stick with it.
	u16 map_offset = (get_lcdc(LCDC_TILEMAP_SELECT)) ? 0x1C00 : 0x1800;
	map_offset += (((line + scroll_y) & 0xFF) >> 3) << 5;

	// why do i have to bitshift? don't get it :/
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

			screen[line][i][0] = palette[colour];

		}
	}

	// loop through OAM
	for (u16 sprite = 0xFE00; sprite <= 0xFE9F; ++sprite) {

	}
}

void Gameboy_Display::draw_background() {
}


void Gameboy_Display::render_buffer() {
	glClear(GL_COLOR_BUFFER_BIT);
	update_texture();
	glutSwapBuffers();
}

// TODO: optimize this: it updates the whole tile, even though the CPU can only
// 	 write 1 byte at a time. Judging by the value, you should be able to find out
//   which row to update
void Gameboy_Display::update_tiles(u8 (&vram)[0x2000], u16 addr) {
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


u8 Gameboy_Display::get_lcdc(u8 pos) {
	return (lcdc & (0x1 << pos));
}
void Gameboy_Display::set_lcdc(u8 pos) {
	lcdc |= (0x1 << pos);
}
void Gameboy_Display::reset_lcdc(u8 pos) {
	lcdc &= ~(0x1 << pos);
}



void Gameboy_Display::test_screen(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(display_width, display_height);
	glutInitWindowPosition(320, 320);
	glutCreateWindow("Gameboy");
	//glutDisplayFunc();
	//glutIdleFunc(display);

	setup_texture();

	glutMainLoop();
}

void Gameboy_Display::setup_texture() {
	for (int y = 0; y < SCREEN_HEIGHT; ++y) {
		for (int x = 0; x < SCREEN_WIDTH; ++x) {
			screen[y][x][0] = screen[y][x][1] = screen[y][x][2] = 0;
		}
	}

	// Generate a new texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE,
				 (GLvoid*)screen);
	// Set it up with parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// Enable textures
	glEnable(GL_TEXTURE_2D);
}

void Gameboy_Display::update_texture() {

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
					GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)screen);

	glBegin( GL_QUADS );
	glTexCoord2d(0.0, 0.0);		glVertex2d(0.0,			  0.0);
	glTexCoord2d(1.0, 0.0); 	glVertex2d(display_width, 0.0);
	glTexCoord2d(1.0, 1.0); 	glVertex2d(display_width, display_height);
	glTexCoord2d(0.0, 1.0); 	glVertex2d(0.0,			  display_height);
	glEnd();

}

void Gameboy_Display::display() {
	GL_COLOR_BUFFER_BIT;
}


void Gameboy_Display::test_screen() { }


Gameboy_Display::Gameboy_Display(/*Gameboy_Cpu *gb_cpu*/) {
	//cpu = gb_cpu;
	mode = 0;
	clock = 0;
	line = 0;
	test_screen(0, nullptr);
}