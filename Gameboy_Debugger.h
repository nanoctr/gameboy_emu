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
	const regex match_numbers = regex("^(\\d+)");
	const regex match_breakpoint_data = regex("^0x[\\dabcdefABCDEF]{4}");
	const regex match_new_breakpoint = regex("^b\\s0x([\\dabcdefABCDEF]{4})");
	const regex match_save_breakpoint = regex("^bs\\s0x([\\dabcdefABCDEF]{4})");

	// Debugger instructions
	static const u8 DEBUGGER_STEP = 1;
	static const u8 DEBUGGER_NUMBER = 2;
	static const u8 DEBUGGER_CONTINUE = 3;
	static const u8 DEBUGGER_NEW_BREAKPOINT = 4;
	static const u8 DEBUGGER_SAVE_BREAKPOINT = 5;
	static const u8 DEBUGGER_WATCH_REGISTER = 6;
	static const u8 DEBUGGER_PRINT_REGISTER = 7;
	static const u8 DEBUGGER_DIFF_REGISTER = 8;
	static const u8 DEBUGGER_DIFF_ALL = 9;

	// Debugger Functions
	class Debug_Register {
		private:
			u8 * register_8bit;
			u16 * register_16bit;
			char name_8bit;
			string name_16bit;
		public:
			Debug_Register(u8 *reg_8bit, u16 *reg_16bit,
						   char n_8bit, string n_16bit) {
				register_8bit = reg_8bit;
				register_16bit = reg_16bit;
				name_8bit = n_8bit;
				name_16bit = n_16bit;
			}
			string description() {
				string result = "";
				if (register_8bit != nullptr) {
					result.append(to_string(name_8bit));
					result.append("     : ");
					result.append(to_string(*register_8bit));
					result.append("\n");
				}
				result.append(name_16bit);
				result.append("    : ");
				result.append(to_string(*register_16bit));
				result.append("\n");

				return result;
			}
	};
	// Debug Register Array
	Debug_Register debug_registers[9];
	// Constants
	static const u8 REG_PC = 0;
	static const u8 REG_SP = 1;
	static const u8 REG_A = 2;
	static const u8 REG_B = 3;
	static const u8 REG_C = 4;
	static const u8 REG_D = 5;
	static const u8 REG_E = 6;
	static const u8 REG_H = 7;
	static const u8 REG_L = 8;

	// Registers mirror
	registers reg;


	// Watch the corresponding index in debug_registers?
	bool watch_list[9];

	// Breakpoint list file location
	const string BREAKPOINT_FILE = "/home/michi/ClionProjects/gameboy_emu/breakpoints.txt";

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
	void debug_interface();
	string print_registers(bool list[9]);

	// debug instruction functions:
	void save_breakpoint(smatch input);

public:
	Gameboy_Debugger();
	void run();
};


#endif //GAMEBOY_EMU_GAMEBOY_DEBUGGER_H
