//
// Created by michi on 18.06.16.
//

#ifndef GAMEBOY_EMU_DEBUG_REGISTER_H
#define GAMEBOY_EMU_DEBUG_REGISTER_H

#include <string>

using u8 = unsigned char;
using u16 = unsigned short;

using namespace std;

// Debugger Functions
	class Debug_Register {
	private:
		string name_8bit;
		string name_16bit;

		string char_to_hex(u8 val);
		string short_to_hex(u16 val);
	public:
		Debug_Register();
		Debug_Register(u8 *reg_8bit, u16 *reg_16bit,
					   string n_8bit, string n_16bit);

		string description();

		u8 *register_8bit;
		u16 *register_16bit;
	};
#endif //GAMEBOY_EMU_DEBUG_REGISTER_H
