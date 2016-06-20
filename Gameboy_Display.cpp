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

}


void Gameboy_Display::render_buffer() {

}

void Gameboy_Display::update_tiles(u8 (&vram)[0x2000], u16 addr) {
	for (int y = addr; y < 8; y += 2) {
		for (int x = 0; x < 8; ++x) {
			if (vram[y] & (0x80 >> x)) {
				tiles[5][y][x] = 1;
			}
			if (vram[y + 1] & (0x80 >> x)) {
				tiles[5][y][x] += 2;
			}
		}
	}
}




void Gameboy_Display::test_screen(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(display_width, display_height);
	glutInitWindowPosition(320, 320);
	glutCreateWindow("Gameboy");
	glutDisplayFunc(display);
	//glutIdleFunc(display);

	glutMainLoop();
}

void Gameboy_Display::display() {
	GL_COLOR_BUFFER_BIT;
}


void Gameboy_Display::test_screen() { }


Gameboy_Display::Gameboy_Display() {
	mode = 0;
	clock = 0;
	line = 0;
}