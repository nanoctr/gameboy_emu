//
// Created by michi on 13.06.16.
//

#include "Gameboy_Debugger.h"

//const u8 Gameboy_Debugger::REG_NUMBER = 13;
constexpr u8 Gameboy_Debugger::REG_PC = 0;
constexpr u8 Gameboy_Debugger::REG_SP = 1;
constexpr u8 Gameboy_Debugger::REG_A  = 2;
constexpr u8 Gameboy_Debugger::REG_B  = 3;
constexpr u8 Gameboy_Debugger::REG_C  = 4;
constexpr u8 Gameboy_Debugger::REG_D  = 5;
constexpr u8 Gameboy_Debugger::REG_E  = 6;
constexpr u8 Gameboy_Debugger::REG_H  = 7;
constexpr u8 Gameboy_Debugger::REG_L  = 8;
constexpr u8 Gameboy_Debugger::REG_AF = 9;
constexpr u8 Gameboy_Debugger::REG_BC = 10;
constexpr u8 Gameboy_Debugger::REG_DE = 11;
constexpr u8 Gameboy_Debugger::REG_HL = 12;

// list of all function names

const unordered_map<u8, string> Gameboy_Debugger::opc_function_names = {
		{0x3E, "ld_a_n"},
		{0x06, "ld_b_n"},
		{0x0E, "ld_c_n"},
		{0x16, "ld_d_n"},
		{0x1E, "ld_e_n"},
		{0x26, "ld_h_n"},
		{0x2E, "ld_l_n"},
		{0x01, "ld_bc_nn"},
		{0x11, "ld_de_nn"},
		{0x21, "ld_hl_nn"},
		{0x31, "ld_sp_nn"},
		{0x36, "ld_p_hl_n"},
		{0x78, "ld_a_b"},
		{0x79, "ld_a_c"},
		{0x7A, "ld_a_d"},
		{0x7B, "ld_a_e"},
		{0x7C, "ld_a_h"},
		{0x7D, "ld_a_l"},
		{0x7E, "ld_a_p_hl"},
		{0x7F, "ld_a_a"},
		{0x0A, "ld_a_p_bc"},
		{0x1A, "ld_a_p_de"},
		{0xFA, "ld_a_p_nn"},
		{0x47, "ld_b_a"},
		{0x40, "ld_b_b"},
		{0x41, "ld_b_c"},
		{0x42, "ld_b_d"},
		{0x43, "ld_b_e"},
		{0x44, "ld_b_h"},
		{0x45, "ld_b_l"},
		{0x46, "ld_b_p_hl"},
		{0x4F, "ld_c_a"},
		{0x48, "ld_c_b"},
		{0x49, "ld_c_c"},
		{0x4A, "ld_c_d"},
		{0x4B, "ld_c_e"},
		{0x4C, "ld_c_h"},
		{0x4D, "ld_c_l"},
		{0x4E, "ld_c_p_hl"},
		{0x57, "ld_d_a"},
		{0x50, "ld_d_b"},
		{0x51, "ld_d_c"},
		{0x52, "ld_d_d"},
		{0x53, "ld_d_e"},
		{0x54, "ld_d_h"},
		{0x55, "ld_d_l"},
		{0x56, "ld_d_p_hl"},
		{0x5F, "ld_e_a"},
		{0x58, "ld_e_b"},
		{0x59, "ld_e_c"},
		{0x5A, "ld_e_d"},
		{0x5B, "ld_e_e"},
		{0x5C, "ld_e_h"},
		{0x5D, "ld_e_l"},
		{0x5E, "ld_e_p_hl"},
		{0x67, "ld_h_a"},
		{0x60, "ld_h_b"},
		{0x61, "ld_h_c"},
		{0x62, "ld_h_d"},
		{0x63, "ld_h_e"},
		{0x64, "ld_h_h"},
		{0x65, "ld_h_l"},
		{0x66, "ld_h_p_hl"},
		{0x6F, "ld_l_a"},
		{0x68, "ld_l_b"},
		{0x69, "ld_l_c"},
		{0x6A, "ld_l_d"},
		{0x6B, "ld_l_e"},
		{0x6C, "ld_l_h"},
		{0x6D, "ld_l_l"},
		{0x6E, "ld_l_p_hl"},
		{0x77, "ld_p_hl_a"},
		{0x70, "ld_p_hl_b"},
		{0x71, "ld_p_hl_c"},
		{0x72, "ld_p_hl_d"},
		{0x73, "ld_p_hl_e"},
		{0x74, "ld_p_hl_h"},
		{0x75, "ld_p_hl_l"},
		{0x02, "ld_p_bc_a"},
		{0x12, "ld_p_de_a"},
		{0x22, "ldi_hl_a"},
		{0x32, "ldd_hl_a"},
		{0x2A, "ldi_a_hl"},
		{0x3A, "ldd_a_hl"},
		{0x3C, "inc_a"},
		{0x04, "inc_b"},
		{0x0C, "inc_c"},
		{0x14, "inc_d"},
		{0x1C, "inc_e"},
		{0x24, "inc_h"},
		{0x2C, "inc_l"},
		{0x03, "inc_bc"},
		{0x13, "inc_de"},
		{0x23, "inc_hl"},
		{0x34, "inc_sp"},
		{0x34, "inc_p_hl"},
		{0x3D, "dec_a"},
		{0x05, "dec_b"},
		{0x0C, "dec_c"},
		{0x15, "dec_d"},
		{0x1D, "dec_e"},
		{0x25, "dec_h"},
		{0x2D, "dec_l"},
		{0x0B, "dec_bc"},
		{0x1B, "dec_de"},
		{0x2B, "dec_hl"},
		{0x3B, "dec_sp"},
		{0x35, "dec_p_hl"},
		{0x87, "add_a_a"},
		{0x80, "add_a_b"},
		{0x81, "add_a_c"},
		{0x82, "add_a_d"},
		{0x83, "add_a_e"},
		{0x84, "add_a_h"},
		{0x85, "add_a_l"},
		{0x86, "add_a_p_hl"},
		{0xC6, "add_a_n"},
		{0xE8, "add_sp_d"},
		{0x29, "add_hl_hl"},
		{0x09, "add_hl_bc"},
		{0x19, "add_hl_de"},
		{0x39, "add_hl_sp"},
		{0x8F, "adc_a_a"},
		{0x88, "adc_a_b"},
		{0x89, "adc_a_c"},
		{0x8A, "adc_a_d"},
		{0x8B, "adc_a_e"},
		{0x8C, "adc_a_h"},
		{0x8D, "adc_a_l"},
		{0x8E, "adc_a_p_hl"},
		{0xCE, "adc_a_n"},
		{0x97, "sub_a_a"},
		{0x90, "sub_a_b"},
		{0x91, "sub_a_c"},
		{0x92, "sub_a_d"},
		{0x93, "sub_a_e"},
		{0x94, "sub_a_h"},
		{0x95, "sub_a_l"},
		{0x96, "sub_a_p_hl"},
		{0xD6, "sub_a_n"},
		{0x9F, "sbc_a_a"},
		{0x98, "sbc_a_b"},
		{0x99, "sbc_a_c"},
		{0x9A, "sbc_a_d"},
		{0x9B, "sbc_a_e"},
		{0x9C, "sbc_a_h"},
		{0x9D, "sbc_a_l"},
		{0xDE, "sbc_a_n"},
		{0x9E, "sbc_a_p_hl"},
		{0xA7, "and_a_a"},
		{0xA0, "and_a_b"},
		{0xA1, "and_a_c"},
		{0xA2, "and_a_d"},
		{0xA3, "and_a_e"},
		{0xA4, "and_a_h"},
		{0xA5, "and_a_l"},
		{0xE6, "and_a_n"},
		{0xA6, "and_a_p_hl"},
		{0xB7, "or_a_a"},
		{0xB0, "or_a_b"},
		{0xB1, "or_a_c"},
		{0xB2, "or_a_d"},
		{0xB3, "or_a_e"},
		{0xB4, "or_a_h"},
		{0xB5, "or_a_l"},
		{0xF6, "or_a_n"},
		{0xB6, "or_a_p_hl"},
		{0xAF, "xor_a_a"},
		{0xA8, "xor_a_b"},
		{0xA9, "xor_a_c"},
		{0xAA, "xor_a_d"},
		{0xAB, "xor_a_e"},
		{0xAC, "xor_a_h"},
		{0xAD, "xor_a_l"},
		{0xEE, "xor_a_n"},
		{0xAE, "xor_a_p_hl"},
		{0xBF, "cp_a_a"},
		{0xB8, "cp_a_b"},
		{0xB9, "cp_a_c"},
		{0xBA, "cp_a_d"},
		{0xBB, "cp_a_e"},
		{0xBC, "cp_a_h"},
		{0xBD, "cp_a_l"},
		{0xBE, "cp_a_p_hl"},
		{0xFE, "cp_a_n"},
		{0xCD, "call_nn"},
		{0xC4, "call_nz_nn"},
		{0xD4, "call_nc_nn"},
		{0xCC, "call_z_nn"},
		{0xDC, "call_c_nn"},
		{0xC9, "ret"},
		{0xC0, "ret_nz"},
		{0xD0, "ret_nc"},
		{0xC8, "ret_z"},
		{0xD8, "ret_n"},
		{0xC3, "jump_nn"},
		{0xC2, "jump_nz_nn"},
		{0xD2, "jump_nc_nn"},
		{0xCA, "jump_z_nn"},
		{0xDA, "jump_c_nn"},
		{0xE9, "jump_hl"},
		{0xC7, "rst_0"},
		{0xD7, "rst_10"},
		{0xE7, "rst_20"},
		{0xF7, "rst_30"},
		{0xCF, "rst_8"},
		{0xDF, "rst_18"},
		{0xEF, "rst_28"},
		{0xFF, "rst_38"},
		{0xC5, "push_bc"},
		{0xD5, "push_de"},
		{0xE5, "push_hl"},
		{0xF5, "push_af"},
		{0xC1, "pop_bc"},
		{0xD1, "pop_de"},
		{0xE1, "pop_hl"},
		{0xF1, "pop_af"},
		{0xF0, "ldh_a_p_n"},
		{0xE0, "ldh_p_n_a"},
		{0xE2, "ldh_p_c_a"},
		{0xEA, "ld_p_nn_a"},
		{0x08, "ld_p_nn_sp"},
		{0xF9, "ld_sp_hl"},
		{0x3F, "ccf"},
		{0x37, "scf"},
		{0x2F, "cpl"},
		{0x18, "jr_n"},
		{0x28, "jr_z_n"},
		{0x38, "jr_c_n"},
		{0x20, "jr_nz_n"},
		{0x30, "jr_nc_n"},
		{0x00, "nop"},
		{0x10, "stop"},
		{0xCB, "ext"}
};
// extended opcodes

