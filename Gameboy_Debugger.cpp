//
// Created by michi on 13.06.16.
//

#include "Gameboy_Debugger.h"


Gameboy_Debugger::Gameboy_Debugger() { }


void Gameboy_Debugger::run() {
	while(true)
	{
		// breakpoint hit, stop execution, show debug interface, next loop if done
		if (is_breakpoint(cpu.pc)) {
			forever = false;
			cycles = 0;
			debug_interface();
			continue;
		}

		if (forever) {
			cpu.emulate_cycle();
		}
		else if (cycles) {
			cpu.emulate_cycle();
			--cycles;
		}

		else {
			debug_interface();
		}
	}
}

void Gameboy_Debugger::debug_interface() {
	string input = "";
	getline(cin, input);

	switch (match_debugger_instr(input))
	{
		case DEBUGGER_NUMBER: cycles = string_to_int(input); break;
		case DEBUGGER_CONTINUE: forever = true; break;
		default: cout << "Invalid debugger instruction!" << endl;
	}
}


u8 Gameboy_Debugger::match_debugger_instr(string input) {
	if (input == "") {
		return DEBUGGER_STEP;
	} // empty ENTER -> execute one step
	if (regex_match(input, match_numbers)) {
		return DEBUGGER_NUMBER;
	} // execute $NUMBER steps
	else if (input[0] == 'c') {
		return DEBUGGER_CONTINUE;
	} // execute until EOP
	else if (regex_match(input, match_new_breakpoint)) {
		return DEBUGGER_NEW_BREAKPOINT;
	} // set new breakpoint
	else if (regex_match(input, match_save_breakpoint)) {
		return DEBUGGER_SAVE_BREAKPOINT;
	} // (set new breakpoint), save to file

	return 0;
}

bool Gameboy_Debugger::is_breakpoint(u16 val) {
	return (breakpoints.count(val) != 0);
}

void Gameboy_Debugger::load_breakpoints(string location) {
	ifstream file(location);
	string line;

	while (getline(file, line)) {
		if (regex_match(line, match_breakpoint_data)) {
			breakpoints.insert(string_to_short(line));
		}
	}
}

int Gameboy_Debugger::string_to_int(string s) {
	string::size_type sz;
	return stoi(s, &sz);
}
u16 Gameboy_Debugger::string_to_short(string s) {
	string::size_type sz;
	// TODO: dunno, this is unsafe, but it will never be a problem. fuck it.
	// (gets only 16 bit numbers, is only used in load_breakpoints)
	return stoi(s, &sz);
}