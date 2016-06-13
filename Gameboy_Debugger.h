//
// Created by michi on 13.06.16.
//
#ifndef GAMEBOY_EMU_GAMEBOY_DEBUGGER_H
#define GAMEBOY_EMU_GAMEBOY_DEBUGGER_H

#include <iostream>
#include "Gameboy_Cpu.h"
#include <regex>
#include <unordered_set>
#include <string>


#include "Gameboy_Logger.h"
#include "Gameboy_Cpu.h"



class Gameboy_Debugger {
private:
	const regex match_numbers = regex("^\\d+$");
	const regex match_breakpoint_data = regex("^0x[\\dabcdefABCDEF]{4}");
	const regex match_new_breakpoint = regex("^b\\s0x([\\dabcdefABCDEF]{4})");
	const regex match_save_breakpoint = regex("^bs\\s0x([\\dabcdefABCDEF]{4})");

	// Debugger instructions
	const u8 DEBUGGER_STEP = 1;
	const u8 DEBUGGER_NUMBER = 2;
	const u8 DEBUGGER_CONTINUE = 3;
	const u8 DEBUGGER_NEW_BREAKPOINT = 4;
	const u8 DEBUGGER_SAVE_BREAKPOINT = 5;

	unordered_set<u16> breakpoints;

	Gameboy_Logger logger = Gameboy_Logger("/tmp/gameboy_debugger.log");
	Gameboy_Cpu cpu;

	// execute $cycles opcodes or until breakpoint / EOP
	u16 cycles = 0;
	// execute opcodes until breakpoint / EOP
	bool forever = false;

	int string_to_int(string s);
	u16 string_to_short(string s);
	bool is_breakpoint(u16 val);
	u8 match_debugger_instr(string input);
	void load_breakpoints(string location);
	void debug_interface();
public:
	Gameboy_Debugger();
	void run();
};


#endif //GAMEBOY_EMU_GAMEBOY_DEBUGGER_H
