//
// Created by michi on 20.06.16.
//

#ifndef GAMEBOY_EMU_GAMEBOY_MEMORY_H
#define GAMEBOY_EMU_GAMEBOY_MEMORY_H

#include "Gameboy_Logger.h"

using u8 = unsigned char;
using u16 = unsigned short;

class Gameboy_Memory {
private:
	Gameboy_Logger logger = Gameboy_Logger("/tmp/gameboy_memory.log");
public:
	u8 cartridge_fixed_rom[0x4000]; // 0x000 - 0x3FFF -> ROM bank on cartridge
	u8 cartridge_switchable_rom[0x4000]; // 0x4000 - 0x7FFF -> switchable ROM bank on cartridge
	u8 vram[0x2000]; // 0x8000 - 0x9FFF -> video ram
	u8 cartridge_ram[0x2000]; // 0xA000 - 0xBFFF -> cartridge RAM, if present
	u8 internal_ram[0x2000]; // 0xC000 - 0 0xDFFF -> internal RAM
	// 0xE000 - 0xFDFF -> ram echo, not used
	u8 oam[0x009F]; // 0xFE00 - 0xFE9F -> object attribute memory
	// 0xFEA0 - 0xFEFF -> unused
	u8 io_registers[0x007F]; // 0xFF00 - 0xFF7F -> Hardware IO registers
	u8 high_ram[0x007E]; // 0xFF80 - 0xFFFE -> high RAM (originally meant for stack)
	u8 enable_interrupt;
	/*
	 *  Jesus Christ this is shameful. What have I done.
	 *  This is really awful. really. the [] operator returns a reference
	 *   to this in case the read_byte function fails.
	 *  Effectively defeating one of the best parts of a reference:
	 *  It never being NULL. Congratulations, retard.
	 */
	u8 horrible_hack = 0;

	Gameboy_Memory();
	u8& read_byte(u16 addr);
	u8& operator[] (u16 addr);
	//u16 read_short(u16 addr);
	//void write_byte(u16 addr, u8 val);
	//void write_short(u16 addr, u16 val);
};


#endif //GAMEBOY_EMU_GAMEBOY_MEMORY_H
