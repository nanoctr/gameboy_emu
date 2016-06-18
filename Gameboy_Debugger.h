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
#include "Debug_Register.h"
#include "Gameboy_Logger.h"
#include "Gameboy_Cpu.h"



class Gameboy_Debugger {
private:
	const regex match_numbers = regex("^(\\d+)");
	const regex match_breakpoint_data = regex("^0x[\\dabcdefABCDEF]{4}");
	const regex match_watches_data = regex("^([abcdehl]|(?:hl|bc|de|af|pc|sp))");
	const regex match_new_breakpoint = regex("^b\\s0x([\\dabcdefABCDEF]{4})");
	const regex match_save_breakpoint = regex("^bs\\s0x([\\dabcdefABCDEF]{4})");
	const regex match_watch_register = regex("^w\\s([abcdehl]$|(?:hl|bc|de|af|pc|sp))$");
	const regex match_watch_save = regex("^ws\\s([abcdehl]$|(?:hl|bc|de|af|pc|sp))$");
	const regex match_print_register = regex("^p\\s([abcdehl]$|(?:hl|bc|de|af|pc|sp))$");
	const regex match_print_memory = regex("^m ([\\dabcdef]{4})");
	//const regex match_print_output = regex("^a$");

	// Debugger instructions
	static const u8 DEBUGGER_STEP = 1;
	static const u8 DEBUGGER_NUMBER = 2;
	static const u8 DEBUGGER_CONTINUE = 3;
	static const u8 DEBUGGER_NEW_BREAKPOINT = 4;
	static const u8 DEBUGGER_SAVE_BREAKPOINT = 5;
	static const u8 DEBUGGER_WATCH_REGISTER = 6;
	static const u8 DEBUGGER_SAFE_WATCH = 7;
	static const u8 DEBUGGER_PRINT_REGISTER = 8;
	static const u8 DEBUGGER_PRINT_MEMORY = 9;
	static const u8 DEBUGGER_PRINT_OUTPUT = 10;


	// Constants
	static constexpr u8 REG_NUMBER = 13;
	static const u8 REG_PC; // = 0;
	static const u8 REG_SP; // = 1;
	static const u8 REG_A ; // = 2;
	static const u8 REG_B ; // = 3;
	static const u8 REG_C ; // = 4;
	static const u8 REG_D ; // = 5;
	static const u8 REG_E ; // = 6;
	static const u8 REG_H ; // = 7;
	static const u8 REG_L ; // = 8;
	static const u8 REG_AF; // = 9;
	static const u8 REG_BC; // = 10;
	static const u8 REG_DE; // = 11;
	static const u8 REG_HL; // = 12;
	// Debug Register Array
	Debug_Register debug_registers[REG_NUMBER];
	// helper map
	unordered_map<string, u8> reg_constants = 	{
			{"a", REG_A},   {"b", REG_B},   {"c", REG_C},
			{"d", REG_D},   {"h", REG_E},   {"h", REG_H},
			{"l", REG_L},   {"af", REG_AF}, {"bc", REG_BC},
			{"de", REG_DE}, {"hl", REG_HL}, {"pc", REG_PC},
			{"sp", REG_SP}
	};


	// Registers mirror
	registers reg;

	unsigned long count_opcodes = 1;


	// Watch the corresponding index in debug_registers?
	bool watch_list[9];
	// Register diff activated?
	bool diff = false;
	registers old_reg;

	static const unordered_map<u8, string> opc_function_names;
	static const unordered_map<u8, string> ext_opc_function_names;

	// Breakpoint list file location
	const string BREAKPOINT_FILE = "/home/michi/ClionProjects/gameboy_emu/breakpoints.txt";
	const string WATCHES_FILE = "/home/michi/ClionProjects/gameboy_emu/watches.txt";

	unordered_set<u16> breakpoints;

	Gameboy_Logger logger = Gameboy_Logger("/tmp/gameboy_debugger.log");
	Gameboy_Cpu cpu;

	// execute $cycles opcodes or until breakpoint / EOP
	u16 steps = 0;
	// execute opcodes until breakpoint / EOP
	bool forever = false;

	int string_to_int(string s);
	u16 string_to_short(string s);
	bool is_breakpoint(u16 val);
	u8 match_debugger_instr(string input, smatch &match);
	void load_breakpoints();
	void load_watches();
	void debug_outputs();
	void debug_interface();
	string print_registers(bool list[9]);
	void print_register(u8 value);
	void print_memory(string p);

	// debug instruction functions:
	void save_breakpoint(smatch input);

public:
	Gameboy_Debugger();
	void run();
};

#endif //GAMEBOY_EMU_GAMEBOY_DEBUGGER_H