const unordered_map<u8, string> Gameboy_Debugger::ext_opc_function_names = {
		{0x47, "bit_a_0"},
		{0x4F, "bit_a_1"},
		{0x57, "bit_a_2"},
		{0x5F, "bit_a_3"},
		{0x67, "bit_a_4"},
		{0x6F, "bit_a_5"},
		{0x77, "bit_a_6"},
		{0x7F, "bit_a_7"},
		{0x40, "bit_b_0"},
		{0x48, "bit_b_1"},
		{0x50, "bit_b_2"},
		{0x58, "bit_b_3"},
		{0x60, "bit_b_4"},
		{0x68, "bit_b_5"},
		{0x70, "bit_b_6"},
		{0x78, "bit_b_7"},
		{0x41, "bit_c_0"},
		{0x49, "bit_c_1"},
		{0x51, "bit_c_2"},
		{0x59, "bit_c_3"},
		{0x61, "bit_c_4"},
		{0x69, "bit_c_5"},
		{0x71, "bit_c_6"},
		{0x79, "bit_c_7"},
		{0x42, "bit_d_0"},
		{0x4A, "bit_d_1"},
		{0x52, "bit_d_2"},
		{0x5A, "bit_d_3"},
		{0x62, "bit_d_4"},
		{0x6A, "bit_d_5"},
		{0x72, "bit_d_6"},
		{0x7A, "bit_d_7"},
		{0x43, "bit_e_0"},
		{0x4B, "bit_e_1"},
		{0x53, "bit_e_2"},
		{0x5B, "bit_e_3"},
		{0x63, "bit_e_4"},
		{0x6B, "bit_e_5"},
		{0x73, "bit_e_6"},
		{0x7B, "bit_e_7"},
		{0x44, "bit_h_0"},
		{0x4C, "bit_h_1"},
		{0x54, "bit_h_2"},
		{0x5C, "bit_h_3"},
		{0x64, "bit_h_4"},
		{0x6C, "bit_h_5"},
		{0x74, "bit_h_6"},
		{0x7C, "bit_h_7"},
		{0x45, "bit_l_0"},
		{0x4D, "bit_l_1"},
		{0x55, "bit_l_2"},
		{0x5D, "bit_l_3"},
		{0x65, "bit_l_4"},
		{0x6D, "bit_l_5"},
		{0x75, "bit_l_6"},
		{0x7D, "bit_l_7"},
		{0x46, "bit_p_hl_0"},
		{0x4E, "bit_p_hl_1"},
		{0x56, "bit_p_hl_2"},
		{0x5E, "bit_p_hl_3"},
		{0x66, "bit_p_hl_4"},
		{0x6E, "bit_p_hl_5"},
		{0x76, "bit_p_hl_6"},
		{0x7E, "bit_p_hl_7"},
		{0xC7, "set_a_0"},
		{0xCF, "set_a_1"},
		{0xD7, "set_a_2"},
		{0xDF, "set_a_3"},
		{0xE7, "set_a_4"},
		{0xEF, "set_a_5"},
		{0xF7, "set_a_6"},
		{0xFF, "set_a_7"},
		{0xC0, "set_b_0"},
		{0xC8, "set_b_1"},
		{0xD0, "set_b_2"},
		{0xD8, "set_b_3"},
		{0xE0, "set_b_4"},
		{0xE8, "set_b_5"},
		{0xF0, "set_b_6"},
		{0xF8, "set_b_7"},
		{0xC1, "set_c_0"},
		{0xC9, "set_c_1"},
		{0xD1, "set_c_2"},
		{0xD9, "set_c_3"},
		{0xE1, "set_c_4"},
		{0xE9, "set_c_5"},
		{0xF1, "set_c_6"},
		{0xF9, "set_c_7"},
		{0xC2, "set_d_0"},
		{0xCA, "set_d_1"},
		{0xD2, "set_d_2"},
		{0xDA, "set_d_3"},
		{0xE2, "set_d_4"},
		{0xEA, "set_d_5"},
		{0xF2, "set_d_6"},
		{0xFA, "set_d_7"},
		{0xC3, "set_e_0"},
		{0xCB, "set_e_1"},
		{0xD3, "set_e_2"},
		{0xDB, "set_e_3"},
		{0xE3, "set_e_4"},
		{0xEB, "set_e_5"},
		{0xF3, "set_e_6"},
		{0xFB, "set_e_7"},
		{0xC4, "set_h_0"},
		{0xCC, "set_h_1"},
		{0xD4, "set_h_2"},
		{0xDC, "set_h_3"},
		{0xE4, "set_h_4"},
		{0xEC, "set_h_5"},
		{0xF4, "set_h_6"},
		{0xFC, "set_h_7"},
		{0xC5, "set_l_0"},
		{0xCD, "set_l_1"},
		{0xD5, "set_l_2"},
		{0xDD, "set_l_3"},
		{0xE5, "set_l_4"},
		{0xED, "set_l_5"},
		{0xF5, "set_l_6"},
		{0xFD, "set_l_7"},
		{0xC6, "set_p_hl_0"},
		{0xCE, "set_p_hl_1"},
		{0xD6, "set_p_hl_2"},
		{0xDE, "set_p_hl_3"},
		{0xE6, "set_p_hl_4"},
		{0xEE, "set_p_hl_5"},
		{0xF6, "set_p_hl_6"},
		{0xFE, "set_p_hl_7"},
		{0x87, "reset_a_0"},
		{0x8F, "reset_a_1"},
		{0x97, "reset_a_2"},
		{0x9F, "reset_a_3"},
		{0xA7, "reset_a_4"},
		{0xAF, "reset_a_5"},
		{0xB7, "reset_a_6"},
		{0xBF, "reset_a_7"},
		{0x80, "reset_b_0"},
		{0x88, "reset_b_1"},
		{0x90, "reset_b_2"},
		{0x98, "reset_b_3"},
		{0xA0, "reset_b_4"},
		{0xA8, "reset_b_5"},
		{0xB0, "reset_b_6"},
		{0xB8, "reset_b_7"},
		{0x81, "reset_c_0"},
		{0x89, "reset_c_1"},
		{0x91, "reset_c_2"},
		{0x99, "reset_c_3"},
		{0xA1, "reset_c_4"},
		{0xA9, "reset_c_5"},
		{0xB1, "reset_c_6"},
		{0xB9, "reset_c_7"},
		{0x82, "reset_d_0"},
		{0x8A, "reset_d_1"},
		{0x92, "reset_d_2"},
		{0x9A, "reset_d_3"},
		{0xA2, "reset_d_4"},
		{0xAA, "reset_d_5"},
		{0xB2, "reset_d_6"},
		{0xBA, "reset_d_7"},
		{0x83, "reset_e_0"},
		{0x8B, "reset_e_1"},
		{0x93, "reset_e_2"},
		{0x9B, "reset_e_3"},
		{0xA3, "reset_e_4"},
		{0xAB, "reset_e_5"},
		{0xB3, "reset_e_6"},
		{0xBB, "reset_e_7"},
		{0x84, "reset_h_0"},
		{0x8C, "reset_h_1"},
		{0x94, "reset_h_2"},
		{0x9C, "reset_h_3"},
		{0xA4, "reset_h_4"},
		{0xAC, "reset_h_5"},
		{0xB4, "reset_h_6"},
		{0xBC, "reset_h_7"},
		{0x85, "reset_l_0"},
		{0x8D, "reset_l_1"},
		{0x95, "reset_l_2"},
		{0x9D, "reset_l_3"},
		{0xA5, "reset_l_4"},
		{0xAD, "reset_l_5"},
		{0xB5, "reset_l_6"},
		{0xBD, "reset_l_7"},
		{0x86, "reset_p_hl_0"},
		{0x8E, "reset_p_hl_1"},
		{0x96, "reset_p_hl_2"},
		{0x9E, "reset_p_hl_3"},
		{0xA6, "reset_p_hl_4"},
		{0xAE, "reset_p_hl_5"},
		{0xB6, "reset_p_hl_6"},
		{0xBE, "reset_p_hl_7"},
		{0x3F, "srl_a"},
		{0x38, "srl_b"},
		{0x39, "srl_c"},
		{0x3A, "srl_d"},
		{0x3B, "srl_e"},
		{0x3C, "srl_h"},
		{0x3D, "srl_l"},
		{0x3E, "srl_p_hl"},
		{0x2F, "sra_a"},
		{0x28, "sra_b"},
		{0x29, "sra_c"},
		{0x2A, "sra_d"},
		{0x2B, "sra_e"},
		{0x2C, "sra_h"},
		{0x2D, "sra_l"},
		{0x2E, "sra_p_hl"},
		{0x27, "sla_a"},
		{0x20, "sla_b"},
		{0x21, "sla_c"},
		{0x22, "sla_d"},
		{0x23, "sla_e"},
		{0x24, "sla_h"},
		{0x25, "sla_l"},
		{0x26, "sla_p_hl"},
		{0x1F, "rr_a"},
		{0x18, "rr_b"},
		{0x19, "rr_c"},
		{0x1A, "rr_d"},
		{0x1B, "rr_e"},
		{0x1C, "rr_h"},
		{0x1D, "rr_l"},
		{0x1E, "rr_p_hl"},
		{0x17, "rl_a"},
		{0x10, "rl_b"},
		{0x11, "rl_c"},
		{0x12, "rl_d"},
		{0x13, "rl_e"},
		{0x14, "rl_h"},
		{0x15, "rl_l"},
		{0x16, "rl_p_hl"},
		{0x0F, "rrc_a"},
		{0x08, "rrc_b"},
		{0x09, "rrc_c"},
		{0x0A, "rrc_d"},
		{0x0B, "rrc_e"},
		{0x0C, "rrc_h"},
		{0x0D, "rrc_l"},
		{0x0E, "rrc_p_hl"},
		{0x07, "rlc_a"},
		{0x00, "rlc_b"},
		{0x01, "rlc_c"},
		{0x02, "rlc_d"},
		{0x03, "rlc_e"},
		{0x04, "rlc_h"},
		{0x05, "rlc_l"},
		{0x06, "rlc_p_hl"},
};

