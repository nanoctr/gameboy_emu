//
// Created by michi on 30.05.16.
//

#include <iostream>
#include "Gameboy_Cpu.h"


const int CARRY = 4;
const int HALF_CARRY = 5;
const int SUBTRACT = 6;
const int ZERO = 7;

void Gameboy_Cpu::startup() {

	load_opcodes();
	load_extended_opcodes();

	logger = Gameboy_Logger("/tmp/gameboy_cpu.log");
	logger.log_line("\n\n\n--------------------");
	logger.log_line("STARTING EMULATOR");
	logger.log_time();
	logger.log_line("\n--------------------\n\n");

	// PC starts at 0
	reg.pc = 0x0000;

	load_file("/home/michi/ClionProjects/gameboy_emu/DMG_ROM.bin", 0);
}

void Gameboy_Cpu::load_file(string location, u16 starting_point) {
	logger.log_line("loading game: '" + location +
					"', starting at: " + std::to_string(starting_point));

	// NOTE: This code is stolen from...dunno, that Chip-8 tutorial
	FILE *fileptr;
	unsigned long filelen;

	fileptr = fopen(location.c_str(), "rb");
	fseek(fileptr, 0, SEEK_END);
	filelen = ftell(fileptr);
	rewind(fileptr);

	u8 buffer[filelen+1];

	fread(buffer, filelen, 1, fileptr);
	fclose(fileptr);

	for (u16 i = 0; i < filelen; ++i) {
		(*memory)[i + starting_point] = buffer[i];

/*#ifdef DEBUG_BUILD
		if (skip > 0) {
			--skip;
		}
		else {
			try {
				// Store opcode position in vector
				opcode_list.push_back(i);
				// Skip next byte(s)?
				skip = (opcodes.at(buffer[i])).length-1;
				++count_opcodes;
			}
			catch(out_of_range) {
				logger.log("ERROR LOADING FILE: invalid opcode at: 0x");
				logger.log(logger.short_to_hex(i));
				logger.log_line("  #" + std::to_string(count_opcodes));
			}
		}
#endif*/

	}
	// maybe not needed, compiler may optimize it away when unused
#ifdef DEBUG_BUILD
	count_opcodes = 1;
#endif
}


void Gameboy_Cpu::emulate_cycle() {
	if (running) {
		// Fetch opcode
		u8 opcode_id = (*memory)[reg.pc];

		try {
			Opcode opcode = opcodes.at(opcode_id);

			// Call opcode function
			(this->*opcode.opcode_function)();

			// increment CPU steps
			m_cycles += opcode.cycles;
			t_cycles += opcode.cycles * 4;
			m_opc_cycles = opcode.cycles;
			t_opc_cycles = opcode.cycles * 4;

			display-> gpu_step(t_opc_cycles);

			// increment PC
			reg.pc += opcode.length;
		}
		catch (out_of_range) {
			logger.log("ERROR: invalid opcode at: 0x");
			logger.log(logger.short_to_hex(reg.pc));
			logger.log(" - ");
			logger.log(logger.char_to_hex((*memory)[reg.pc]));
#ifdef DEBUG_BUILD
			logger.log_line("  #" + std::to_string(count_opcodes));
#endif
			running = false;
		}
	}
}

void Gameboy_Cpu::opc_di() {}


