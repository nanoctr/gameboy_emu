//
// Created by michi on 13.06.16.
//

#include "Gameboy_Debugger.h"

Gameboy_Debugger::Gameboy_Debugger() {
	debug_registers[REG_PC] = Debug_Register(nullptr, &reg.pc, ' ', "PC");
	debug_registers[REG_SP] = Debug_Register(nullptr, &reg.sp, ' ', "SP");
	debug_registers[REG_A] = Debug_Register(&reg.a, &reg.af, 'A', "AF");
	debug_registers[REG_AF] = Debug_Register(nullptr, &reg.af, ' ', "AF");
	debug_registers[REG_B] = Debug_Register(&reg.b, &reg.bc, 'B', "BC");
	debug_registers[REG_C] = Debug_Register(&reg.c, &reg.bc, 'C', "BC");
	debug_registers[REG_BC] = Debug_Register(nullptr, &reg.bc, ' ', "BC");
	debug_registers[REG_D] = Debug_Register(&reg.d, &reg.de, 'D', "DE");
	debug_registers[REG_E] = Debug_Register(&reg.e, &reg.de, 'E', "DE");
	debug_registers[REG_DE] = Debug_Register(nullptr, &reg.de, ' ', "DE");
	debug_registers[REG_H] = Debug_Register(&reg.h, &reg.hl, 'H', "HL");
	debug_registers[REG_L] = Debug_Register(&reg.l, &reg.hl, 'L', "HL");
	debug_registers[REG_HL] = Debug_Register(nullptr, &reg.hl, ' ', "HL");

	watch_list[REG_PC] = true;
	watch_list[REG_SP] = true;
}

// Main execution loop
void Gameboy_Debugger::run() {
	while(true)
	{
		// breakpoint hit, stop execution, show debug interface, next loop when done
		if (is_breakpoint(cpu.reg.pc)) {
			forever = false;
			steps = 0;
			reg = cpu.reg;
			debug_interface();
			continue;
		}

		if (forever) {
			cpu.emulate_cycle();
		}
		else if (steps) {
			cpu.emulate_cycle();
			--steps;
		}

		// No 'forever' execution or end of steps to execute -> open debug interface
		else {
			debug_interface();
		}
	}
}

string Gameboy_Debugger::print_register(u8 value) {
	bool arr[REG_NUMBER];
	for (bool & b : arr) {
		b = false;
	}
	arr[value] = true;
	return print_registers(arr);
}

string Gameboy_Debugger::print_registers(bool list[REG_NUMBER]) {
	string result = "REGISTERS: \n";
	for (u8 i = 0; i <= 8; ++i) {
		if (list[i]) {
			result.append(debug_registers[i].description());
		}
	}
	result.append("\n");
	return result;
}

// Debugger main interface: print values, control debugger & code execution
void Gameboy_Debugger::debug_interface() {
	string input = "";
	smatch match;
	getline(cin, input);

	switch (match_debugger_instr(input, match))
	{
		case DEBUGGER_STEP: steps = 1; break; // execute one step
		case DEBUGGER_NUMBER: // execute $NUMBER steps
			steps = string_to_short(match.str(1)); break;
		case DEBUGGER_CONTINUE: // continue executing
			forever = true; break;
		case DEBUGGER_NEW_BREAKPOINT: // set new breakpoint
			breakpoints.insert(string_to_short(match.str(1))); break;
		case DEBUGGER_SAVE_BREAKPOINT: // set new breakpoint, store in file
			save_breakpoint(match); break;
		case DEBUGGER_PRINT_REGISTER: // print register value
			print_register(reg_constants.at(match.str(1))); break;
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


u8 Gameboy_Debugger::match_debugger_instr(string input, smatch &match) {
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
	else if (regex_search(input, match, match_watch_register) && match.size() > 1) {
		return DEBUGGER_WATCH_REGISTER;
	}
	else if (regex_search(input, match, match_watch_save) && match.size() > 1) {
		return DEBUGGER_SAFE_WATCH;
	}
	else if (regex_search(input, match, match_print_register) && match.size() > 1) {
		return DEBUGGER_PRINT_REGISTER;
	}

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