Gameboy_Debugger::Gameboy_Debugger() {
	debug_registers[REG_PC] = Debug_Register(nullptr, &reg.pc, "", "PC");
	debug_registers[REG_SP] = Debug_Register(nullptr, &reg.sp, "", "SP");
	debug_registers[REG_A] = Debug_Register(&reg.a, &reg.af, "A", "AF");
	debug_registers[REG_AF] = Debug_Register(nullptr, &reg.af, "", "AF");
	debug_registers[REG_B] = Debug_Register(&reg.b, &reg.bc, "B", "BC");
	debug_registers[REG_C] = Debug_Register(&reg.c, &reg.bc, "C", "BC");
	debug_registers[REG_BC] = Debug_Register(nullptr, &reg.bc, "", "BC");
	debug_registers[REG_D] = Debug_Register(&reg.d, &reg.de, "D", "DE");
	debug_registers[REG_E] = Debug_Register(&reg.e, &reg.de, "E", "DE");
	debug_registers[REG_DE] = Debug_Register(nullptr, &reg.de, "", "DE");
	debug_registers[REG_H] = Debug_Register(&reg.h, &reg.hl, "H", "HL");
	debug_registers[REG_L] = Debug_Register(&reg.l, &reg.hl, "L", "HL");
	debug_registers[REG_HL] = Debug_Register(nullptr, &reg.hl, "", "HL");

	watch_list[REG_PC] = true;
	watch_list[REG_SP] = true;

	load_breakpoints();
	load_watches();

	// reg.pc = 0;
	cpu.startup();
}