// populate opcodes hashmaps
void Gameboy_Cpu::load_opcodes() {
	opcodes = {
			{0xF3, Opcode(&Gameboy_Cpu::opc_di, 4, 1)},
			{0xCB, Opcode(&Gameboy_Cpu::opc_ext, 4, 1)},
			{0x3E, Opcode(&Gameboy_Cpu::opc_ld_a_n, 8, 2)},
			{0x06, Opcode(&Gameboy_Cpu::opc_ld_b_n, 8, 2)},
			{0x0E, Opcode(&Gameboy_Cpu::opc_ld_c_n, 8, 2)},
			{0x16, Opcode(&Gameboy_Cpu::opc_ld_d_n, 8, 2)},
			{0x1E, Opcode(&Gameboy_Cpu::opc_ld_e_n, 8, 2)},
			{0x26, Opcode(&Gameboy_Cpu::opc_ld_h_n, 8, 2)},
			{0x2E, Opcode(&Gameboy_Cpu::opc_ld_l_n, 8, 2)},
			{0x01, Opcode(&Gameboy_Cpu::opc_ld_bc_nn, 12, 3)},
			{0x11, Opcode(&Gameboy_Cpu::opc_ld_de_nn, 12, 3)},
			{0x21, Opcode(&Gameboy_Cpu::opc_ld_hl_nn, 12, 3)},
			{0x31, Opcode(&Gameboy_Cpu::opc_ld_sp_nn, 12, 3)},
			{0x36, Opcode(&Gameboy_Cpu::opc_ld_p_hl_n, 12, 2)},
			{0x78, Opcode(&Gameboy_Cpu::opc_ld_a_b, 4, 1)},
			{0x79, Opcode(&Gameboy_Cpu::opc_ld_a_c, 4, 1)},
			{0x7A, Opcode(&Gameboy_Cpu::opc_ld_a_d, 4, 1)},
			{0x7B, Opcode(&Gameboy_Cpu::opc_ld_a_e, 4, 1)},
			{0x7C, Opcode(&Gameboy_Cpu::opc_ld_a_h, 4, 1)},
			{0x7D, Opcode(&Gameboy_Cpu::opc_ld_a_l, 4, 1)},
			{0x7E, Opcode(&Gameboy_Cpu::opc_ld_a_p_hl, 8, 1)},
			{0x7F, Opcode(&Gameboy_Cpu::opc_ld_a_a, 4, 1)},
			{0x0A, Opcode(&Gameboy_Cpu::opc_ld_a_p_bc, 8, 1)}, // unsure about steps
			{0x1A, Opcode(&Gameboy_Cpu::opc_ld_a_p_de, 8, 1)}, // unsure about steps
			{0xFA, Opcode(&Gameboy_Cpu::opc_ld_a_p_nn, 8, 3)}, // unsure about steps
			{0x47, Opcode(&Gameboy_Cpu::opc_ld_b_a, 4, 1)},
			{0x40, Opcode(&Gameboy_Cpu::opc_ld_b_b, 4, 1)},
			{0x41, Opcode(&Gameboy_Cpu::opc_ld_b_c, 4, 1)},
			{0x42, Opcode(&Gameboy_Cpu::opc_ld_b_d, 4, 1)},
			{0x43, Opcode(&Gameboy_Cpu::opc_ld_b_e, 4, 1)},
			{0x44, Opcode(&Gameboy_Cpu::opc_ld_b_h, 4, 1)},
			{0x45, Opcode(&Gameboy_Cpu::opc_ld_b_l, 4, 1)},
			{0x46, Opcode(&Gameboy_Cpu::opc_ld_b_p_hl, 8, 1)},
			{0x4F, Opcode(&Gameboy_Cpu::opc_ld_c_a, 4, 1)},
			{0x48, Opcode(&Gameboy_Cpu::opc_ld_c_b, 4, 1)},
			{0x49, Opcode(&Gameboy_Cpu::opc_ld_c_c, 4, 1)},
			{0x4A, Opcode(&Gameboy_Cpu::opc_ld_c_d, 4, 1)},
			{0x4B, Opcode(&Gameboy_Cpu::opc_ld_c_e, 4, 1)},
			{0x4C, Opcode(&Gameboy_Cpu::opc_ld_c_h, 4, 1)},
			{0x4D, Opcode(&Gameboy_Cpu::opc_ld_c_l, 4, 1)},
			{0x4E, Opcode(&Gameboy_Cpu::opc_ld_c_p_hl, 8, 1)},
			{0x57, Opcode(&Gameboy_Cpu::opc_ld_d_a, 4, 1)},
			{0x50, Opcode(&Gameboy_Cpu::opc_ld_d_b, 4, 1)},
			{0x51, Opcode(&Gameboy_Cpu::opc_ld_d_c, 4, 1)},
			{0x52, Opcode(&Gameboy_Cpu::opc_ld_d_d, 4, 1)},
			{0x53, Opcode(&Gameboy_Cpu::opc_ld_d_e, 4, 1)},
			{0x54, Opcode(&Gameboy_Cpu::opc_ld_d_h, 4, 1)},
			{0x55, Opcode(&Gameboy_Cpu::opc_ld_d_l, 4, 1)},
			{0x56, Opcode(&Gameboy_Cpu::opc_ld_d_p_hl, 8, 1)},
			{0x5F, Opcode(&Gameboy_Cpu::opc_ld_e_a, 4, 1)},
			{0x58, Opcode(&Gameboy_Cpu::opc_ld_e_b, 4, 1)},
			{0x59, Opcode(&Gameboy_Cpu::opc_ld_e_c, 4, 1)},
			{0x5A, Opcode(&Gameboy_Cpu::opc_ld_e_d, 4, 1)},
			{0x5B, Opcode(&Gameboy_Cpu::opc_ld_e_e, 4, 1)},
			{0x5C, Opcode(&Gameboy_Cpu::opc_ld_e_h, 4, 1)},
			{0x5D, Opcode(&Gameboy_Cpu::opc_ld_e_l, 4, 1)},
			{0x5E, Opcode(&Gameboy_Cpu::opc_ld_e_p_hl, 8, 1)},
			{0x67, Opcode(&Gameboy_Cpu::opc_ld_h_a, 4, 1)},
			{0x60, Opcode(&Gameboy_Cpu::opc_ld_h_b, 4, 1)},
			{0x61, Opcode(&Gameboy_Cpu::opc_ld_h_c, 4, 1)},
			{0x62, Opcode(&Gameboy_Cpu::opc_ld_h_d, 4, 1)},
			{0x63, Opcode(&Gameboy_Cpu::opc_ld_h_e, 4, 1)},
			{0x64, Opcode(&Gameboy_Cpu::opc_ld_h_h, 4, 1)},
			{0x65, Opcode(&Gameboy_Cpu::opc_ld_h_l, 4, 1)},
			{0x66, Opcode(&Gameboy_Cpu::opc_ld_h_p_hl, 8, 1)},
			{0x6F, Opcode(&Gameboy_Cpu::opc_ld_l_a, 4, 1)},
			{0x68, Opcode(&Gameboy_Cpu::opc_ld_l_b, 4, 1)},
			{0x69, Opcode(&Gameboy_Cpu::opc_ld_l_c, 4, 1)},
			{0x6A, Opcode(&Gameboy_Cpu::opc_ld_l_d, 4, 1)},
			{0x6B, Opcode(&Gameboy_Cpu::opc_ld_l_e, 4, 1)},
			{0x6C, Opcode(&Gameboy_Cpu::opc_ld_l_h, 4, 1)},
			{0x6D, Opcode(&Gameboy_Cpu::opc_ld_l_l, 4, 1)},
			{0x6E, Opcode(&Gameboy_Cpu::opc_ld_l_p_hl, 8, 1)},
			{0x77, Opcode(&Gameboy_Cpu::opc_ld_p_hl_a, 8, 1)},
			{0x70, Opcode(&Gameboy_Cpu::opc_ld_p_hl_b, 8, 1)},
			{0x71, Opcode(&Gameboy_Cpu::opc_ld_p_hl_c, 8, 1)},
			{0x72, Opcode(&Gameboy_Cpu::opc_ld_p_hl_d, 8, 1)},
			{0x73, Opcode(&Gameboy_Cpu::opc_ld_p_hl_e, 8, 1)},
			{0x74, Opcode(&Gameboy_Cpu::opc_ld_p_hl_h, 8, 1)},
			{0x75, Opcode(&Gameboy_Cpu::opc_ld_p_hl_l, 8, 1)},
			{0x02, Opcode(&Gameboy_Cpu::opc_ld_p_bc_a, 8, 1)},
			{0x12, Opcode(&Gameboy_Cpu::opc_ld_p_de_a, 8, 1)},
			{0x22, Opcode(&Gameboy_Cpu::opc_ldi_hl_a, 8, 1)},
			{0x32, Opcode(&Gameboy_Cpu::opc_ldd_hl_a, 8, 1)},
			{0x2A, Opcode(&Gameboy_Cpu::opc_ldi_a_hl, 8, 1)},
			{0x3A, Opcode(&Gameboy_Cpu::opc_ldd_a_hl, 8, 1)},
			{0x3C, Opcode(&Gameboy_Cpu::opc_inc_a, 4, 1)},
			{0x04, Opcode(&Gameboy_Cpu::opc_inc_b, 4, 1)},
			{0x0C, Opcode(&Gameboy_Cpu::opc_inc_c, 4, 1)},
			{0x14, Opcode(&Gameboy_Cpu::opc_inc_d, 4, 1)},
			{0x1C, Opcode(&Gameboy_Cpu::opc_inc_e, 4, 1)},
			{0x24, Opcode(&Gameboy_Cpu::opc_inc_h, 4, 1)},
			{0x2C, Opcode(&Gameboy_Cpu::opc_inc_l, 4, 1)},
			{0x03, Opcode(&Gameboy_Cpu::opc_inc_bc, 8, 1)},
			{0x13, Opcode(&Gameboy_Cpu::opc_inc_de, 8, 1)},
			{0x23, Opcode(&Gameboy_Cpu::opc_inc_hl, 8, 1)},
			{0x34, Opcode(&Gameboy_Cpu::opc_inc_sp, 8, 1)},
			{0x34, Opcode(&Gameboy_Cpu::opc_inc_p_hl, 12, 1)},
			{0x3D, Opcode(&Gameboy_Cpu::opc_dec_a, 4, 1)},
			{0x05, Opcode(&Gameboy_Cpu::opc_dec_b, 4, 1)},
			{0x0D, Opcode(&Gameboy_Cpu::opc_dec_c, 4, 1)},
			{0x15, Opcode(&Gameboy_Cpu::opc_dec_d, 4, 1)},
			{0x1D, Opcode(&Gameboy_Cpu::opc_dec_e, 4, 1)},
			{0x25, Opcode(&Gameboy_Cpu::opc_dec_h, 4, 1)},
			{0x2D, Opcode(&Gameboy_Cpu::opc_dec_l, 4, 1)},
			{0x0B, Opcode(&Gameboy_Cpu::opc_dec_bc, 8, 1)},
			{0x1B, Opcode(&Gameboy_Cpu::opc_dec_de, 8, 1)},
			{0x2B, Opcode(&Gameboy_Cpu::opc_dec_hl, 8, 1)},
			{0x3B, Opcode(&Gameboy_Cpu::opc_dec_sp, 8, 1)},
			{0x35, Opcode(&Gameboy_Cpu::opc_dec_p_hl, 12, 1)},
			{0x87, Opcode(&Gameboy_Cpu::opc_add_a_a, 4, 1)},
			{0x80, Opcode(&Gameboy_Cpu::opc_add_a_b, 4, 1)},
			{0x81, Opcode(&Gameboy_Cpu::opc_add_a_c, 4, 1)},
			{0x82, Opcode(&Gameboy_Cpu::opc_add_a_d, 4, 1)},
			{0x83, Opcode(&Gameboy_Cpu::opc_add_a_e, 4, 1)},
			{0x84, Opcode(&Gameboy_Cpu::opc_add_a_h, 4, 1)},
			{0x85, Opcode(&Gameboy_Cpu::opc_add_a_l, 4, 1)},
			{0x86, Opcode(&Gameboy_Cpu::opc_add_a_p_hl, 8, 1)},
			{0xC6, Opcode(&Gameboy_Cpu::opc_add_a_n, 8, 2)},
			{0xE8, Opcode(&Gameboy_Cpu::opc_add_sp_d, 16, 1)},
			{0x29, Opcode(&Gameboy_Cpu::opc_add_hl_hl, 8, 1)},
			{0x09, Opcode(&Gameboy_Cpu::opc_add_hl_bc, 8, 1)},
			{0x19, Opcode(&Gameboy_Cpu::opc_add_hl_de, 8, 1)},
			{0x39, Opcode(&Gameboy_Cpu::opc_add_hl_sp, 8, 1)},
			{0x8F, Opcode(&Gameboy_Cpu::opc_adc_a_a, 4, 1)},
			{0x88, Opcode(&Gameboy_Cpu::opc_adc_a_b, 4, 1)},
			{0x89, Opcode(&Gameboy_Cpu::opc_adc_a_c, 4, 1)},
			{0x8A, Opcode(&Gameboy_Cpu::opc_adc_a_d, 4, 1)},
			{0x8B, Opcode(&Gameboy_Cpu::opc_adc_a_e, 4, 1)},
			{0x8C, Opcode(&Gameboy_Cpu::opc_adc_a_h, 4, 1)},
			{0x8D, Opcode(&Gameboy_Cpu::opc_adc_a_l, 4, 1)},
			{0x8E, Opcode(&Gameboy_Cpu::opc_adc_a_p_hl, 8, 1)},
			{0xCE, Opcode(&Gameboy_Cpu::opc_adc_a_n, 8, 2)},
			{0x97, Opcode(&Gameboy_Cpu::opc_sub_a_a, 4, 1)},
			{0x90, Opcode(&Gameboy_Cpu::opc_sub_a_b, 4, 1)},
			{0x91, Opcode(&Gameboy_Cpu::opc_sub_a_c, 4, 1)},
			{0x92, Opcode(&Gameboy_Cpu::opc_sub_a_d, 4, 1)},
			{0x93, Opcode(&Gameboy_Cpu::opc_sub_a_e, 4, 1)},
			{0x94, Opcode(&Gameboy_Cpu::opc_sub_a_h, 4, 1)},
			{0x95, Opcode(&Gameboy_Cpu::opc_sub_a_l, 4, 1)},
			{0x96, Opcode(&Gameboy_Cpu::opc_sub_a_p_hl, 8, 1)},
			{0xD6, Opcode(&Gameboy_Cpu::opc_sub_a_n, 8, 2)},
			{0x9F, Opcode(&Gameboy_Cpu::opc_sbc_a_a, 4, 1)},
			{0x98, Opcode(&Gameboy_Cpu::opc_sbc_a_b, 4, 1)},
			{0x99, Opcode(&Gameboy_Cpu::opc_sbc_a_c, 4, 1)},
			{0x9A, Opcode(&Gameboy_Cpu::opc_sbc_a_d, 4, 1)},
			{0x9B, Opcode(&Gameboy_Cpu::opc_sbc_a_e, 4, 1)},
			{0x9C, Opcode(&Gameboy_Cpu::opc_sbc_a_h, 4, 1)},
			{0x9D, Opcode(&Gameboy_Cpu::opc_sbc_a_l, 4, 1)},
			{0xDE, Opcode(&Gameboy_Cpu::opc_sbc_a_n, 8, 1)},
			{0x9E, Opcode(&Gameboy_Cpu::opc_sbc_a_p_hl, 8, 1)},
			{0xA7, Opcode(&Gameboy_Cpu::opc_and_a_a, 4, 1)},
			{0xA0, Opcode(&Gameboy_Cpu::opc_and_a_b, 4, 1)},
			{0xA1, Opcode(&Gameboy_Cpu::opc_and_a_c, 4, 1)},
			{0xA2, Opcode(&Gameboy_Cpu::opc_and_a_d, 4, 1)},
			{0xA3, Opcode(&Gameboy_Cpu::opc_and_a_e, 4, 1)},
			{0xA4, Opcode(&Gameboy_Cpu::opc_and_a_h, 4, 1)},
			{0xA5, Opcode(&Gameboy_Cpu::opc_and_a_l, 4, 1)},
			{0xE6, Opcode(&Gameboy_Cpu::opc_and_a_n, 8, 2)},
			{0xA6, Opcode(&Gameboy_Cpu::opc_and_a_p_hl, 8, 1)},
			{0xB7, Opcode(&Gameboy_Cpu::opc_or_a_a, 4, 1)},
			{0xB0, Opcode(&Gameboy_Cpu::opc_or_a_b, 4, 1)},
			{0xB1, Opcode(&Gameboy_Cpu::opc_or_a_c, 4, 1)},
			{0xB2, Opcode(&Gameboy_Cpu::opc_or_a_d, 4, 1)},
			{0xB3, Opcode(&Gameboy_Cpu::opc_or_a_e, 4, 1)},
			{0xB4, Opcode(&Gameboy_Cpu::opc_or_a_h, 4, 1)},
			{0xB5, Opcode(&Gameboy_Cpu::opc_or_a_l, 4, 1)},
			{0xF6, Opcode(&Gameboy_Cpu::opc_or_a_n, 8, 2)},
			{0xB6, Opcode(&Gameboy_Cpu::opc_or_a_p_hl, 8, 1)},
			{0xAF, Opcode(&Gameboy_Cpu::opc_xor_a_a, 4, 1)},
			{0xA8, Opcode(&Gameboy_Cpu::opc_xor_a_b, 4, 1)},
			{0xA9, Opcode(&Gameboy_Cpu::opc_xor_a_c, 4, 1)},
			{0xAA, Opcode(&Gameboy_Cpu::opc_xor_a_d, 4, 1)},
			{0xAB, Opcode(&Gameboy_Cpu::opc_xor_a_e, 4, 1)},
			{0xAC, Opcode(&Gameboy_Cpu::opc_xor_a_h, 4, 1)},
			{0xAD, Opcode(&Gameboy_Cpu::opc_xor_a_l, 4, 1)},
			{0xEE, Opcode(&Gameboy_Cpu::opc_xor_a_n, 8, 2)},
			{0xAE, Opcode(&Gameboy_Cpu::opc_xor_a_p_hl, 8, 1)},
			{0xBF, Opcode(&Gameboy_Cpu::opc_cp_a_a, 4, 1)},
			{0xB8, Opcode(&Gameboy_Cpu::opc_cp_a_b, 4, 1)},
			{0xB9, Opcode(&Gameboy_Cpu::opc_cp_a_c, 4, 1)},
			{0xBA, Opcode(&Gameboy_Cpu::opc_cp_a_d, 4, 1)},
			{0xBB, Opcode(&Gameboy_Cpu::opc_cp_a_e, 4, 1)},
			{0xBC, Opcode(&Gameboy_Cpu::opc_cp_a_h, 4, 1)},
			{0xBD, Opcode(&Gameboy_Cpu::opc_cp_a_l, 4, 1)},
			{0xBE, Opcode(&Gameboy_Cpu::opc_cp_a_p_hl, 8, 1)},
			{0xFE, Opcode(&Gameboy_Cpu::opc_cp_a_n, 8, 2)},
			{0xCD, Opcode(&Gameboy_Cpu::opc_call_nn, 24, 0)},
			{0xC4, Opcode(&Gameboy_Cpu::opc_call_nz_nn, 12, 0)},
			{0xD4, Opcode(&Gameboy_Cpu::opc_call_nc_nn, 12, 0)},
			{0xCC, Opcode(&Gameboy_Cpu::opc_call_z_nn, 12, 0)},
			{0xDC, Opcode(&Gameboy_Cpu::opc_call_c_nn, 12, 0)},
			{0xC9, Opcode(&Gameboy_Cpu::opc_ret, 16, 3)}, // TODO: check this, cinoop doesn't increase the PC
			{0xC0, Opcode(&Gameboy_Cpu::opc_ret_nz, 8, 3)},
			{0xD0, Opcode(&Gameboy_Cpu::opc_ret_nc, 8, 3)},
			{0xC8, Opcode(&Gameboy_Cpu::opc_ret_z, 8, 3)},
			{0xD8, Opcode(&Gameboy_Cpu::opc_ret_n, 8, 3)}, // TODO: END
			{0xC3, Opcode(&Gameboy_Cpu::opc_jump_nn, 16, 0)},
			{0xC2, Opcode(&Gameboy_Cpu::opc_jump_nz_nn, 12, 0)},
			{0xD2, Opcode(&Gameboy_Cpu::opc_jump_nc_nn, 12, 0)},
			{0xCA, Opcode(&Gameboy_Cpu::opc_jump_z_nn, 12, 0)},
			{0xDA, Opcode(&Gameboy_Cpu::opc_jump_c_nn, 12, 0)},
			{0xE9, Opcode(&Gameboy_Cpu::opc_jump_hl, 4, 0)},
			{0xC7, Opcode(&Gameboy_Cpu::opc_rst_0, 16, 0)},
			{0xD7, Opcode(&Gameboy_Cpu::opc_rst_10, 16, 0)},
			{0xE7, Opcode(&Gameboy_Cpu::opc_rst_20, 16, 0)},
			{0xF7, Opcode(&Gameboy_Cpu::opc_rst_30, 16, 0)},
			{0xCF, Opcode(&Gameboy_Cpu::opc_rst_8, 16, 0)},
			{0xDF, Opcode(&Gameboy_Cpu::opc_rst_18, 16, 0)},
			{0xEF, Opcode(&Gameboy_Cpu::opc_rst_28, 16, 0)},
			{0xFF, Opcode(&Gameboy_Cpu::opc_rst_38, 16, 0)},
			{0xC5, Opcode(&Gameboy_Cpu::opc_push_bc, 16, 1)},
			{0xD5, Opcode(&Gameboy_Cpu::opc_push_de, 16, 1)},
			{0xE5, Opcode(&Gameboy_Cpu::opc_push_hl, 16, 1)},
			{0xF5, Opcode(&Gameboy_Cpu::opc_push_af, 16, 1)},
			{0xC1, Opcode(&Gameboy_Cpu::opc_pop_bc, 12, 1)},
			{0xD1, Opcode(&Gameboy_Cpu::opc_pop_de, 12, 1)},
			{0xE1, Opcode(&Gameboy_Cpu::opc_pop_hl, 12, 1)},
			{0xF1, Opcode(&Gameboy_Cpu::opc_pop_af, 12, 1)},
			{0xF0, Opcode(&Gameboy_Cpu::opc_ldh_a_p_n, 12, 2)},
			{0xE0, Opcode(&Gameboy_Cpu::opc_ldh_p_n_a, 12, 2)},
			{0xE2, Opcode(&Gameboy_Cpu::opc_ldh_p_c_a, 8, 1)},
			{0xEA, Opcode(&Gameboy_Cpu::opc_ld_p_nn_a, 16, 3)},
			{0x08, Opcode(&Gameboy_Cpu::opc_ld_p_nn_sp, 20, 3)},
			{0xF9, Opcode(&Gameboy_Cpu::opc_ld_sp_hl, 8, 1)},
			{0x3F, Opcode(&Gameboy_Cpu::opc_ccf, 4, 1)},
			{0x37, Opcode(&Gameboy_Cpu::opc_scf, 4, 1)},
			{0x2F, Opcode(&Gameboy_Cpu::opc_cpl, 4, 1)},
			{0x18, Opcode(&Gameboy_Cpu::opc_jr_n, 12, 2)},
			{0x28, Opcode(&Gameboy_Cpu::opc_jr_z_n, 8, 2)},
			{0x38, Opcode(&Gameboy_Cpu::opc_jr_c_n, 8, 2)},
			{0x20, Opcode(&Gameboy_Cpu::opc_jr_nz_n, 8, 2)},
			{0x30, Opcode(&Gameboy_Cpu::opc_jr_nc_n, 8, 2)},
			{0x00, Opcode(&Gameboy_Cpu::opc_nop, 4, 1)},
			{0x10, Opcode(&Gameboy_Cpu::opc_stop, 4, 1)},
			{0x0F, Opcode(&Gameboy_Cpu::opc_rrc_a, 8, 1)},
			{0x07, Opcode(&Gameboy_Cpu::opc_rlc_a, 8, 1)},
			{0x33, Opcode(&Gameboy_Cpu::opc_inc_sp, 8, 1)}
	};
}
void Gameboy_Cpu::load_extended_opcodes() {
	extended_opcodes = {
			{0x47, Opcode(&Gameboy_Cpu::opc_bit_a_0, 8, 1)},
			{0x4F, Opcode(&Gameboy_Cpu::opc_bit_a_1, 8, 1)},
			{0x57, Opcode(&Gameboy_Cpu::opc_bit_a_2, 8, 1)},
			{0x5F, Opcode(&Gameboy_Cpu::opc_bit_a_3, 8, 1)},
			{0x67, Opcode(&Gameboy_Cpu::opc_bit_a_4, 8, 1)},
			{0x6F, Opcode(&Gameboy_Cpu::opc_bit_a_5, 8, 1)},
			{0x77, Opcode(&Gameboy_Cpu::opc_bit_a_6, 8, 1)},
			{0x7F, Opcode(&Gameboy_Cpu::opc_bit_a_7, 8, 1)},
			{0x40, Opcode(&Gameboy_Cpu::opc_bit_b_0, 8, 1)},
			{0x48, Opcode(&Gameboy_Cpu::opc_bit_b_1, 8, 1)},
			{0x50, Opcode(&Gameboy_Cpu::opc_bit_b_2, 8, 1)},
			{0x58, Opcode(&Gameboy_Cpu::opc_bit_b_3, 8, 1)},
			{0x60, Opcode(&Gameboy_Cpu::opc_bit_b_4, 8, 1)},
			{0x68, Opcode(&Gameboy_Cpu::opc_bit_b_5, 8, 1)},
			{0x70, Opcode(&Gameboy_Cpu::opc_bit_b_6, 8, 1)},
			{0x78, Opcode(&Gameboy_Cpu::opc_bit_b_7, 8, 1)},
			{0x41, Opcode(&Gameboy_Cpu::opc_bit_c_0, 8, 1)},
			{0x49, Opcode(&Gameboy_Cpu::opc_bit_c_1, 8, 1)},
			{0x51, Opcode(&Gameboy_Cpu::opc_bit_c_2, 8, 1)},
			{0x59, Opcode(&Gameboy_Cpu::opc_bit_c_3, 8, 1)},
			{0x61, Opcode(&Gameboy_Cpu::opc_bit_c_4, 8, 1)},
			{0x69, Opcode(&Gameboy_Cpu::opc_bit_c_5, 8, 1)},
			{0x71, Opcode(&Gameboy_Cpu::opc_bit_c_6, 8, 1)},
			{0x79, Opcode(&Gameboy_Cpu::opc_bit_c_7, 8, 1)},
			{0x42, Opcode(&Gameboy_Cpu::opc_bit_d_0, 8, 1)},
			{0x4A, Opcode(&Gameboy_Cpu::opc_bit_d_1, 8, 1)},
			{0x52, Opcode(&Gameboy_Cpu::opc_bit_d_2, 8, 1)},
			{0x5A, Opcode(&Gameboy_Cpu::opc_bit_d_3, 8, 1)},
			{0x62, Opcode(&Gameboy_Cpu::opc_bit_d_4, 8, 1)},
			{0x6A, Opcode(&Gameboy_Cpu::opc_bit_d_5, 8, 1)},
			{0x72, Opcode(&Gameboy_Cpu::opc_bit_d_6, 8, 1)},
			{0x7A, Opcode(&Gameboy_Cpu::opc_bit_d_7, 8, 1)},
			{0x43, Opcode(&Gameboy_Cpu::opc_bit_e_0, 8, 1)},
			{0x4B, Opcode(&Gameboy_Cpu::opc_bit_e_1, 8, 1)},
			{0x53, Opcode(&Gameboy_Cpu::opc_bit_e_2, 8, 1)},
			{0x5B, Opcode(&Gameboy_Cpu::opc_bit_e_3, 8, 1)},
			{0x63, Opcode(&Gameboy_Cpu::opc_bit_e_4, 8, 1)},
			{0x6B, Opcode(&Gameboy_Cpu::opc_bit_e_5, 8, 1)},
			{0x73, Opcode(&Gameboy_Cpu::opc_bit_e_6, 8, 1)},
			{0x7B, Opcode(&Gameboy_Cpu::opc_bit_e_7, 8, 1)},
			{0x44, Opcode(&Gameboy_Cpu::opc_bit_h_0, 8, 1)},
			{0x4C, Opcode(&Gameboy_Cpu::opc_bit_h_1, 8, 1)},
			{0x54, Opcode(&Gameboy_Cpu::opc_bit_h_2, 8, 1)},
			{0x5C, Opcode(&Gameboy_Cpu::opc_bit_h_3, 8, 1)},
			{0x64, Opcode(&Gameboy_Cpu::opc_bit_h_4, 8, 1)},
			{0x6C, Opcode(&Gameboy_Cpu::opc_bit_h_5, 8, 1)},
			{0x74, Opcode(&Gameboy_Cpu::opc_bit_h_6, 8, 1)},
			{0x7C, Opcode(&Gameboy_Cpu::opc_bit_h_7, 8, 1)},
			{0x45, Opcode(&Gameboy_Cpu::opc_bit_l_0, 8, 1)},
			{0x4D, Opcode(&Gameboy_Cpu::opc_bit_l_1, 8, 1)},
			{0x55, Opcode(&Gameboy_Cpu::opc_bit_l_2, 8, 1)},
			{0x5D, Opcode(&Gameboy_Cpu::opc_bit_l_3, 8, 1)},
			{0x65, Opcode(&Gameboy_Cpu::opc_bit_l_4, 8, 1)},
			{0x6D, Opcode(&Gameboy_Cpu::opc_bit_l_5, 8, 1)},
			{0x75, Opcode(&Gameboy_Cpu::opc_bit_l_6, 8, 1)},
			{0x7D, Opcode(&Gameboy_Cpu::opc_bit_l_7, 8, 1)},
			{0x46, Opcode(&Gameboy_Cpu::opc_bit_p_hl_0, 12, 1)},
			{0x4E, Opcode(&Gameboy_Cpu::opc_bit_p_hl_1, 12, 1)},
			{0x56, Opcode(&Gameboy_Cpu::opc_bit_p_hl_2, 12, 1)},
			{0x5E, Opcode(&Gameboy_Cpu::opc_bit_p_hl_3, 12, 1)},
			{0x66, Opcode(&Gameboy_Cpu::opc_bit_p_hl_4, 12, 1)},
			{0x6E, Opcode(&Gameboy_Cpu::opc_bit_p_hl_5, 12, 1)},
			{0x76, Opcode(&Gameboy_Cpu::opc_bit_p_hl_6, 12, 1)},
			{0x7E, Opcode(&Gameboy_Cpu::opc_bit_p_hl_7, 12, 1)},
			{0xC7, Opcode(&Gameboy_Cpu::opc_set_a_0, 8, 1)},
			{0xCF, Opcode(&Gameboy_Cpu::opc_set_a_1, 8, 1)},
			{0xD7, Opcode(&Gameboy_Cpu::opc_set_a_2, 8, 1)},
			{0xDF, Opcode(&Gameboy_Cpu::opc_set_a_3, 8, 1)},
			{0xE7, Opcode(&Gameboy_Cpu::opc_set_a_4, 8, 1)},
			{0xEF, Opcode(&Gameboy_Cpu::opc_set_a_5, 8, 1)},
			{0xF7, Opcode(&Gameboy_Cpu::opc_set_a_6, 8, 1)},
			{0xFF, Opcode(&Gameboy_Cpu::opc_set_a_7, 8, 1)},
			{0xC0, Opcode(&Gameboy_Cpu::opc_set_b_0, 8, 1)},
			{0xC8, Opcode(&Gameboy_Cpu::opc_set_b_1, 8, 1)},
			{0xD0, Opcode(&Gameboy_Cpu::opc_set_b_2, 8, 1)},
			{0xD8, Opcode(&Gameboy_Cpu::opc_set_b_3, 8, 1)},
			{0xE0, Opcode(&Gameboy_Cpu::opc_set_b_4, 8, 1)},
			{0xE8, Opcode(&Gameboy_Cpu::opc_set_b_5, 8, 1)},
			{0xF0, Opcode(&Gameboy_Cpu::opc_set_b_6, 8, 1)},
			{0xF8, Opcode(&Gameboy_Cpu::opc_set_b_7, 8, 1)},
			{0xC1, Opcode(&Gameboy_Cpu::opc_set_c_0, 8, 1)},
			{0xC9, Opcode(&Gameboy_Cpu::opc_set_c_1, 8, 1)},
			{0xD1, Opcode(&Gameboy_Cpu::opc_set_c_2, 8, 1)},
			{0xD9, Opcode(&Gameboy_Cpu::opc_set_c_3, 8, 1)},
			{0xE1, Opcode(&Gameboy_Cpu::opc_set_c_4, 8, 1)},
			{0xE9, Opcode(&Gameboy_Cpu::opc_set_c_5, 8, 1)},
			{0xF1, Opcode(&Gameboy_Cpu::opc_set_c_6, 8, 1)},
			{0xF9, Opcode(&Gameboy_Cpu::opc_set_c_7, 8, 1)},
			{0xC2, Opcode(&Gameboy_Cpu::opc_set_d_0, 8, 1)},
			{0xCA, Opcode(&Gameboy_Cpu::opc_set_d_1, 8, 1)},
			{0xD2, Opcode(&Gameboy_Cpu::opc_set_d_2, 8, 1)},
			{0xDA, Opcode(&Gameboy_Cpu::opc_set_d_3, 8, 1)},
			{0xE2, Opcode(&Gameboy_Cpu::opc_set_d_4, 8, 1)},
			{0xEA, Opcode(&Gameboy_Cpu::opc_set_d_5, 8, 1)},
			{0xF2, Opcode(&Gameboy_Cpu::opc_set_d_6, 8, 1)},
			{0xFA, Opcode(&Gameboy_Cpu::opc_set_d_7, 8, 1)},
			{0xC3, Opcode(&Gameboy_Cpu::opc_set_e_0, 8, 1)},
			{0xCB, Opcode(&Gameboy_Cpu::opc_set_e_1, 8, 1)},
			{0xD3, Opcode(&Gameboy_Cpu::opc_set_e_2, 8, 1)},
			{0xDB, Opcode(&Gameboy_Cpu::opc_set_e_3, 8, 1)},
			{0xE3, Opcode(&Gameboy_Cpu::opc_set_e_4, 8, 1)},
			{0xEB, Opcode(&Gameboy_Cpu::opc_set_e_5, 8, 1)},
			{0xF3, Opcode(&Gameboy_Cpu::opc_set_e_6, 8, 1)},
			{0xFB, Opcode(&Gameboy_Cpu::opc_set_e_7, 8, 1)},
			{0xC4, Opcode(&Gameboy_Cpu::opc_set_h_0, 8, 1)},
			{0xCC, Opcode(&Gameboy_Cpu::opc_set_h_1, 8, 1)},
			{0xD4, Opcode(&Gameboy_Cpu::opc_set_h_2, 8, 1)},
			{0xDC, Opcode(&Gameboy_Cpu::opc_set_h_3, 8, 1)},
			{0xE4, Opcode(&Gameboy_Cpu::opc_set_h_4, 8, 1)},
			{0xEC, Opcode(&Gameboy_Cpu::opc_set_h_5, 8, 1)},
			{0xF4, Opcode(&Gameboy_Cpu::opc_set_h_6, 8, 1)},
			{0xFC, Opcode(&Gameboy_Cpu::opc_set_h_7, 8, 1)},
			{0xC5, Opcode(&Gameboy_Cpu::opc_set_l_0, 8, 1)},
			{0xCD, Opcode(&Gameboy_Cpu::opc_set_l_1, 8, 1)},
			{0xD5, Opcode(&Gameboy_Cpu::opc_set_l_2, 8, 1)},
			{0xDD, Opcode(&Gameboy_Cpu::opc_set_l_3, 8, 1)},
			{0xE5, Opcode(&Gameboy_Cpu::opc_set_l_4, 8, 1)},
			{0xED, Opcode(&Gameboy_Cpu::opc_set_l_5, 8, 1)},
			{0xF5, Opcode(&Gameboy_Cpu::opc_set_l_6, 8, 1)},
			{0xFD, Opcode(&Gameboy_Cpu::opc_set_l_7, 8, 1)},
			{0xC6, Opcode(&Gameboy_Cpu::opc_set_p_hl_0, 16, 1)},
			{0xCE, Opcode(&Gameboy_Cpu::opc_set_p_hl_1, 16, 1)},
			{0xD6, Opcode(&Gameboy_Cpu::opc_set_p_hl_2, 16, 1)},
			{0xDE, Opcode(&Gameboy_Cpu::opc_set_p_hl_3, 16, 1)},
			{0xE6, Opcode(&Gameboy_Cpu::opc_set_p_hl_4, 16, 1)},
			{0xEE, Opcode(&Gameboy_Cpu::opc_set_p_hl_5, 16, 1)},
			{0xF6, Opcode(&Gameboy_Cpu::opc_set_p_hl_6, 16, 1)},
			{0xFE, Opcode(&Gameboy_Cpu::opc_set_p_hl_7, 16, 1)},
			{0x87, Opcode(&Gameboy_Cpu::opc_reset_a_0, 8, 1)},
			{0x8F, Opcode(&Gameboy_Cpu::opc_reset_a_1, 8, 1)},
			{0x97, Opcode(&Gameboy_Cpu::opc_reset_a_2, 8, 1)},
			{0x9F, Opcode(&Gameboy_Cpu::opc_reset_a_3, 8, 1)},
			{0xA7, Opcode(&Gameboy_Cpu::opc_reset_a_4, 8, 1)},
			{0xAF, Opcode(&Gameboy_Cpu::opc_reset_a_5, 8, 1)},
			{0xB7, Opcode(&Gameboy_Cpu::opc_reset_a_6, 8, 1)},
			{0xBF, Opcode(&Gameboy_Cpu::opc_reset_a_7, 8, 1)},
			{0x80, Opcode(&Gameboy_Cpu::opc_reset_b_0, 8, 1)},
			{0x88, Opcode(&Gameboy_Cpu::opc_reset_b_1, 8, 1)},
			{0x90, Opcode(&Gameboy_Cpu::opc_reset_b_2, 8, 1)},
			{0x98, Opcode(&Gameboy_Cpu::opc_reset_b_3, 8, 1)},
			{0xA0, Opcode(&Gameboy_Cpu::opc_reset_b_4, 8, 1)},
			{0xA8, Opcode(&Gameboy_Cpu::opc_reset_b_5, 8, 1)},
			{0xB0, Opcode(&Gameboy_Cpu::opc_reset_b_6, 8, 1)},
			{0xB8, Opcode(&Gameboy_Cpu::opc_reset_b_7, 8, 1)},
			{0x81, Opcode(&Gameboy_Cpu::opc_reset_c_0, 8, 1)},
			{0x89, Opcode(&Gameboy_Cpu::opc_reset_c_1, 8, 1)},
			{0x91, Opcode(&Gameboy_Cpu::opc_reset_c_2, 8, 1)},
			{0x99, Opcode(&Gameboy_Cpu::opc_reset_c_3, 8, 1)},
			{0xA1, Opcode(&Gameboy_Cpu::opc_reset_c_4, 8, 1)},
			{0xA9, Opcode(&Gameboy_Cpu::opc_reset_c_5, 8, 1)},
			{0xB1, Opcode(&Gameboy_Cpu::opc_reset_c_6, 8, 1)},
			{0xB9, Opcode(&Gameboy_Cpu::opc_reset_c_7, 8, 1)},
			{0x82, Opcode(&Gameboy_Cpu::opc_reset_d_0, 8, 1)},
			{0x8A, Opcode(&Gameboy_Cpu::opc_reset_d_1, 8, 1)},
			{0x92, Opcode(&Gameboy_Cpu::opc_reset_d_2, 8, 1)},
			{0x9A, Opcode(&Gameboy_Cpu::opc_reset_d_3, 8, 1)},
			{0xA2, Opcode(&Gameboy_Cpu::opc_reset_d_4, 8, 1)},
			{0xAA, Opcode(&Gameboy_Cpu::opc_reset_d_5, 8, 1)},
			{0xB2, Opcode(&Gameboy_Cpu::opc_reset_d_6, 8, 1)},
			{0xBA, Opcode(&Gameboy_Cpu::opc_reset_d_7, 8, 1)},
			{0x83, Opcode(&Gameboy_Cpu::opc_reset_e_0, 8, 1)},
			{0x8B, Opcode(&Gameboy_Cpu::opc_reset_e_1, 8, 1)},
			{0x93, Opcode(&Gameboy_Cpu::opc_reset_e_2, 8, 1)},
			{0x9B, Opcode(&Gameboy_Cpu::opc_reset_e_3, 8, 1)},
			{0xA3, Opcode(&Gameboy_Cpu::opc_reset_e_4, 8, 1)},
			{0xAB, Opcode(&Gameboy_Cpu::opc_reset_e_5, 8, 1)},
			{0xB3, Opcode(&Gameboy_Cpu::opc_reset_e_6, 8, 1)},
			{0xBB, Opcode(&Gameboy_Cpu::opc_reset_e_7, 8, 1)},
			{0x84, Opcode(&Gameboy_Cpu::opc_reset_h_0, 8, 1)},
			{0x8C, Opcode(&Gameboy_Cpu::opc_reset_h_1, 8, 1)},
			{0x94, Opcode(&Gameboy_Cpu::opc_reset_h_2, 8, 1)},
			{0x9C, Opcode(&Gameboy_Cpu::opc_reset_h_3, 8, 1)},
			{0xA4, Opcode(&Gameboy_Cpu::opc_reset_h_4, 8, 1)},
			{0xAC, Opcode(&Gameboy_Cpu::opc_reset_h_5, 8, 1)},
			{0xB4, Opcode(&Gameboy_Cpu::opc_reset_h_6, 8, 1)},
			{0xBC, Opcode(&Gameboy_Cpu::opc_reset_h_7, 8, 1)},
			{0x85, Opcode(&Gameboy_Cpu::opc_reset_l_0, 8, 1)},
			{0x8D, Opcode(&Gameboy_Cpu::opc_reset_l_1, 8, 1)},
			{0x95, Opcode(&Gameboy_Cpu::opc_reset_l_2, 8, 1)},
			{0x9D, Opcode(&Gameboy_Cpu::opc_reset_l_3, 8, 1)},
			{0xA5, Opcode(&Gameboy_Cpu::opc_reset_l_4, 8, 1)},
			{0xAD, Opcode(&Gameboy_Cpu::opc_reset_l_5, 8, 1)},
			{0xB5, Opcode(&Gameboy_Cpu::opc_reset_l_6, 8, 1)},
			{0xBD, Opcode(&Gameboy_Cpu::opc_reset_l_7, 8, 1)},
			{0x86, Opcode(&Gameboy_Cpu::opc_reset_p_hl_0, 16, 1)},
			{0x8E, Opcode(&Gameboy_Cpu::opc_reset_p_hl_1, 16, 1)},
			{0x96, Opcode(&Gameboy_Cpu::opc_reset_p_hl_2, 16, 1)},
			{0x9E, Opcode(&Gameboy_Cpu::opc_reset_p_hl_3, 16, 1)},
			{0xA6, Opcode(&Gameboy_Cpu::opc_reset_p_hl_4, 16, 1)},
			{0xAE, Opcode(&Gameboy_Cpu::opc_reset_p_hl_5, 16, 1)},
			{0xB6, Opcode(&Gameboy_Cpu::opc_reset_p_hl_6, 16, 1)},
			{0xBE, Opcode(&Gameboy_Cpu::opc_reset_p_hl_7, 16, 1)},
			{0x3F, Opcode(&Gameboy_Cpu::opc_srl_a, 8, 1)},
			{0x38, Opcode(&Gameboy_Cpu::opc_srl_b, 8, 1)},
			{0x39, Opcode(&Gameboy_Cpu::opc_srl_c, 8, 1)},
			{0x3A, Opcode(&Gameboy_Cpu::opc_srl_d, 8, 1)},
			{0x3B, Opcode(&Gameboy_Cpu::opc_srl_e, 8, 1)},
			{0x3C, Opcode(&Gameboy_Cpu::opc_srl_h, 8, 1)},
			{0x3D, Opcode(&Gameboy_Cpu::opc_srl_l, 8, 1)},
			{0x3E, Opcode(&Gameboy_Cpu::opc_srl_p_hl, 16, 1)},
			{0x2F, Opcode(&Gameboy_Cpu::opc_sra_a, 8, 1)},
			{0x28, Opcode(&Gameboy_Cpu::opc_sra_b, 8, 1)},
			{0x29, Opcode(&Gameboy_Cpu::opc_sra_c, 8, 1)},
			{0x2A, Opcode(&Gameboy_Cpu::opc_sra_d, 8, 1)},
			{0x2B, Opcode(&Gameboy_Cpu::opc_sra_e, 8, 1)},
			{0x2C, Opcode(&Gameboy_Cpu::opc_sra_h, 8, 1)},
			{0x2D, Opcode(&Gameboy_Cpu::opc_sra_l, 8, 1)},
			{0x2E, Opcode(&Gameboy_Cpu::opc_sra_p_hl, 16, 1)},
			{0x27, Opcode(&Gameboy_Cpu::opc_sla_a, 8, 1)},
			{0x20, Opcode(&Gameboy_Cpu::opc_sla_b, 8, 1)},
			{0x21, Opcode(&Gameboy_Cpu::opc_sla_c, 8, 1)},
			{0x22, Opcode(&Gameboy_Cpu::opc_sla_d, 8, 1)},
			{0x23, Opcode(&Gameboy_Cpu::opc_sla_e, 8, 1)},
			{0x24, Opcode(&Gameboy_Cpu::opc_sla_h, 8, 1)},
			{0x25, Opcode(&Gameboy_Cpu::opc_sla_l, 8, 1)},
			{0x26, Opcode(&Gameboy_Cpu::opc_sla_p_hl, 16, 1)},
			{0x1F, Opcode(&Gameboy_Cpu::opc_rr_a, 8, 1)},
			{0x18, Opcode(&Gameboy_Cpu::opc_rr_b, 8, 1)},
			{0x19, Opcode(&Gameboy_Cpu::opc_rr_c, 8, 1)},
			{0x1A, Opcode(&Gameboy_Cpu::opc_rr_d, 8, 1)},
			{0x1B, Opcode(&Gameboy_Cpu::opc_rr_e, 8, 1)},
			{0x1C, Opcode(&Gameboy_Cpu::opc_rr_h, 8, 1)},
			{0x1D, Opcode(&Gameboy_Cpu::opc_rr_l, 8, 1)},
			{0x1E, Opcode(&Gameboy_Cpu::opc_rr_p_hl, 16, 1)},
			{0x17, Opcode(&Gameboy_Cpu::opc_rl_a, 8, 1)},
			{0x10, Opcode(&Gameboy_Cpu::opc_rl_b, 8, 1)},
			{0x11, Opcode(&Gameboy_Cpu::opc_rl_c, 8, 1)},
			{0x12, Opcode(&Gameboy_Cpu::opc_rl_d, 8, 1)},
			{0x13, Opcode(&Gameboy_Cpu::opc_rl_e, 8, 1)},
			{0x14, Opcode(&Gameboy_Cpu::opc_rl_h, 8, 1)},
			{0x15, Opcode(&Gameboy_Cpu::opc_rl_l, 8, 1)},
			{0x16, Opcode(&Gameboy_Cpu::opc_rl_p_hl, 16, 1)},
			{0x0F, Opcode(&Gameboy_Cpu::opc_rrc_a, 8, 1)},
			{0x08, Opcode(&Gameboy_Cpu::opc_rrc_b, 8, 1)},
			{0x09, Opcode(&Gameboy_Cpu::opc_rrc_c, 8, 1)},
			{0x0A, Opcode(&Gameboy_Cpu::opc_rrc_d, 8, 1)},
			{0x0B, Opcode(&Gameboy_Cpu::opc_rrc_e, 8, 1)},
			{0x0C, Opcode(&Gameboy_Cpu::opc_rrc_h, 8, 1)},
			{0x0D, Opcode(&Gameboy_Cpu::opc_rrc_l, 8, 1)},
			{0x0E, Opcode(&Gameboy_Cpu::opc_rrc_p_hl, 16, 1)},
			{0x07, Opcode(&Gameboy_Cpu::opc_rlc_a, 8, 1)},
			{0x00, Opcode(&Gameboy_Cpu::opc_rlc_b, 8, 1)},
			{0x01, Opcode(&Gameboy_Cpu::opc_rlc_c, 8, 1)},
			{0x02, Opcode(&Gameboy_Cpu::opc_rlc_d, 8, 1)},
			{0x03, Opcode(&Gameboy_Cpu::opc_rlc_e, 8, 1)},
			{0x04, Opcode(&Gameboy_Cpu::opc_rlc_h, 8, 1)},
			{0x05, Opcode(&Gameboy_Cpu::opc_rlc_l, 8, 1)},
			{0x06, Opcode(&Gameboy_Cpu::opc_rlc_p_hl, 16, 1)},
	};
}


