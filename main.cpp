#include <iostream>
#include "Gameboy_Cpu.h"
#include <string>
#include <regex>
#include <stdlib.h>

using namespace std;

const regex match_numbers("^\\d+$");
Gameboy_Logger logger = Gameboy_Logger("/tmp/gameboy_main.log");

int string_to_int(string s);

int main() {
	Gameboy_Cpu cpu;
	cpu.startup();

	string input = "";
	bool debugger = false;
	cout << "Enable Debugger?" << endl;
	getline(cin, input);
	if (input == "y" || input == "yes") {
		debugger = true;
		logger.log_line("\n\n--------------------");
		logger.log_line("DEBUGGER ENABLED");
		logger.log_line("\n--------------------\n\n");
	}

	if (debugger) {
		while(true) {
			getline(cin, input);
			// is line empty?
			if (input == "") {
				// execute one opcode
				cpu.emulate_cycle();
			}
			// input not empty
			else {
				// Was a number n entered?
				if (regex_match(input, match_numbers)) {
					// execute n opcodes
					for (int n = 0; n < string_to_int(input); ++n) {
						cpu.emulate_cycle();
					}
				}
			}
		}
	}
	// debugger disabled, execute 30k opcodes
	else {
		for (int i = 0; i < 30000; i++) {
				cpu.emulate_cycle();
			}
		}


	return 0;
}

int string_to_int(string s) {
	string::size_type sz;
	return stoi(s, &sz);
}
