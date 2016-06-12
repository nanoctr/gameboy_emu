#include <iostream>
#include "Gameboy_Cpu.h"
#include <curses.h>
#include <string>
#include <regex>
#include <stdlib.h>

const regex match_numbers("^\\d*$");

using namespace std;

void initialize_curses();
void finalize_curses();
int string_to_int(string s);

int main() {
	Gameboy_Cpu cpu;
	cpu.startup();

	initialize_curses();

	int ch;

	for (int i = 0; i < 30000; i++) {
		ch = wgetch(stdscr);
		// Wait for ENTER key
		if (ch == KEY_ENTER) {
			string input;
			getline(cin, input);

			// Was a number n entered?
			if (regex_match(input, match_numbers)) {
				// execute n opcodes
				for (int n = 0; n < string_to_int(input); ++n) {
					cpu.emulate_cycle();
				}
			}
			// No number entered -> execute one opcode
			else {
				cpu.emulate_cycle();
			}
		}
	}

	//cpu.startup();

	finalize_curses();
	return 0;
}

// stolen from http://www.cplusplus.com/forum/beginner/4520/#msg19965
void initialize_curses() {
	initscr();
	raw();
	(void)noecho();
	nonl();
	intrflush(stdscr, false);
	(void)keypad(stdscr, true);
}
void finalize_curses() {
	endwin();
}

int string_to_int(string s) {
	string::size_type sz;
	return stoi(s, &sz);
}