// LOAD group - load value into register

// load free value into register

// 0x06 - load n in B
void Gameboy_Cpu::opc_ld_b_n() {
	reg.b = (*memory)[reg.pc+1];
	// pc += 2;
}
// 0x0E - load in C
void Gameboy_Cpu::opc_ld_c_n() {
	reg.c = (*memory)[reg.pc+1];
	// pc += 2;
}
// 0x16 - load in D
void Gameboy_Cpu::opc_ld_d_n() {
	reg.d = (*memory)[reg.pc+1];
	// pc += 2;
}
// 0x1E - load in E
void Gameboy_Cpu::opc_ld_e_n() {
	reg.e = (*memory)[reg.pc+1];
	// pc += 2;
}
// 0x26 - load in H
void Gameboy_Cpu::opc_ld_h_n() {
	reg.h = (*memory)[reg.pc+1];
	// pc += 2;
}
// 0x2E - load in L
void Gameboy_Cpu::opc_ld_l_n() {
	reg.l = (*memory)[reg.pc+1];
	// pc += 2;
}
// 0x01 - load 16bit in BC
void Gameboy_Cpu::opc_ld_bc_nn() {
	reg.bc = ((*memory)[reg.pc+2] << 8) | (*memory)[reg.pc+1];
	// pc += 3;
}
// 0x11 - load 16bit in DE
void Gameboy_Cpu::opc_ld_de_nn() {
	reg.de = ((*memory)[reg.pc+2] << 8) | (*memory)[reg.pc+1];
	// pc += 3;
}
// 0x21 - load 16bit in HL
void Gameboy_Cpu::opc_ld_hl_nn() {
	reg.hl = ((*memory)[reg.pc+2] << 8) | (*memory)[reg.pc+1];
	// pc += 3;
}
// 0x31 - load 16bit in SP
void Gameboy_Cpu::opc_ld_sp_nn() {
	reg.sp = ((*memory)[reg.pc+2] << 8) | (*memory)[reg.pc+1];
	// pc += 3;
}
// 0x36 - load 8bit in HL
void Gameboy_Cpu::opc_ld_p_hl_n() {
	(*memory)[reg.hl] = (*memory)[reg.pc+1];
	// pc += 2;
}

