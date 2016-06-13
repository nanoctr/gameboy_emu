//
// Created by michi on 13.06.16.
//

#include "Gameboy_Debugger.h"

Gameboy_Debugger::Gameboy_Debugger() { }

// Main execution loop
void Gameboy_Debugger::run() {
	while(true)
	{
		// breakpoint hit, stop execution, show debug interface, next loop when done
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

		// No 'forever' execution or end of cycles to execute -> open debug interface
		else {
			debug_interface();
		}
	}
}

// Debugger main interface: print values, control debugger & code execution
void Gameboy_Debugger::debug_interface() {
	string input = "";
	smatch match;
	getline(cin, input);

	switch (match_debugger_instr(input, match))
	{
		case DEBUGGER_STEP: break; // execute one step
		case DEBUGGER_NUMBER: // execute $NUMBER steps
			cycles = string_to_short(match.str(1)); break;
		case DEBUGGER_CONTINUE: // continue executing
			forever = true; break;
		case DEBUGGER_NEW_BREAKPOINT: // set new breakpoint
			breakpoints.insert(string_to_short(match.str(1))); break;
		case DEBUGGER_SAVE_BREAKPOINT: // set new breakpoint, store in file
			save_breakpoint(match); break;
		default:
			logger.log_line("Invalid Debugger Instruction: " + input);
			cout << "Invalid Debugger Instruction!"; break;
	}
}

// set new breakpoint, store in file
void Gameboy_Debugger::save_breakpoint(smatch input) {
	string s = input.str(1);
	breakpoints.insert(string_to_short(s));

	ofstream file;
	file.open(BREAKPOINT_FILE, ios_base::app);

	file << endl << s;

	file.close();
}


u8 Gameboy_Debugger::match_debugger_instr(string input, smatch match) {
	if (input == "") {
		return DEBUGGER_STEP;
	} // empty ENTER -> execute one step
	if (regex_search(input, match, match_numbers) && match.size() > 1) {
		return DEBUGGER_NUMBER;
	} // execute $NUMBER steps
	else if (input[0] == 'c') {
		return DEBUGGER_CONTINUE;
	} // execute until EOP
	else if (regex_search(input, match, match_new_breakpoint) && match.size() > 1) {
		return DEBUGGER_NEW_BREAKPOINT;
	} // set new breakpoint
	else if (regex_search(input, match, match_save_breakpoint) && match.size() > 1) {
		return DEBUGGER_SAVE_BREAKPOINT;
	} // (set new breakpoint), save to file

	return 0;
}


bool Gameboy_Debugger::is_breakpoint(u16 val) {
	return (breakpoints.count(val) != 0);
}

// load breakpoints from $BREAKPOINT_FILE
void Gameboy_Debugger::load_breakpoints() {
	ifstream file(BREAKPOINT_FILE);
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
// TODO: dunno, this is unsafe, but it will probably never be a problem. fuck it.
// (receives only 16 bit numbers, is called only with regex -> *hex*{4} values)
u16 Gameboy_Debugger::string_to_short(string s) {
	string::size_type sz;
	return stoi(s, &sz);
}