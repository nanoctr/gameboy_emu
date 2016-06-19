//
// Created by michi on 19.06.16.
//

#include "Gameboy_Display.h"
#include <GL/glut.h>

int i = 0;

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


Gameboy_Display::Gameboy_Display() { }