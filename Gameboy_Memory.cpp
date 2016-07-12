//
// Created by michi on 20.06.16.
//

#include "Gameboy_Memory.h"
#include "Gameboy_Gpu.h"

Gameboy_Memory::Gameboy_Memory() {
	for (auto & i : cartridge_fixed_rom) {
		i = 0;
	}
	for (auto & i : cartridge_switchable_rom) {
		i = 0;
	}
	for (auto & i : vram) {
		i = 0;
	}
	for (auto & i : cartridge_ram) {
		i = 0;
	}
	for (auto & i : internal_ram) {
		i = 0;
	}
	for (auto & i : oam) {
		i = 0;
	}
	for (auto & i : io_registers) {
		i = 0;
	}
	for (auto & i : high_ram) {
		i = 0;
	}
	enable_interrupt = 0;
}

//void Gameboy_Memory::write_short(u16 addr, u16 val) {
//	write_byte(addr, (val >> 8));
//	write_byte(addr + 1, val);
//}
//
//u16 Gameboy_Memory::read_short(u16 addr) {
//	u16 result = (read_byte(addr)) << 8;
//	result |= read_byte(addr + 1);
//	return result;
//}

u8& Gameboy_Memory::read_byte(u16 addr) {
	if (addr <= 0x3FFF) {
		return cartridge_fixed_rom[addr];
	}
	if ((addr >= 0x4000) && (addr <= 0x7FFF)) {
		return cartridge_switchable_rom[addr - 0x4000];
	}
	if ((addr >= 0x8000) && (addr <= 0x9FFF)) {
		if (addr <= 0x97FF) {
			display-> update_tiles(vram, (addr - 0x8000));
		}
		return vram[addr - 0x8000];
	}
	if ((addr >= 0xA000) && (addr <= 0xBFFF)) {
		return cartridge_ram[addr - 0xA000];
	}
	if ((addr >= 0xC000) && (addr <= 0xDFFF)) {
		return internal_ram[addr - 0xC000];
	}
	if ((addr >= 0xFE00) && (addr <= 0xFE9F)) {
		return oam[addr - 0xFE00];
	}
	if ((addr >= 0xFF00) && (addr <= 0xFF7F)) {
		return io_registers[addr - 0xFF00];
	}
	if ((addr >= 0xFF80) && (addr <= 0xFFFE)) {
		return high_ram[addr - 0xFF80];
	}
	if (addr == 0xFFFF) {
		return enable_interrupt;
	}

	// invalid address
	logger.log_line("Error reading byte " + logger.short_to_hex(addr)
					+ ": invalid address!");
	return horrible_hack;
}


u8 &Gameboy_Memory::operator[](u16 addr) {
	return read_byte(addr);
}


//void Gameboy_Memory::write_byte(u16 addr, u8 val) {
//	if (addr <= 0x3FFF) {
//		cartridge_fixed_rom[addr] = val;
//	}
//	if ((addr >= 0x4000) && (addr <= 0x7FFF)) {
//		cartridge_switchable_rom[addr - 0x4000] = val;
//	}
//	if ((addr >= 0x8000) && (addr <= 0x9FFF)) {
//		vram[addr - 0x8000] = val;
//	}
//	if ((addr >= 0xA000) && (addr <= 0xBFFF)) {
//		cartridge_ram[addr - 0xA000] = val;
//	}
//	if ((addr >= 0xC000) && (addr <= 0xDFFF)) {
//		internal_ram[addr - 0xC000] = val;
//	}
//	if ((addr >= 0xFE00) && (addr <= 0xFE9F)) {
//		oam[addr - 0xFE00] = val;
//	}
//	if ((addr >= 0xFF00) && (addr <= 0xFF7F)) {
//		io_registers[addr - 0xFF00] = val;
//	}
//	if ((addr >= 0xFF80) && (addr <= 0xFFFE)) {
//		high_ram[addr - 0xFF80] = val;
//	}
//	if (addr == 0xFFFF) {
//		enable_interrupt = val;
//	}
//
//	// invalid address
//	logger.log_line("Error writing byte " + logger.short_to_hex(addr)
//					+ ": invalid address!");
//}