// Main execution loop
void Gameboy_Debugger::run() {
	while(true)
	{
		if (cpu.memory[cpu.reg.pc] == 0xCB) ext = 2;
		else --ext;

		// breakpoint hit, stop execution, show debug interface, next loop when done
		if (is_breakpoint(cpu.reg.pc)) {
			forever = false;
			steps = 0;
			reg = cpu.reg;
			debug_interface();
			continue;
		}

		if (forever) {
			++count_opcodes;
			cpu.emulate_cycle();
		}
		else if (steps) {
			++count_opcodes;
			cpu.emulate_cycle();
			--steps;
		}

		// No 'forever' execution or end of steps to execute -> open debug interface
		else {
			reg = cpu.reg;
			debug_interface();
		}
	}
}

string Gameboy_Debugger::print_opc_function(u8 opc) {
	string result;
	if (ext == 1) {
		result = ext_opc_function_names.at(opc);
	}
	else {
		result = opc_function_names.at(opc);
	}
	result += "\n";
	return result;
}

string Gameboy_Debugger::print_memory(u16 addr) {
	string result = "";
	u8 data = cpu.memory[addr];
	std::bitset<8> bits(data);
	string bit_string = bits.to_string();
	bit_string.insert(4, " ");

	result.append(logger.char_to_hex(data) + "  |  ");
	result.append(bit_string + "  |  ");
	result.append(to_string(data) + "\n");

	return result;
}



