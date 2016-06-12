#include <iostream>
#include "Gameboy_Cpu.h"
#include <string>
#include <regex>
#include <stdlib.h>

using namespace std;

// Debugger instructions
const u8 DEBUGGER_NUMBER = 1;
const u8 DEBUGGER_CONTINUE = 2;
// saving breakpoints, take these from external files and such
constexpr u16 breakpoints[] = {0x0003, 0x0007};

const regex match_numbers("^\\d+$");

Gameboy_Logger logger = Gameboy_Logger("/tmp/gameboy_main.log");

Gameboy_Cpu cpu;

int string_to_int(string s);
bool is_breakpoint(u16 val);
u8 match_debugger_instr(string input);
void debug();

int main() {
#ifdef DEBUG_BUILD
	logger.log_line("\n\n--------------------");
	logger.log_line("DEBUG BUILD ENABLED");
	logger.log_line("\n--------------------");
#endif
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
		debug();
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

void debug() {
	u64 cycles = 0;
	bool forever = false;
	string input = "";

	while(true)
	{
		if (is_breakpoint(cpu.pc)) {
			forever = false;
			cycles = 0;
		}

		if (forever) {
			cpu.emulate_cycle();
		}
		else if (cycles) {
			cpu.emulate_cycle();
			--cycles;
		}

		else {
			getline(cin, input);
			if (input == ""){
				cpu.emulate_cycle();
				continue;
			} // empty ENTER -> execute one opcode, continue loop, forever stays false

			switch (match_debugger_instr(input))
			{
				case DEBUGGER_NUMBER: cycles = string_to_int(input); break;
				case DEBUGGER_CONTINUE: forever = true; break;
				default: cout << "Invalid debugger instruction!" << endl;
			}
		}
	}
}

u8 match_debugger_instr(string input) {
	if (regex_match(input, match_numbers)) {
		return DEBUGGER_NUMBER;
	}
	else if (input == "c") {
		return DEBUGGER_CONTINUE;
	}

	return 0;
}

bool is_breakpoint(u16 val) {
	const u16 *breakpoint = find(begin(breakpoints), end(breakpoints), val);
	if (breakpoint != breakpoints+2) return true;
	else return false;
}

/*
 *  LEGACY CODE: main func, debug loop
 *
 *
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
				// Continue (until breakpoint hit or done)
				else if (input == "c") {
					for (int i = 0; i < 30000; i++) {
						if (breakpoints.con)
						cpu.emulate_cycle();
					}
				}
			}
		}
 */