// LD a, a & so on -> NOP calls essentially

void Gameboy_Cpu::opc_ld_a_a() {
	opc_nop();
}
void Gameboy_Cpu::opc_ld_b_b() {
	opc_nop();
}
void Gameboy_Cpu::opc_ld_c_c() {
	opc_nop();
}
void Gameboy_Cpu::opc_ld_d_d() {
	opc_nop();
}
void Gameboy_Cpu::opc_ld_e_e() {
	opc_nop();
}
void Gameboy_Cpu::opc_ld_h_h() {
	opc_nop();
}
void Gameboy_Cpu::opc_ld_l_l() {
	opc_nop();
}

// copy register r2 into r1

void Gameboy_Cpu::opc_ld_a_b() {
	reg.a = reg.b;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_a_c() {
	reg.a = reg.c;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_a_d() {
	reg.a = reg.d;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_a_e() {
	reg.a = reg.e;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_a_h() {
	reg.a = reg.h;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_a_l() {
	reg.a = reg.l;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_a_p_hl() {
	reg.a = (*memory)[reg.hl];
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_a_p_bc() {
	reg.a = (*memory)[reg.bc];
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_a_p_de() {
	reg.a = (*memory)[reg.de];
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_a_p_nn() {
	reg.a = (*memory)[((*memory)[reg.pc+1] << 8) & (*memory)[reg.pc+2]];
	// pc += 3;
}
void Gameboy_Cpu::opc_ld_a_n() {
	reg.a = (*memory)[reg.pc+1];
	// pc += 2;
}
void Gameboy_Cpu::opc_ld_b_a() {
	reg.b = reg.a;
	// ++reg.pc;
} //0x47
void Gameboy_Cpu::opc_ld_b_c() {
	reg.b = reg.c;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_b_d() {
	reg.b = reg.d;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_b_e() {
	reg.b = reg.e;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_b_h() {
	reg.b = reg.h;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_b_l() {
	reg.b = reg.l;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_b_p_hl() {
	reg.b = (*memory)[reg.hl];
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_c_a() {
	reg.c = reg.a;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_c_b() {
	reg.c = reg.b;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_c_d() {
	reg.c = reg.d;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_c_e() {
	reg.c = reg.e;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_c_h() {
	reg.c = reg.h;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_c_l() {
	reg.c = reg.l;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_c_p_hl() {
	reg.c = (*memory)[reg.hl];
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_d_a() {
	reg.d = reg.a;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_d_b() {
	reg.d = reg.b;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_d_c() {
	reg.d = reg.c;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_d_e() {
	reg.d = reg.e;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_d_h() {
	reg.d = reg.h;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_d_l() {
	reg.d = reg.l;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_d_p_hl() {
	reg.d = (*memory)[reg.hl];
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_e_a() {
	reg.e = reg.a;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_e_b() {
	reg.e = reg.b;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_e_c() {
	reg.e = reg.c;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_e_d() {
	reg.e = reg.d;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_e_h() {
	reg.e = reg.h;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_e_l() {
	reg.e = reg.l;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_e_p_hl() {
	reg.e = (*memory)[reg.hl];
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_h_a() {
	reg.h = reg.a;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_h_b() {
	reg.h = reg.b;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_h_c() {
	reg.h = reg.c;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_h_d() {
	reg.h = reg.d;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_h_e() {
	reg.h = reg.e;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_h_l() {
	reg.h = reg.l;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_h_p_hl() {
	reg.h = (*memory)[reg.hl];
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_l_a() {
	reg.l = reg.a;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_l_b() {
	reg.l = reg.b;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_l_c() {
	reg.l = reg.c;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_l_d() {
	reg.l = reg.d;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_l_e() {
	reg.l = reg.e;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_l_h() {
	reg.l = reg.h;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_l_p_hl() {
	reg.l = (*memory)[reg.hl];
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_p_hl_a() {
	(*memory)[reg.hl] = reg.a;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_p_hl_b() {
	(*memory)[reg.hl] = reg.b;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_p_hl_c() {
	(*memory)[reg.hl] = reg.c;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_p_hl_d() {
	(*memory)[reg.hl] = reg.d;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_p_hl_e() {
	(*memory)[reg.hl] = reg.e;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_p_hl_h() {
	(*memory)[reg.hl] = reg.h;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ld_p_hl_l() {
	(*memory)[reg.hl] = reg.l;
	// ++reg.pc;
}

void Gameboy_Cpu::opc_ld_p_bc_a() {
	(*memory)[reg.bc] = reg.a;
	// ++reg.pc;
} //0x02
void Gameboy_Cpu::opc_ld_p_de_a() {
	(*memory)[reg.de] = reg.a;
	// ++reg.pc;
} //0x12

void Gameboy_Cpu::opc_ldi_hl_a() {
	(*memory)[reg.hl] = reg.a;
	inc16(reg.hl);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ldd_hl_a() {
	(*memory)[reg.hl] = reg.a;
	--reg.hl;
	// ++reg.pc;
}

// increment values

void Gameboy_Cpu::opc_inc_bc() {
	inc16(reg.bc);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_inc_de() {
	inc16(reg.de);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_inc_hl() {
	inc16(reg.hl);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_inc_sp() {
	inc16(reg.sp);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_inc_a() {
	inc(reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_inc_b() {
	inc(reg.b);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_inc_c() {
	inc(reg.c);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_inc_d() {
	inc(reg.d);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_inc_e() {
	inc(reg.e);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_inc_h() {
	inc(reg.h);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_inc_l() {
	inc(reg.l);
	// ++reg.pc;
}

void Gameboy_Cpu::opc_inc_p_hl() {
	inc((*memory)[reg.hl]);
	// ++reg.pc;
}

// decrement values

void Gameboy_Cpu::opc_dec_hl() {
	dec16(reg.hl);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_dec_bc() {
	dec16(reg.bc);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_dec_de() {
	dec16(reg.de);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_dec_sp() {
	dec16(reg.sp);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_dec_a() {
	dec(reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_dec_b() {
	dec(reg.b);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_dec_c() {
	dec(reg.c);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_dec_d() {
	dec(reg.d);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_dec_e() {
	dec(reg.e);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_dec_h() {
	dec(reg.h);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_dec_l() {
	dec(reg.l);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_dec_p_hl() {
	dec((*memory)[reg.hl]);
	// ++reg.pc;
}


void Gameboy_Cpu::opc_ldi_a_hl() {
	reg.a = (*memory)[reg.hl];
	++reg.hl;
	// ++reg.pc;
}
void Gameboy_Cpu::opc_ldd_a_hl() {
	reg.a = (*memory)[reg.hl];
	--reg.hl;
	// ++reg.pc;
}

//TODO: you gotta set flags in DEC / INC too, retard
//TODO: check other opcodes for flags that need to be set



// add stuff to A

void Gameboy_Cpu::opc_add_a_a() {
	add(reg.a, reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_add_a_b() {
	add(reg.a, reg.b);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_add_a_c() {
	add(reg.a, reg.c);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_add_a_d() {
	add(reg.a, reg.d);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_add_a_e() {
	add(reg.a, reg.e);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_add_a_h() {
	add(reg.a, reg.h);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_add_a_l() {
	add(reg.a, reg.l);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_add_a_p_hl() {
	add(reg.a, (*memory)[reg.hl]);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_add_a_n() {
	add(reg.a, (*memory)[reg.pc+1]);
	// pc += 2;
}

void Gameboy_Cpu::opc_add_sp_d() {
	add16(reg.sp, reg.d);
	// ++reg.pc;
}

// add to A with carry

void Gameboy_Cpu::opc_adc_a_a() {
	adc(reg.a, reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_adc_a_b() {
	adc(reg.a, reg.b);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_adc_a_c() {
	adc(reg.a, reg.c);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_adc_a_d() {
	adc(reg.a, reg.d);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_adc_a_e() {
	adc(reg.a, reg.e);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_adc_a_h() {
	adc(reg.a, reg.h);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_adc_a_l() {
	adc(reg.a, reg.l);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_adc_a_p_hl() {
	adc(reg.a, (*memory)[reg.hl]);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_adc_a_n() {
	adc(reg.a, (*memory)[reg.pc+1]);
	// pc += 2;
}

// subtract from A

void Gameboy_Cpu::opc_sub_a_a() {
	sub(reg.a, reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sub_a_b() {
	sub(reg.a, reg.b);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sub_a_c() {
	sub(reg.a, reg.c);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sub_a_d() {
	sub(reg.a, reg.d);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sub_a_e() {
	sub(reg.a, reg.e);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sub_a_h() {
	sub(reg.a, reg.h);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sub_a_l() {
	sub(reg.a, reg.l);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sub_a_p_hl() {
	sub(reg.a, (*memory)[reg.hl]);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sub_a_n() {
	sub(reg.a, (*memory)[reg.pc]);
	// ++reg.pc;
}

// subtract with carry

void Gameboy_Cpu::opc_sbc_a_a() {
	sbc(reg.a, reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sbc_a_b() {
	sbc(reg.a, reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sbc_a_c() {
	sbc(reg.a, reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sbc_a_d() {
	sbc(reg.a, reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sbc_a_e() {
	sbc(reg.a, reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sbc_a_h() {
	sbc(reg.a, reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sbc_a_l() {
	sbc(reg.a, reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sbc_a_n() {
	sbc(reg.a, (*memory)[reg.pc+1]);
	// pc += 2;
}
void Gameboy_Cpu::opc_sbc_a_p_hl() {
	sbc(reg.a, (*memory)[reg.hl]);
	// ++reg.pc;
}

// add 16 bit values

void Gameboy_Cpu::opc_add_hl_hl() {
	add16(reg.hl, reg.hl);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_add_hl_bc() {
	add16(reg.hl, reg.bc);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_add_hl_de() {
	add16(reg.hl, reg.de);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_add_hl_sp() {
	add16(reg.hl, reg.sp);
	// ++reg.pc;
}

// logical AND

void Gameboy_Cpu::opc_and_a_a() {
	logical_and(reg.a, reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_and_a_b() {
	logical_and(reg.a, reg.b);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_and_a_c() {
	logical_and(reg.a, reg.c);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_and_a_d() {
	logical_and(reg.a, reg.d);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_and_a_e() {
	logical_and(reg.a, reg.e);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_and_a_h() {
	logical_and(reg.a, reg.h);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_and_a_l() {
	logical_and(reg.a, reg.l);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_and_a_n() {
	logical_and(reg.a, (*memory)[reg.pc+1]);
	// pc += 2;
}
void Gameboy_Cpu::opc_and_a_p_hl() {
	logical_and(reg.a, (*memory)[reg.hl]);
	// pc += 2;
}


// logical OR

void Gameboy_Cpu::opc_or_a_a() {
	logical_or(reg.a, reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_or_a_b() {
	logical_or(reg.a, reg.b);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_or_a_c() {
	logical_or(reg.a, reg.c);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_or_a_d() {
	logical_or(reg.a, reg.d);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_or_a_e() {
	logical_or(reg.a, reg.e);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_or_a_h() {
	logical_or(reg.a, reg.h);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_or_a_l() {
	logical_or(reg.a, reg.l);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_or_a_n() {
	logical_or(reg.a, (*memory)[reg.pc+1]);
	// pc += 2;
}
void Gameboy_Cpu::opc_or_a_p_hl() {
	logical_or(reg.a, (*memory)[reg.hl]);
	// ++reg.pc;
}

// logical XOR

void Gameboy_Cpu::opc_xor_a_a() {
	logical_xor(reg.a, reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_xor_a_b() {
	logical_xor(reg.a, reg.b);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_xor_a_c() {
	logical_xor(reg.a, reg.c);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_xor_a_d() {
	logical_xor(reg.a, reg.d);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_xor_a_e() {
	logical_xor(reg.a, reg.e);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_xor_a_h() {
	logical_xor(reg.a, reg.h);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_xor_a_l() {
	logical_xor(reg.a, reg.l);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_xor_a_n() {
	logical_xor(reg.a, (*memory)[reg.pc+1]);
	// pc += 2;
}
void Gameboy_Cpu::opc_xor_a_p_hl() {
	logical_xor(reg.a, (*memory)[reg.hl]);
	// ++reg.pc;
}

// compare against a

void Gameboy_Cpu::opc_cp_a_a() {
	compare(reg.a, reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_cp_a_b() {
	compare(reg.a, reg.b);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_cp_a_c() {
	compare(reg.a, reg.c);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_cp_a_d() {
	compare(reg.a, reg.d);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_cp_a_e() {
	compare(reg.a, reg.e);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_cp_a_h() {
	compare(reg.a, reg.h);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_cp_a_l() {
	compare(reg.a, reg.l);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_cp_a_n() {
	compare(reg.a, (*memory)[reg.pc+1]);
	// pc += 2;
}
void Gameboy_Cpu::opc_cp_a_p_hl() {
	compare(reg.a, (*memory)[reg.hl]);
	// pc += 2;
}

// calling subroutine

void Gameboy_Cpu::opc_call_nn() {
	call_subroutine(((*memory)[reg.pc+2] << 8) | (*memory)[reg.pc+1]);
}
void Gameboy_Cpu::opc_call_nz_nn() {
	if (!get_flag(ZERO)) {
		call_subroutine(((*memory)[reg.pc+2] << 8) | (*memory)[reg.pc+1]);
		// m_cycles += 12;
	}
}
void Gameboy_Cpu::opc_call_nc_nn() {
	if (!get_flag(CARRY)) {
		call_subroutine(((*memory)[reg.pc+2] << 8) | (*memory)[reg.pc+1]);
		// m_cycles += 12;
	}
}
void Gameboy_Cpu::opc_call_z_nn() {
	if (get_flag(ZERO)) {
		call_subroutine(((*memory)[reg.pc+2] << 8) | (*memory)[reg.pc+1]);
		// m_cycles += 12;
	}
}
void Gameboy_Cpu::opc_call_c_nn() {
	if (get_flag(CARRY)) {
		call_subroutine(((*memory)[reg.pc+2] << 8) | (*memory)[reg.pc+1]);
		// m_cycles += 12;
	}
}

// return from subroutine

void Gameboy_Cpu::opc_ret() {
	return_subroutine();
}
void Gameboy_Cpu::opc_ret_nz() {
	if (!get_flag(ZERO)) {
		return_subroutine();
		// m_cycles += 12;
	}
}
void Gameboy_Cpu::opc_ret_nc() {
	if (!get_flag(CARRY)) {
		return_subroutine();
		// m_cycles += 12;
	}
}
void Gameboy_Cpu::opc_ret_z() {
	if (get_flag(ZERO)) {
		return_subroutine();
		// m_cycles += 12;
	}
}
void Gameboy_Cpu::opc_ret_n() {
	if (get_flag(CARRY)) {
		return_subroutine();
		// m_cycles += 12;
	}
}

// jumping to address

void Gameboy_Cpu::opc_jump_nn() {
	reg.pc = ((*memory)[reg.pc+2] << 8) | (*memory)[reg.pc+1];
}
void Gameboy_Cpu::opc_jump_nz_nn() {
	if (!get_flag(ZERO)) {
		reg.pc = ((*memory)[reg.pc+2] << 8) | (*memory)[reg.pc+1];
		// m_cycles += 4;
	}
}
void Gameboy_Cpu::opc_jump_nc_nn() {
	if (!get_flag(CARRY)) {
		reg.pc = ((*memory)[reg.pc+2] << 8) | (*memory)[reg.pc+1];
		// m_cycles += 4;
	}
}
void Gameboy_Cpu::opc_jump_z_nn() {
	if (get_flag(ZERO)) {
		reg.pc = ((*memory)[reg.pc+2] << 8) | (*memory)[reg.pc+1];
		// m_cycles += 4;
	}
}
void Gameboy_Cpu::opc_jump_c_nn() {
	if (get_flag(CARRY)) {
		reg.pc = ((*memory)[reg.pc+2] << 8) | (*memory)[reg.pc+1];
		// m_cycles += 4;
	}
}
void Gameboy_Cpu::opc_jump_hl() {
	reg.pc = reg.hl;
}

// RST

void Gameboy_Cpu::opc_rst_0() {
	call_subroutine(0x0000);
}
void Gameboy_Cpu::opc_rst_10() {
	call_subroutine(0x0010);
}
void Gameboy_Cpu::opc_rst_20() {
	call_subroutine(0x0020);
}
void Gameboy_Cpu::opc_rst_30() {
	call_subroutine(0x0030);
}
void Gameboy_Cpu::opc_rst_8() {
	call_subroutine(0x0008);
}
void Gameboy_Cpu::opc_rst_18() {
	call_subroutine(0x0018);
}
void Gameboy_Cpu::opc_rst_28() {
	call_subroutine(0x0028);
}
void Gameboy_Cpu::opc_rst_38() {
	call_subroutine(0x0038);
}


// 2 byte codes:
// test bit

void Gameboy_Cpu::opc_bit_a_0() { test_bit(reg.a, 0); }
void Gameboy_Cpu::opc_bit_a_1() { test_bit(reg.a, 1); }
void Gameboy_Cpu::opc_bit_a_2() { test_bit(reg.a, 2); }
void Gameboy_Cpu::opc_bit_a_3() { test_bit(reg.a, 3); }
void Gameboy_Cpu::opc_bit_a_4() { test_bit(reg.a, 4); }
void Gameboy_Cpu::opc_bit_a_5() { test_bit(reg.a, 5); }
void Gameboy_Cpu::opc_bit_a_6() { test_bit(reg.a, 6); }
void Gameboy_Cpu::opc_bit_a_7() { test_bit(reg.a, 7); }

void Gameboy_Cpu::opc_bit_b_0() { test_bit(reg.b, 0); }
void Gameboy_Cpu::opc_bit_b_1() { test_bit(reg.b, 1); }
void Gameboy_Cpu::opc_bit_b_2() { test_bit(reg.b, 2); }
void Gameboy_Cpu::opc_bit_b_3() { test_bit(reg.b, 3); }
void Gameboy_Cpu::opc_bit_b_4() { test_bit(reg.b, 4); }
void Gameboy_Cpu::opc_bit_b_5() { test_bit(reg.b, 5); }
void Gameboy_Cpu::opc_bit_b_6() { test_bit(reg.b, 6); }
void Gameboy_Cpu::opc_bit_b_7() { test_bit(reg.b, 7); }

void Gameboy_Cpu::opc_bit_c_0() { test_bit(reg.c, 0); }
void Gameboy_Cpu::opc_bit_c_1() { test_bit(reg.c, 1); }
void Gameboy_Cpu::opc_bit_c_2() { test_bit(reg.c, 2); }
void Gameboy_Cpu::opc_bit_c_3() { test_bit(reg.c, 3); }
void Gameboy_Cpu::opc_bit_c_4() { test_bit(reg.c, 4); }
void Gameboy_Cpu::opc_bit_c_5() { test_bit(reg.c, 5); }
void Gameboy_Cpu::opc_bit_c_6() { test_bit(reg.c, 6); }
void Gameboy_Cpu::opc_bit_c_7() { test_bit(reg.c, 7); }

void Gameboy_Cpu::opc_bit_d_0() { test_bit(reg.d, 0); }
void Gameboy_Cpu::opc_bit_d_1() { test_bit(reg.d, 1); }
void Gameboy_Cpu::opc_bit_d_2() { test_bit(reg.d, 2); }
void Gameboy_Cpu::opc_bit_d_3() { test_bit(reg.d, 3); }
void Gameboy_Cpu::opc_bit_d_4() { test_bit(reg.d, 4); }
void Gameboy_Cpu::opc_bit_d_5() { test_bit(reg.d, 5); }
void Gameboy_Cpu::opc_bit_d_6() { test_bit(reg.d, 6); }
void Gameboy_Cpu::opc_bit_d_7() { test_bit(reg.d, 7); }

void Gameboy_Cpu::opc_bit_e_0() { test_bit(reg.e, 0); }
void Gameboy_Cpu::opc_bit_e_1() { test_bit(reg.e, 1); }
void Gameboy_Cpu::opc_bit_e_2() { test_bit(reg.e, 2); }
void Gameboy_Cpu::opc_bit_e_3() { test_bit(reg.e, 3); }
void Gameboy_Cpu::opc_bit_e_4() { test_bit(reg.e, 4); }
void Gameboy_Cpu::opc_bit_e_5() { test_bit(reg.e, 5); }
void Gameboy_Cpu::opc_bit_e_6() { test_bit(reg.e, 6); }
void Gameboy_Cpu::opc_bit_e_7() { test_bit(reg.e, 7); }

void Gameboy_Cpu::opc_bit_h_0() { test_bit(reg.h, 0); }
void Gameboy_Cpu::opc_bit_h_1() { test_bit(reg.h, 1); }
void Gameboy_Cpu::opc_bit_h_2() { test_bit(reg.h, 2); }
void Gameboy_Cpu::opc_bit_h_3() { test_bit(reg.h, 3); }
void Gameboy_Cpu::opc_bit_h_4() { test_bit(reg.h, 4); }
void Gameboy_Cpu::opc_bit_h_5() { test_bit(reg.h, 5); }
void Gameboy_Cpu::opc_bit_h_6() { test_bit(reg.h, 6); }
void Gameboy_Cpu::opc_bit_h_7() { test_bit(reg.h, 7); }

void Gameboy_Cpu::opc_bit_l_0() { test_bit(reg.l, 0); }
void Gameboy_Cpu::opc_bit_l_1() { test_bit(reg.l, 1); }
void Gameboy_Cpu::opc_bit_l_2() { test_bit(reg.l, 2); }
void Gameboy_Cpu::opc_bit_l_3() { test_bit(reg.l, 3); }
void Gameboy_Cpu::opc_bit_l_4() { test_bit(reg.l, 4); }
void Gameboy_Cpu::opc_bit_l_5() { test_bit(reg.l, 5); }
void Gameboy_Cpu::opc_bit_l_6() { test_bit(reg.l, 6); }
void Gameboy_Cpu::opc_bit_l_7() { test_bit(reg.l, 7); }

void Gameboy_Cpu::opc_bit_p_hl_0() { test_bit16(reg.hl, 0); }
void Gameboy_Cpu::opc_bit_p_hl_1() { test_bit16(reg.hl, 1); }
void Gameboy_Cpu::opc_bit_p_hl_2() { test_bit16(reg.hl, 2); }
void Gameboy_Cpu::opc_bit_p_hl_3() { test_bit16(reg.hl, 3); }
void Gameboy_Cpu::opc_bit_p_hl_4() { test_bit16(reg.hl, 4); }
void Gameboy_Cpu::opc_bit_p_hl_5() { test_bit16(reg.hl, 5); }
void Gameboy_Cpu::opc_bit_p_hl_6() { test_bit16(reg.hl, 6); }
void Gameboy_Cpu::opc_bit_p_hl_7() { test_bit16(reg.hl, 7); }

// set bits

void Gameboy_Cpu::opc_set_a_0() { set_bit(reg.a, 0); }
void Gameboy_Cpu::opc_set_a_1() { set_bit(reg.a, 1); }
void Gameboy_Cpu::opc_set_a_2() { set_bit(reg.a, 2); }
void Gameboy_Cpu::opc_set_a_3() { set_bit(reg.a, 3); }
void Gameboy_Cpu::opc_set_a_4() { set_bit(reg.a, 4); }
void Gameboy_Cpu::opc_set_a_5() { set_bit(reg.a, 5); }
void Gameboy_Cpu::opc_set_a_6() { set_bit(reg.a, 6); }
void Gameboy_Cpu::opc_set_a_7() { set_bit(reg.a, 7); }

void Gameboy_Cpu::opc_set_b_0() { set_bit(reg.b, 0); }
void Gameboy_Cpu::opc_set_b_1() { set_bit(reg.b, 1); }
void Gameboy_Cpu::opc_set_b_2() { set_bit(reg.b, 2); }
void Gameboy_Cpu::opc_set_b_3() { set_bit(reg.b, 3); }
void Gameboy_Cpu::opc_set_b_4() { set_bit(reg.b, 4); }
void Gameboy_Cpu::opc_set_b_5() { set_bit(reg.b, 5); }
void Gameboy_Cpu::opc_set_b_6() { set_bit(reg.b, 6); }
void Gameboy_Cpu::opc_set_b_7() { set_bit(reg.b, 7); }

void Gameboy_Cpu::opc_set_c_0() { set_bit(reg.c, 0); }
void Gameboy_Cpu::opc_set_c_1() { set_bit(reg.c, 1); }
void Gameboy_Cpu::opc_set_c_2() { set_bit(reg.c, 2); }
void Gameboy_Cpu::opc_set_c_3() { set_bit(reg.c, 3); }
void Gameboy_Cpu::opc_set_c_4() { set_bit(reg.c, 4); }
void Gameboy_Cpu::opc_set_c_5() { set_bit(reg.c, 5); }
void Gameboy_Cpu::opc_set_c_6() { set_bit(reg.c, 6); }
void Gameboy_Cpu::opc_set_c_7() { set_bit(reg.c, 7); }

void Gameboy_Cpu::opc_set_d_0() { set_bit(reg.d, 0); }
void Gameboy_Cpu::opc_set_d_1() { set_bit(reg.d, 1); }
void Gameboy_Cpu::opc_set_d_2() { set_bit(reg.d, 2); }
void Gameboy_Cpu::opc_set_d_3() { set_bit(reg.d, 3); }
void Gameboy_Cpu::opc_set_d_4() { set_bit(reg.d, 4); }
void Gameboy_Cpu::opc_set_d_5() { set_bit(reg.d, 5); }
void Gameboy_Cpu::opc_set_d_6() { set_bit(reg.d, 6); }
void Gameboy_Cpu::opc_set_d_7() { set_bit(reg.d, 7); }

void Gameboy_Cpu::opc_set_e_0() { set_bit(reg.e, 0); }
void Gameboy_Cpu::opc_set_e_1() { set_bit(reg.e, 1); }
void Gameboy_Cpu::opc_set_e_2() { set_bit(reg.e, 2); }
void Gameboy_Cpu::opc_set_e_3() { set_bit(reg.e, 3); }
void Gameboy_Cpu::opc_set_e_4() { set_bit(reg.e, 4); }
void Gameboy_Cpu::opc_set_e_5() { set_bit(reg.e, 5); }
void Gameboy_Cpu::opc_set_e_6() { set_bit(reg.e, 6); }
void Gameboy_Cpu::opc_set_e_7() { set_bit(reg.e, 7); }

void Gameboy_Cpu::opc_set_h_0() { set_bit(reg.h, 0); }
void Gameboy_Cpu::opc_set_h_1() { set_bit(reg.h, 1); }
void Gameboy_Cpu::opc_set_h_2() { set_bit(reg.h, 2); }
void Gameboy_Cpu::opc_set_h_3() { set_bit(reg.h, 3); }
void Gameboy_Cpu::opc_set_h_4() { set_bit(reg.h, 4); }
void Gameboy_Cpu::opc_set_h_5() { set_bit(reg.h, 5); }
void Gameboy_Cpu::opc_set_h_6() { set_bit(reg.h, 6); }
void Gameboy_Cpu::opc_set_h_7() { set_bit(reg.h, 7); }

void Gameboy_Cpu::opc_set_l_0() { set_bit(reg.l, 0); }
void Gameboy_Cpu::opc_set_l_1() { set_bit(reg.l, 1); }
void Gameboy_Cpu::opc_set_l_2() { set_bit(reg.l, 2); }
void Gameboy_Cpu::opc_set_l_3() { set_bit(reg.l, 3); }
void Gameboy_Cpu::opc_set_l_4() { set_bit(reg.l, 4); }
void Gameboy_Cpu::opc_set_l_5() { set_bit(reg.l, 5); }
void Gameboy_Cpu::opc_set_l_6() { set_bit(reg.l, 6); }
void Gameboy_Cpu::opc_set_l_7() { set_bit(reg.l, 7); }

void Gameboy_Cpu::opc_set_p_hl_0() { set_bit16(reg.hl, 0); }
void Gameboy_Cpu::opc_set_p_hl_1() { set_bit16(reg.hl, 1); }
void Gameboy_Cpu::opc_set_p_hl_2() { set_bit16(reg.hl, 2); }
void Gameboy_Cpu::opc_set_p_hl_3() { set_bit16(reg.hl, 3); }
void Gameboy_Cpu::opc_set_p_hl_4() { set_bit16(reg.hl, 4); }
void Gameboy_Cpu::opc_set_p_hl_5() { set_bit16(reg.hl, 5); }
void Gameboy_Cpu::opc_set_p_hl_6() { set_bit16(reg.hl, 6); }
void Gameboy_Cpu::opc_set_p_hl_7() { set_bit16(reg.hl, 7); }

// reset bits

void Gameboy_Cpu::opc_reset_a_0() { reset_bit(reg.a, 0); }
void Gameboy_Cpu::opc_reset_a_1() { reset_bit(reg.a, 1); }
void Gameboy_Cpu::opc_reset_a_2() { reset_bit(reg.a, 2); }
void Gameboy_Cpu::opc_reset_a_3() { reset_bit(reg.a, 3); }
void Gameboy_Cpu::opc_reset_a_4() { reset_bit(reg.a, 4); }
void Gameboy_Cpu::opc_reset_a_5() { reset_bit(reg.a, 5); }
void Gameboy_Cpu::opc_reset_a_6() { reset_bit(reg.a, 6); }
void Gameboy_Cpu::opc_reset_a_7() { reset_bit(reg.a, 7); }

void Gameboy_Cpu::opc_reset_b_0() { reset_bit(reg.b, 0); }
void Gameboy_Cpu::opc_reset_b_1() { reset_bit(reg.b, 1); }
void Gameboy_Cpu::opc_reset_b_2() { reset_bit(reg.b, 2); }
void Gameboy_Cpu::opc_reset_b_3() { reset_bit(reg.b, 3); }
void Gameboy_Cpu::opc_reset_b_4() { reset_bit(reg.b, 4); }
void Gameboy_Cpu::opc_reset_b_5() { reset_bit(reg.b, 5); }
void Gameboy_Cpu::opc_reset_b_6() { reset_bit(reg.b, 6); }
void Gameboy_Cpu::opc_reset_b_7() { reset_bit(reg.b, 7); }

void Gameboy_Cpu::opc_reset_c_0() { reset_bit(reg.c, 0); }
void Gameboy_Cpu::opc_reset_c_1() { reset_bit(reg.c, 1); }
void Gameboy_Cpu::opc_reset_c_2() { reset_bit(reg.c, 2); }
void Gameboy_Cpu::opc_reset_c_3() { reset_bit(reg.c, 3); }
void Gameboy_Cpu::opc_reset_c_4() { reset_bit(reg.c, 4); }
void Gameboy_Cpu::opc_reset_c_5() { reset_bit(reg.c, 5); }
void Gameboy_Cpu::opc_reset_c_6() { reset_bit(reg.c, 6); }
void Gameboy_Cpu::opc_reset_c_7() { reset_bit(reg.c, 7); }

void Gameboy_Cpu::opc_reset_d_0() { reset_bit(reg.d, 0); }
void Gameboy_Cpu::opc_reset_d_1() { reset_bit(reg.d, 1); }
void Gameboy_Cpu::opc_reset_d_2() { reset_bit(reg.d, 2); }
void Gameboy_Cpu::opc_reset_d_3() { reset_bit(reg.d, 3); }
void Gameboy_Cpu::opc_reset_d_4() { reset_bit(reg.d, 4); }
void Gameboy_Cpu::opc_reset_d_5() { reset_bit(reg.d, 5); }
void Gameboy_Cpu::opc_reset_d_6() { reset_bit(reg.d, 6); }
void Gameboy_Cpu::opc_reset_d_7() { reset_bit(reg.d, 7); }

void Gameboy_Cpu::opc_reset_e_0() { reset_bit(reg.e, 0); }
void Gameboy_Cpu::opc_reset_e_1() { reset_bit(reg.e, 1); }
void Gameboy_Cpu::opc_reset_e_2() { reset_bit(reg.e, 2); }
void Gameboy_Cpu::opc_reset_e_3() { reset_bit(reg.e, 3); }
void Gameboy_Cpu::opc_reset_e_4() { reset_bit(reg.e, 4); }
void Gameboy_Cpu::opc_reset_e_5() { reset_bit(reg.e, 5); }
void Gameboy_Cpu::opc_reset_e_6() { reset_bit(reg.e, 6); }
void Gameboy_Cpu::opc_reset_e_7() { reset_bit(reg.e, 7); }

void Gameboy_Cpu::opc_reset_h_0() { reset_bit(reg.h, 0); }
void Gameboy_Cpu::opc_reset_h_1() { reset_bit(reg.h, 1); }
void Gameboy_Cpu::opc_reset_h_2() { reset_bit(reg.h, 2); }
void Gameboy_Cpu::opc_reset_h_3() { reset_bit(reg.h, 3); }
void Gameboy_Cpu::opc_reset_h_4() { reset_bit(reg.h, 4); }
void Gameboy_Cpu::opc_reset_h_5() { reset_bit(reg.h, 5); }
void Gameboy_Cpu::opc_reset_h_6() { reset_bit(reg.h, 6); }
void Gameboy_Cpu::opc_reset_h_7() { reset_bit(reg.h, 7); }

void Gameboy_Cpu::opc_reset_l_0() { reset_bit(reg.l, 0); }
void Gameboy_Cpu::opc_reset_l_1() { reset_bit(reg.l, 1); }
void Gameboy_Cpu::opc_reset_l_2() { reset_bit(reg.l, 2); }
void Gameboy_Cpu::opc_reset_l_3() { reset_bit(reg.l, 3); }
void Gameboy_Cpu::opc_reset_l_4() { reset_bit(reg.l, 4); }
void Gameboy_Cpu::opc_reset_l_5() { reset_bit(reg.l, 5); }
void Gameboy_Cpu::opc_reset_l_6() { reset_bit(reg.l, 6); }
void Gameboy_Cpu::opc_reset_l_7() { reset_bit(reg.l, 7); }

void Gameboy_Cpu::opc_reset_p_hl_0() { reset_bit16(reg.hl, 0); }
void Gameboy_Cpu::opc_reset_p_hl_1() { reset_bit16(reg.hl, 1); }
void Gameboy_Cpu::opc_reset_p_hl_2() { reset_bit16(reg.hl, 2); }
void Gameboy_Cpu::opc_reset_p_hl_3() { reset_bit16(reg.hl, 3); }
void Gameboy_Cpu::opc_reset_p_hl_4() { reset_bit16(reg.hl, 4); }
void Gameboy_Cpu::opc_reset_p_hl_5() { reset_bit16(reg.hl, 5); }
void Gameboy_Cpu::opc_reset_p_hl_6() { reset_bit16(reg.hl, 6); }
void Gameboy_Cpu::opc_reset_p_hl_7() { reset_bit16(reg.hl, 7); }


// bitshift right

void Gameboy_Cpu::opc_srl_a() {
	shift_right(reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_srl_b() {
	shift_right(reg.b);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_srl_c() {
	shift_right(reg.c);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_srl_d() {
	shift_right(reg.d);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_srl_e() {
	shift_right(reg.e);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_srl_h() {
	shift_right(reg.h);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_srl_l() {
	shift_right(reg.l);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_srl_p_hl() {
	shift_right((*memory)[reg.hl]);
	// ++reg.pc;
}

// bitshift right, preserve sign

void Gameboy_Cpu::opc_sra_a() {
	shift_right_preserve_sign(reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sra_b() {
	shift_right_preserve_sign(reg.b);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sra_c() {
	shift_right_preserve_sign(reg.c);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sra_d() {
	shift_right_preserve_sign(reg.d);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sra_e() {
	shift_right_preserve_sign(reg.e);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sra_h() {
	shift_right_preserve_sign(reg.h);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sra_l() {
	shift_right_preserve_sign(reg.l);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sra_p_hl() {
	shift_right_preserve_sign((*memory)[reg.hl]);
	// ++reg.pc;
}

// bitshift left, preserve sign

void Gameboy_Cpu::opc_sla_a() {
	shift_left_preserve_sign(reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sla_b() {
	shift_left_preserve_sign(reg.b);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sla_c() {
	shift_left_preserve_sign(reg.c);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sla_d() {
	shift_left_preserve_sign(reg.d);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sla_e() {
	shift_left_preserve_sign(reg.e);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sla_h() {
	shift_left_preserve_sign(reg.h);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sla_l() {
	shift_left_preserve_sign(reg.l);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_sla_p_hl() {
	shift_left_preserve_sign((*memory)[reg.hl]);
	// ++reg.pc;
}

// swap nybbles

void Gameboy_Cpu::swap_a() {
	swap(reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::swap_b() {
	swap(reg.b);
	// ++reg.pc;
}
void Gameboy_Cpu::swap_c() {
	swap(reg.c);
	// ++reg.pc;
}
void Gameboy_Cpu::swap_d() {
	swap(reg.d);
	// ++reg.pc;
}
void Gameboy_Cpu::swap_e() {
	swap(reg.e);
	// ++reg.pc;
}
void Gameboy_Cpu::swap_h() {
	swap(reg.h);
	// ++reg.pc;
}
void Gameboy_Cpu::swap_l() {
	swap(reg.l);
	// ++reg.pc;
}
void Gameboy_Cpu::swap_p_hl() {
	swap((*memory)[reg.hl]);
	// ++reg.pc;
}

// rotate right

void Gameboy_Cpu::opc_rr_a() {
	rotate_right(reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rr_b() {
	rotate_right(reg.b);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rr_c() {
	rotate_right(reg.c);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rr_d() {
	rotate_right(reg.d);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rr_e() {
	rotate_right(reg.e);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rr_h() {
	rotate_right(reg.h);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rr_l() {
	rotate_right(reg.l);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rr_p_hl() {
	rotate_right((*memory)[reg.hl]);
	// ++reg.pc;
}

// rotate left

void Gameboy_Cpu::opc_rl_a() {
	rotate_left(reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rl_b() {
	rotate_left(reg.b);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rl_c() {
	rotate_left(reg.c);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rl_d() {
	rotate_left(reg.d);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rl_e() {
	rotate_left(reg.e);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rl_h() {
	rotate_left(reg.h);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rl_l() {
	rotate_left(reg.l);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rl_p_hl() {
	rotate_left((*memory)[reg.hl]);
	// ++reg.pc;
}

// rotate right carry

void Gameboy_Cpu::opc_rrc_a() {
	rotate_right_carry(reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rrc_b() {
	rotate_right_carry(reg.b);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rrc_c() {
	rotate_right_carry(reg.c);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rrc_d() {
	rotate_right_carry(reg.d);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rrc_e() {
	rotate_right_carry(reg.e);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rrc_h() {
	rotate_right_carry(reg.h);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rrc_l() {
	rotate_right_carry(reg.l);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rrc_p_hl() {
	rotate_right_carry((*memory)[reg.hl]);
	// ++reg.pc;
}

// rotate left carry

void Gameboy_Cpu::opc_rlc_a() {
	rotate_left_carry(reg.a);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rlc_b() {
	rotate_left_carry(reg.b);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rlc_c() {
	rotate_left_carry(reg.c);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rlc_d() {
	rotate_left_carry(reg.d);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rlc_e() {
	rotate_left_carry(reg.e);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rlc_h() {
	rotate_left_carry(reg.h);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rlc_l() {
	rotate_left_carry(reg.l);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_rlc_p_hl() {
	rotate_left_carry((*memory)[reg.hl]);
	// ++reg.pc;
}

// push 16bit onto stack

void Gameboy_Cpu::opc_push_bc() {
	push(reg.bc);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_push_de() {
	push(reg.de);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_push_hl() {
	push(reg.hl);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_push_af() {
	push(reg.af);
	// ++reg.pc;
}

// pop 16bit from stack into register

void Gameboy_Cpu::opc_pop_bc() {
	pop(reg.bc);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_pop_de() {
	pop(reg.de);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_pop_hl() {
	pop(reg.hl);
	// ++reg.pc;
}
void Gameboy_Cpu::opc_pop_af() {
	pop(reg.af);
	// ++reg.pc;
}

// load at 0xFF00 + n

// load A from 0xFF00 + n
void Gameboy_Cpu::opc_ldh_a_p_n() {
	reg.a = (*memory)[0xFF00 | (*memory)[reg.pc+1]];
	// pc += 2;
}
// save A at 0xFF00 + n
void Gameboy_Cpu::opc_ldh_p_n_a() {
	(*memory)[0xFF00 | (*memory)[reg.pc+1]] = reg.a;
	// pc += 2;
}
// save A at 0xFF00 + C
void Gameboy_Cpu::opc_ldh_p_c_a() {
	(*memory)[0xFF00 | reg.c] = reg.a;
	// pc += 2;
}

// MISC:

// save A at nn
void Gameboy_Cpu::opc_ld_p_nn_a() {
	// get nn from memory
	u16 nn = ((*memory)[reg.pc] << 8) | (*memory)[reg.pc+1];
	(*memory)[nn] = reg.a;

	// pc += 3;
}
// save SP at nn
void Gameboy_Cpu::opc_ld_p_nn_sp() {
	// get nn from memory
	u16 nn = ((*memory)[reg.pc] << 8) | (*memory)[reg.pc+1];
	(*memory)[nn] = reg.sp;

	// pc += 3;
}
// copy HL into SP
void Gameboy_Cpu::opc_ld_sp_hl() {
	reg.sp = reg.hl;
	// ++reg.pc;
}
// add signed n to SP, save result in HL
void Gameboy_Cpu::opc_ldhl_sp_n() {
	char n = (*memory)[reg.pc+1];
	reg.hl = reg.sp + n;
	// pc += 2;
}
// clear carry flag
void Gameboy_Cpu::opc_ccf() {
	reset_flag(SUBTRACT);
	reset_flag(HALF_CARRY);

	if (get_flag(CARRY)) {
		reset_flag(CARRY);
	}
	else {
		set_flag(CARRY);
	}
}
// set carry flag
void Gameboy_Cpu::opc_scf() {
	set_flag(CARRY);
	reset_flag(SUBTRACT);
	reset_flag(HALF_CARRY);
	// ++reg.pc;
}
// compliment (logical NOT) on A
void Gameboy_Cpu::opc_cpl() {
	set_flag(SUBTRACT);
	set_flag(HALF_CARRY);
	reg.a = ~reg.a;
	// ++reg.pc;
}

// relative jump by n

void Gameboy_Cpu::opc_jr_n() {
	relative_jump((*memory)[reg.pc+1]);
	// pc += 2;
}
void Gameboy_Cpu::opc_jr_z_n() {
	if (get_flag(ZERO)) {
		relative_jump((*memory)[reg.pc+1]);
		// m_cycles += 4;
	}
	// pc += 2;
}
void Gameboy_Cpu::opc_jr_c_n() {
	if (get_flag(CARRY)) {
		relative_jump((*memory)[reg.pc+1]);
		// m_cycles += 4;
	}
	// pc += 2;
}
void Gameboy_Cpu::opc_jr_nz_n() {
	if (!get_flag(ZERO)) {
		relative_jump((*memory)[reg.pc+1]);
		// m_cycles += 4;
	}
	// pc += 2;
}
void Gameboy_Cpu::opc_jr_nc_n() {
	if (!get_flag(CARRY)) {
		relative_jump((*memory)[reg.pc+1]);
		// m_cycles += 4;
	}
	// pc += 2;
}

// no operation
void Gameboy_Cpu::opc_nop() {
	// ++reg.pc;
}

// stop CPU
void Gameboy_Cpu::opc_stop() {
	running = false;
	// ++reg.pc;
}

//TODO
void Gameboy_Cpu::opc_reti() {}

// call extended opcode
void Gameboy_Cpu::opc_ext() {
	// Fetch opcode
	u8 opcode_id = (*memory)[reg.pc+1];

	try {
		Opcode opcode = extended_opcodes.at(opcode_id);

		// DEBUG BUILD -> log opcode ID, function and steps
/*#ifdef DEBUG_BUILD
		logger.log_time();
		logger.log(" ++++ executing extended opcode #");
		logger.log(std::to_string(count_opcodes-1));
		logger.log(":\nPC      : ");
		logger.log(logger.short_to_hex(reg.pc));
		logger.log("\nSP      : ");
		logger.log(logger.short_to_hex(reg.sp));
		logger.log("\nID      : +");
		logger.log(logger.char_to_hex(opcode_id));
		logger.log("\nCYCLES  : ");
		logger.log(std::to_string(opcode.m_cycles));
		logger.log_line("\n----");

		// fuck, no reflection...gotta revisit this some time later on
		// -> print function name
#endif */

		// Call opcode function
		(this->*opcode.opcode_function)();

		// increment CPU steps
		// m_cycles += opcode.cycles;
	}
	catch (out_of_range) {
		logger.log("ERROR: invalid opcode at: 0x");
		logger.log(logger.short_to_hex(reg.pc));
#ifdef DEBUG_BUILD
		logger.log_line("  #" + std::to_string(count_opcodes));
#endif
	}
	// pc += 2;
}


// helper functions

void Gameboy_Cpu::set_flag(u8 flag) {
	reg.f &= 0xF0;
	switch (flag)
	{
		case 4: reg.f |= 1 << 4; break;
		case 5: reg.f |= 1 << 5; break;
		case 6: reg.f |= 1 << 6; break;
		case 7: reg.f |= 1 << 7; break;
		default: logger.log_line("Error setting flag: invalid flag :" + flag);
	}
}
void Gameboy_Cpu::reset_flag(u8 flag) {
	switch (flag)
	{
		case 4: reg.f &= ~(1 << 4); break;
		case 5: reg.f &= ~(1 << 5); break;
		case 6: reg.f &= ~(1 << 6); break;
		case 7: reg.f &= ~(1 << 7); break;
		default: logger.log_line("Error resetting flag: invalid flag :" + flag);
	}
}
bool Gameboy_Cpu::get_flag(u8 flag) {
	switch (flag)
	{
		case 4: return reg.f & 0x10; break;
		case 5: return reg.f & 0x20; break;
		case 6: return reg.f & 0x40; break;
		case 7: return reg.f & 0x80; break;
		default: logger.log_line("Error getting flag value: invalid flag :" + flag);
			return false;
	}
}
void Gameboy_Cpu::add(u8 &a, u8 b) {
	u16 result = a + b;
	// set carry flag?
	if (result & 0xff00) {
		set_flag(CARRY);
	}
	else {
		reset_flag(CARRY);
	}

	a = (u8) (result & 0xff);

	// set half-carry flag?
	if (((a & 0x0f) + (b & 0x0f)) > 0x0f) {
		set_flag(HALF_CARRY);
	}

	// if A is 0, set 7th bit (Z/S flag) to 1
	if (result == 0) {
		set_flag(ZERO);
	}
	else {
		reset_flag(ZERO);
	}

	// unset subtraction flag
	reset_flag(SUBTRACT);

	// ++reg.pc;
}
void Gameboy_Cpu::add16(u16 &a, u16 b) {
	unsigned int result = a + b;
	// set carry flag?
	if (result & 0xFFFF0000) {
		set_flag(CARRY);
	}
	else {
		reset_flag(CARRY);
	}

	a = (u16) (result & 0xFFFF);

	// set half carry flag?
	if (((a & 0x0f) + (b & 0x0f)) > 0x0f) {
		set_flag(HALF_CARRY);
	}
	else {
		reset_flag(HALF_CARRY);
	}

	if (result == 0) {
		set_flag(ZERO);
	}
	else {
		reset_flag(ZERO);
	}

	reset_flag(SUBTRACT);
}

//TODO: pass this shit by value
void Gameboy_Cpu::inc(u8 &val) {
	if ((val & 0x0f) == 0x0f) {
		set_flag(HALF_CARRY);
	}
	else {
		reset_flag(HALF_CARRY);
	}

	++val;

	if (val) {
		reset_flag(ZERO);
	}
	else {
		set_flag(ZERO);
	}

	reset_flag(SUBTRACT);
}
void Gameboy_Cpu::dec(u8 &val) {
	if (val & 0x0f) {
		reset_flag(HALF_CARRY);
	}
	else {
		set_flag(HALF_CARRY);
	}

	--val;

	if (val) {
		reset_flag(ZERO);
	}
	else {
		set_flag(ZERO);
	}

	set_flag(SUBTRACT);
}
// TODO: check this, not sure about the way this is supposed to work
void Gameboy_Cpu::dec16(u16 &val) {
	if (val & 0x000f) {
		reset_flag(HALF_CARRY);
	}
	else {
		set_flag(HALF_CARRY);
	}

	--val;

	if (val) {
		reset_flag(ZERO);
	}
	else {
		set_flag(ZERO);
	}

	set_flag(SUBTRACT);
}
void Gameboy_Cpu::inc16(u16 &val) {
	if ((val & 0x000f) == 0x000f) {
		set_flag(HALF_CARRY);
	}
	else {
		reset_flag(HALF_CARRY);
	}

	++val;

	if (val) {
		reset_flag(ZERO);
	}
	else {
		set_flag(ZERO);
	}

	reset_flag(ZERO);
}

void Gameboy_Cpu::adc(u8 &a, u8 b) {
	// add values
	add(a, b + get_flag(CARRY));
}

void Gameboy_Cpu::sub(u8 &a, u8 b) {
	// set carry flag
	if (b > a) {
		set_flag(CARRY);
	}
	else {
		reset_flag(CARRY);
	}

	// set half carry flag
	if ((b & 0x0f) > (a & 0x0f)) {
		set_flag(HALF_CARRY);
	}
	else {
		reset_flag(HALF_CARRY);
	}

	// compute and store result
	a -= b;

	// set zero flag
	if (a == 0) {
		set_flag(ZERO);
	}
	else {
		reset_flag(ZERO);
	}

	// set subtract flag
	set_flag(SUBTRACT);
}

void Gameboy_Cpu::sbc(u8 &a, u8 b) {
	 sub(a, b+get_flag(CARRY));
}

void Gameboy_Cpu::logical_and(u8 &a, u8 b) {
	reset_flag(CARRY);
	reset_flag(SUBTRACT);
	set_flag(HALF_CARRY);

	a &= b;
	if (a == 0) {
		set_flag(ZERO);
	}
	else {
		reset_flag(ZERO);
	}
}

void Gameboy_Cpu::logical_or(u8 &a, u8 b) {
	reset_flag(CARRY);
	reset_flag(HALF_CARRY);
	reset_flag(SUBTRACT);

	a |= b;
	if (a == 0) {
		set_flag(ZERO);
	}
	else {
		reset_flag(ZERO);
	}
}
void Gameboy_Cpu::logical_xor(u8 &a, u8 b) {
	reset_flag(CARRY);
	reset_flag(HALF_CARRY);
	reset_flag(SUBTRACT);

	a ^= b;
	if (a == 0) {
		set_flag(ZERO);
	}
	else {
		reset_flag(ZERO);
	}
}

void Gameboy_Cpu::compare(u8 a, u8 b) {
	// zero flag, equality?
	if (a == b) {
		set_flag(ZERO);
	}
	else {
		reset_flag(ZERO);
	}

	if (b > a) {
		set_flag(CARRY);
	}
	else {
		reset_flag(CARRY);
	}

	// half carry flag
	if ((b & 0x0f) > (a & 0x0f)) {
		set_flag(HALF_CARRY);
	}
	else {
		reset_flag(HALF_CARRY);
	}
	// subtract flag (why the fuck...)
	set_flag(SUBTRACT);
}

void Gameboy_Cpu::call_subroutine(u16 address) {
	// save position in stack
	reg.sp -= 2;
	(*memory)[reg.sp] = reg.pc >> 8;
	(*memory)[reg.sp+1] = reg.pc;

	reg.pc = address;
}

void Gameboy_Cpu::return_subroutine() {
	reg.pc = ((*memory)[reg.sp] << 8) | (*memory)[reg.sp+1];
	reg.sp += 2;
	//TODO: cinoop doesn't do this...check this
	// pc += 3;
}
void Gameboy_Cpu::test_bit(u8 &reg, u8 bit) {
	bool result = reg & (1 << bit);

	if (!result) {
		set_flag(ZERO);
	}
	else {
		reset_flag(ZERO);
	}

	reset_flag(SUBTRACT);
	set_flag(HALF_CARRY);
}
void Gameboy_Cpu::test_bit16(u16 &reg, u8 bit) {
	bool result = reg & (1 << bit);

	if (!result) {
		set_flag(ZERO);
	}
	else {
		reset_flag(ZERO);
	}

	reset_flag(SUBTRACT);
	set_flag(HALF_CARRY);
}

void Gameboy_Cpu::set_bit(u8 &reg, u8 bit) {
	reg |= 1 << bit;
}
void Gameboy_Cpu::set_bit16(u16 &reg, u8 bit) {
	reg |= 1 << bit;
}
void Gameboy_Cpu::reset_bit(u8 &reg, u8 bit) {
	reg &= ~(1 << bit);
}
void Gameboy_Cpu::reset_bit16(u16 &reg, u8 bit) {
	reg &= ~(1 << bit);
}

void Gameboy_Cpu::shift_right(u8 &reg) {
	reset_flag(HALF_CARRY);
	reset_flag(SUBTRACT);

	// if least bit is 1 - set carry flag
	if (reg & 0x01) {
		set_flag(CARRY);
	}
	else {
		reset_flag(CARRY);
	}

	reg >>= 1;

	if (!reg) {
		set_flag(ZERO);
	}
	else {
		reset_flag(ZERO);
	}
}
void Gameboy_Cpu::shift_right_preserve_sign(u8 &reg) {
	reset_flag(HALF_CARRY);
	reset_flag(SUBTRACT);

	// if least bit is 1 - set carry flag
	if (reg & 0x01) {
		set_flag(CARRY);
	}
	else {
		reset_flag(CARRY);
	}

	reg = (reg & 0x80) | (reg >> 1);
	reg >>= 1;

	if (!reg) {
		set_flag(ZERO);
	}
	else {
		reset_flag(ZERO);
	}
}
void Gameboy_Cpu::shift_left_preserve_sign(u8 &reg) {
	reset_flag(HALF_CARRY);
	reset_flag(SUBTRACT);

	if (reg & 0x80) {
		set_flag(CARRY);
	}
	else {
		reset_flag(CARRY);
	}

	reg <<= 1;

	if (!reg) {
		set_flag(ZERO);
	}
	else {
		reset_flag(ZERO);
	}
}

void Gameboy_Cpu::swap(u8 &reg) {
	reset_flag(CARRY);
	reset_flag(HALF_CARRY);
	reset_flag(SUBTRACT);

	// copy right nybble
	u8 original = reg & 0x0F;
	// shift right to left nybble
	original <<= 4;

	// shift left to right nybble
	reg >>= 4;

	// OR / combine both
	reg |= original;

	if (!reg) {
		set_flag(ZERO);
	}
	else {
		reset_flag(ZERO);
	}
}

void Gameboy_Cpu::rotate_right(u8 &reg) {
	reset_flag(SUBTRACT);
	reset_flag(HALF_CARRY);

	reg >>= 1;

	// if carry flag is set, set 7th bit
	if (get_flag(CARRY)) {
		reg |= 0x80;
	}

	if (!reg) {
		set_flag(ZERO);
	}
	else {
		reset_flag(ZERO);
	}
}
void Gameboy_Cpu::rotate_left(u8 &reg) {
	reset_flag(SUBTRACT);
	reset_flag(HALF_CARRY);

	reg <<= 1;

	// if carry flag is set, set bit 0th bit
	if (get_flag(CARRY)) {
		reg |= 0x01;
	}

	if (!reg) {
		set_flag(ZERO);
	}
	else {
		reset_flag(ZERO);
	}
}
void Gameboy_Cpu::rotate_right_carry(u8 &reg) {
	reset_flag(SUBTRACT);
	reset_flag(HALF_CARRY);

	// get 0th bit
	u8 carry = reg & 0x01;

	reg >>= 1;

	if (carry) {
		set_flag(CARRY);
		reg |= 0x80;
	}
	else {
		reset_flag(CARRY);
	}


	if (!reg) {
		set_flag(ZERO);
	}
	else {
		reset_flag(ZERO);
	}
}
void Gameboy_Cpu::rotate_left_carry(u8 &reg) {
	reset_flag(SUBTRACT);
	reset_flag(HALF_CARRY);

	// get 7th bit
	u8 carry = (reg & 0x80) >> 7;

	reg <<= 1;

	if (carry) {
		set_flag(CARRY);
		reg |= 0x01;
	}
	else {
		reset_flag(CARRY);
	}

	if (!reg) {
		set_flag(ZERO);
	}
	else {
		reset_flag(ZERO);
	}
}

void Gameboy_Cpu::push(u16 value) {
	reg.sp -= 2;
	(*memory)[reg.sp] = value >> 8;
	(*memory)[reg.sp+1] = value;
}

void Gameboy_Cpu::pop(u16 &_reg) {
	_reg = ((*memory)[reg.sp] << 8) | (*memory)[reg.sp+1];
	reg.sp += 2;
}

void Gameboy_Cpu::relative_jump(char value) {
	reg.pc += value;
}

Gameboy_Cpu::Gameboy_Cpu() { }