void Gameboy_Debugger::debug_outputs() {

	cout << "Opcode #" << count_opcodes << endl;
	cout << "Memory at PC: " << endl;
	cout << print_memory(reg.pc);

	//cout << "Opcode Function: " << opc_function_names.at(cpu.memory[reg.pc]);
	cout << "Opcode Function: " << print_opc_function(cpu.memory[reg.pc]);
	cout << endl << endl;


	cout << "Flags: " << endl;
	cout << "Zero       Subtract   HalfCarry  Carry\n";
	cout << ((reg.f >> 7) & 0x01) << "          ";
	cout << ((reg.f >> 6) & 0x01) << "          ";
	cout << ((reg.f >> 5) & 0x01) << "          ";
	cout << ((reg.f >> 4) & 0x01) << "          " << endl << endl;

	cout << print_registers(watch_list);

}

void Gameboy_Debugger::print_register(u8 value) {
	cout << debug_registers[value].description() << endl;
}

string Gameboy_Debugger::print_registers(bool list[REG_NUMBER]) {
	string result = "REGISTERS: \n";
	for (u8 i = 0; i <= REG_NUMBER; ++i) {
		if (list[i]) {
			result.append(debug_registers[i].description());
		}
	}
	result.append("\n");
	return result;
}

// Debugger main interface: print values, control debugger & code execution
void Gameboy_Debugger::debug_interface() {
	// Print watches and stuff
	debug_outputs();

	string input = "";
	bool stay_debug = true;
	smatch match;
	while (stay_debug) {
		getline(cin, input);

		switch (match_debugger_instr(input, match))
		{
			case DEBUGGER_STEP:  // execute one step
				stay_debug = false;
				steps = 1; break;
			case DEBUGGER_NUMBER:  // execute $NUMBER steps
				stay_debug = false;
				steps = string_to_short(match.str(1)); break;
			case DEBUGGER_CONTINUE: // continue executing
				stay_debug = false;
				forever = true; break;
			case DEBUGGER_NEW_BREAKPOINT: // set new breakpoint
				breakpoints.insert(string_to_short(match.str(1))); break;
			case DEBUGGER_SAVE_BREAKPOINT: // set new breakpoint, store in file
				save_breakpoint(match); break;
			case DEBUGGER_PRINT_REGISTER: // print register value
				print_register(reg_constants.at(match.str(1))); break;
			case DEBUGGER_WATCH_REGISTER: // self-explaining
				print_register(reg_constants.at(match.str(1)));
				watch_list[reg_constants.at(match.str(1))] = true; break;
			case DEBUGGER_PRINT_MEMORY: // print memory value at position
				print_memory(string_to_short(match.str(1))); break;
			case DEBUGGER_PRINT_OUTPUT: // print all output stuff
				debug_outputs(); break;
			default:
				logger.log_line("Invalid Debugger Instruction: " + input);
		}
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
	} // watch a register
	else if (regex_search(input, match, match_watch_save) && match.size() > 1) {
		return DEBUGGER_SAFE_WATCH;
	} // store watch in file
	else if (regex_search(input, match, match_print_register) && match.size() > 1) {
		return DEBUGGER_PRINT_REGISTER;
	} // print register value
	else if (regex_search(input, match, match_print_memory) && match.size() > 1) {
		return DEBUGGER_PRINT_MEMORY;
	} // print value of memory at position
	else if (input[0] == 'a') {
		return DEBUGGER_PRINT_OUTPUT;
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
void Gameboy_Debugger::load_watches() {
	ifstream file(WATCHES_FILE);
	string line;
	smatch match;

	while (getline(file, line)) {
		if (regex_search(line, match, match_watches_data) && match.size() > 1) {
			watch_list[reg_constants.at(match.str(1))] = true;
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