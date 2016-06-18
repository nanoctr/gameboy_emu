//
// Created by michi on 18.06.16.
//

#include <bitset>
#include "Debug_Register.h"

constexpr char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
						   '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

Debug_Register::Debug_Register(u8 *reg_8bit, u16 *reg_16bit, string n_8bit,
							   string n_16bit) {
	register_8bit = reg_8bit;
	register_16bit = reg_16bit;
	name_8bit = n_8bit;
	name_16bit = n_16bit;
}
Debug_Register::Debug_Register() { }

string Debug_Register::description() {
	string result = "";
	if (register_8bit != nullptr) {
		std::bitset<8> bits_8(*register_8bit);
		result.append(name_8bit);
		result.append("    : 0x");
		result.append(char_to_hex(*register_8bit));
		result.append("    |  ");
		result.append(bits_8.to_string());
		result.append(" ---- ----  |  ");
		result.append(to_string(*register_8bit));
		result.append("\n");
	}
	std::bitset<16> bits_16(*register_16bit);

	result.append(name_16bit);
	result.append("   : 0x");
	result.append(short_to_hex(*register_16bit));
	result.append("  |  ");
	result.append(bits_16.to_string());
	result.append("  |  ");
	result.append(to_string(*register_16bit));
	result.append("\n");

	return result;
}


string Debug_Register::char_to_hex(u8 val) {
	string result(2, ' ');
	result[0] = hexmap[(val & 0xF0) >> 4];
	result[1] = hexmap[val & 0x0F];

	return result;
}
string Debug_Register::short_to_hex(u16 val) {
	string result(4, ' ');
	result[0] = hexmap[(val & 0xF000) >> 12];
	result[1] = hexmap[(val & 0x0F00) >> 8];
	result[2] = hexmap[(val & 0x00F0) >> 4];
	result[3] = hexmap[val & 0x000F];

	return result;
}