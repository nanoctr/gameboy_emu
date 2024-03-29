//
// Created by michi on 30.05.16.
//

#ifndef GAMEBOY_EMU_GAMEBOY_CPU_H
#define GAMEBOY_EMU_GAMEBOY_CPU_H
// this is a debug build, change this for release compilation
#define DEBUG_BUILD


#include <unordered_map>
#include <vector>
#include "Gameboy_Logger.h"
#include "Gameboy_Registers.h"
#include <memory>

typedef unsigned long u64;

class Gameboy_Display;
class Gameboy_Memory;

class Gameboy_Cpu {
private:

	// counting executed opcodes for debugging, starting at 1
#ifdef DEBUG_BUILD
	unsigned int count_opcodes = 1;
	vector<u16> opcode_list;
#endif


// Opcode struct, stores function pointer, ticks and so on
	struct Opcode
	{
		Opcode(void (Gameboy_Cpu::*opc_func)(), u8 cpu_cycles, u8 opc_length) {
			opcode_function = opc_func;
			cycles = cpu_cycles;
			length = opc_length;
		}
		// Function pointer to opcode function
		void (Gameboy_Cpu::*opcode_function)();
		// Used cpu steps
		u8 cycles;

		// Length in bytes -> increment PC by this value
		u8 length;
	};

// Opcode structs saved in hashmap: Key[opcode_byte] -> Value[Opcode_struct]
	std::unordered_map<u8, Opcode> opcodes;
	std::unordered_map<u8, Opcode> extended_opcodes;

// Cpu Cycle counter
	unsigned long m_cycles;
	unsigned long t_cycles;
	u8 m_opc_cycles;
	u8 t_opc_cycles;


	u8 video_memory[256][256];

	bool running = true; // used for CPU interrupts

	Gameboy_Logger logger = Gameboy_Logger("/tmp/gameboy_cpu.log");


	// populate opcodes hashmaps
	void load_opcodes();
	void load_extended_opcodes();

	// load n into register:

	void opc_ld_a_n(); //0x3E
	void opc_ld_b_n(); //0x06
	void opc_ld_c_n(); //0x0E
	void opc_ld_d_n(); //0x16
	void opc_ld_e_n(); //0x1E
	void opc_ld_h_n(); //0x26
	void opc_ld_l_n(); //0x2E
	void opc_ld_bc_nn(); //0x01
	void opc_ld_de_nn(); //0x11
	void opc_ld_hl_nn(); //0x21
	void opc_ld_sp_nn(); //0x31
	void opc_ld_p_hl_n(); //0x36

	// load r2 into r1:

	void opc_ld_a_b(); //0x78
	void opc_ld_a_c(); //0x79
	void opc_ld_a_d(); //0x7A
	void opc_ld_a_e(); //0x7B
	void opc_ld_a_h(); //0x7C
	void opc_ld_a_l(); //0x7D
	void opc_ld_a_p_hl(); //0x7E
	void opc_ld_a_a(); //0x7F -> NOP
	void opc_ld_a_p_bc(); //0x0A
	void opc_ld_a_p_de(); //0x1A
	void opc_ld_a_p_nn(); //0xFA
	void opc_ld_b_a(); //0x47
	void opc_ld_b_b(); //0x40 -> NOP
	void opc_ld_b_c(); //0x41
	void opc_ld_b_d(); //0x42
	void opc_ld_b_e(); //0x43
	void opc_ld_b_h(); //0x44
	void opc_ld_b_l(); //0x45
	void opc_ld_b_p_hl(); //0x46
	void opc_ld_c_a(); //0x4F
	void opc_ld_c_b(); //0x48
	void opc_ld_c_c(); //0x49 -> NOP
	void opc_ld_c_d(); //0x4A
	void opc_ld_c_e(); //0x4B
	void opc_ld_c_h(); //0x4C
	void opc_ld_c_l(); //0x4D
	void opc_ld_c_p_hl(); //0x4E
	void opc_ld_d_a(); //0x57
	void opc_ld_d_b(); //0x50
	void opc_ld_d_c(); //0x51
	void opc_ld_d_d(); //0x52 -> NOP
	void opc_ld_d_e(); //0x53
	void opc_ld_d_h(); //0x54
	void opc_ld_d_l(); //0x55
	void opc_ld_d_p_hl(); //0x56
	void opc_ld_e_a(); //0x5F
	void opc_ld_e_b(); //0x58
	void opc_ld_e_c(); //0x59
	void opc_ld_e_d(); //0x5A
	void opc_ld_e_e(); //0x5B -> NOP
	void opc_ld_e_h(); //0x5C
	void opc_ld_e_l(); //0x5D
	void opc_ld_e_p_hl(); //0x5E
	void opc_ld_h_a(); //0x67
	void opc_ld_h_b(); //0x60
	void opc_ld_h_c(); //0x61
	void opc_ld_h_d(); //0x62
	void opc_ld_h_e(); //0x63
	void opc_ld_h_h(); //0x64 -> NOP
	void opc_ld_h_l(); //0x65
	void opc_ld_h_p_hl(); //0x66
	void opc_ld_l_a(); //0x6F
	void opc_ld_l_b(); //0x68
	void opc_ld_l_c(); //0x69
	void opc_ld_l_d(); //0x6A
	void opc_ld_l_e(); //0x6B
	void opc_ld_l_h(); //0x6C
	void opc_ld_l_l(); //0x6D -> NOP
	void opc_ld_l_p_hl(); //0x6E
	void opc_ld_p_hl_a(); //0x77
	void opc_ld_p_hl_b(); //0x70
	void opc_ld_p_hl_c(); //0x71
	void opc_ld_p_hl_d(); //0x72
	void opc_ld_p_hl_e(); //0x73
	void opc_ld_p_hl_h(); //0x74
	void opc_ld_p_hl_l(); //0x75
	void opc_ld_p_bc_a(); //0x02
	void opc_ld_p_de_a(); //0x12

	// load + increment

	void opc_ldi_hl_a(); //0x22; save A to memory pointed to by HL, HL += 1
	void opc_ldd_hl_a(); //0x32; save A to memory pointed to by HL, HL -= 1
	void opc_ldi_a_hl(); //0x2A
	void opc_ldd_a_hl(); //0x3A

	// increment registers

	void opc_inc_a(); //0x3C
	void opc_inc_b(); //0x04
	void opc_inc_c(); //0x0C
	void opc_inc_d(); //0x14
	void opc_inc_e(); //0x1C
	void opc_inc_h(); //0x24
	void opc_inc_l(); //0x2C
	void opc_inc_bc(); //0x03
	void opc_inc_de(); //0x13
	void opc_inc_hl(); //0x23
	void opc_inc_sp(); //0x34
	void opc_inc_p_hl(); //0x34

	// decrement registers

	void opc_dec_a(); //0x3D
	void opc_dec_b(); //0x05
	void opc_dec_c(); //0x0C
	void opc_dec_d(); //0x15
	void opc_dec_e(); //0x1D
	void opc_dec_h(); //0x25
	void opc_dec_l(); //0x2D
	void opc_dec_bc(); //0x0B
	void opc_dec_de(); //0x1B
	void opc_dec_hl(); //0x2B
	void opc_dec_sp(); //0x3B
	void opc_dec_p_hl(); //0x35

	// add registers

	void opc_add_a_a(); //0x87
	void opc_add_a_b(); //0x80
	void opc_add_a_c(); //0x81
	void opc_add_a_d(); //0x82
	void opc_add_a_e(); //0x83
	void opc_add_a_h(); //0x84
	void opc_add_a_l(); //0x85
	void opc_add_a_p_hl(); //0x86
	void opc_add_a_n(); //0xC6
	void opc_add_sp_d(); //0xE8

	// add 16 bits

	void opc_add_hl_hl(); //0x29
	void opc_add_hl_bc(); //0x09
	void opc_add_hl_de(); //0x19
	void opc_add_hl_sp(); //0x39

	// add with carry

	void opc_adc_a_a(); //0x8F
	void opc_adc_a_b(); //0x88
	void opc_adc_a_c(); //0x89
	void opc_adc_a_d(); //0x8A
	void opc_adc_a_e(); //0x8B
	void opc_adc_a_h(); //0x8C
	void opc_adc_a_l(); //0x8D
	void opc_adc_a_p_hl(); //0x8E
	void opc_adc_a_n(); //0xCE

	// sub registers

	void opc_sub_a_a(); //0x97
	void opc_sub_a_b(); //0x90
	void opc_sub_a_c(); //0x91
	void opc_sub_a_d(); //0x92
	void opc_sub_a_e(); //0x93
	void opc_sub_a_h(); //0x94
	void opc_sub_a_l(); //0x95
	void opc_sub_a_p_hl(); //0x96
	void opc_sub_a_n(); //0xD6

	// sub with carry

	void opc_sbc_a_a(); //0x9F
	void opc_sbc_a_b(); //0x98
	void opc_sbc_a_c(); //0x99
	void opc_sbc_a_d(); //0x9A
	void opc_sbc_a_e(); //0x9B
	void opc_sbc_a_h(); //0x9C
	void opc_sbc_a_l(); //0x9D
	void opc_sbc_a_n(); //0xDE
	void opc_sbc_a_p_hl(); //0x9E

	// logical AND

	void opc_and_a_a(); //0xA7
	void opc_and_a_b(); //0xA0
	void opc_and_a_c(); //0xA1
	void opc_and_a_d(); //0xA2
	void opc_and_a_e(); //0xA3
	void opc_and_a_h(); //0xA4
	void opc_and_a_l(); //0xA5
	void opc_and_a_n(); //0xE6
	void opc_and_a_p_hl(); //0xA6

	// logical OR

	void opc_or_a_a(); //0xB7
	void opc_or_a_b(); //0xB0
	void opc_or_a_c(); //0xB1
	void opc_or_a_d(); //0xB2
	void opc_or_a_e(); //0xB3
	void opc_or_a_h(); //0xB4
	void opc_or_a_l(); //0xB5
	void opc_or_a_n(); //0xF6
	void opc_or_a_p_hl(); //0xB6

	// logical XOR

	void opc_xor_a_a(); //0xAF
	void opc_xor_a_b(); //0xA8
	void opc_xor_a_c(); //0xA9
	void opc_xor_a_d(); //0xAA
	void opc_xor_a_e(); //0xAB
	void opc_xor_a_h(); //0xAC
	void opc_xor_a_l(); //0xAD
	void opc_xor_a_n(); //0xEE
	void opc_xor_a_p_hl(); //0xAE

	// compare against a

	void opc_cp_a_a(); //0xBF
	void opc_cp_a_b(); //0xB8
	void opc_cp_a_c(); //0xB9
	void opc_cp_a_d(); //0xBA
	void opc_cp_a_e(); //0xBB
	void opc_cp_a_h(); //0xBC
	void opc_cp_a_l(); //0xBD
	void opc_cp_a_p_hl(); //0xBE
	void opc_cp_a_n(); //0xFE

	// calling subroutine

	void opc_call_nn(); // 0xCD - call subroutine at nn
	void opc_call_nz_nn(); //0xC4 - call subroutine if ZERO flag is not set
	void opc_call_nc_nn(); //0xD4 - call subroutine if CARRY flag ist not set
	void opc_call_z_nn(); //0xCC - call subroutine if ZERO flag is set
	void opc_call_c_nn(); //0xDC - call subroutine if CARRY flag is set

	// returning from subroutine

	void opc_ret(); //0xC9
	void opc_ret_nz(); //0xC0 - return if ZERO flag is not set
	void opc_ret_nc(); //0xD0
	void opc_ret_z(); //0xC8
	void opc_ret_n(); //0xD8

	// jumping to address

	void opc_jump_nn(); //0xC3
	void opc_jump_nz_nn(); //0xC2
	void opc_jump_nc_nn(); //0xD2
	void opc_jump_z_nn(); //0xCA
	void opc_jump_c_nn(); //0xDA
	void opc_jump_hl(); //0xE9

	// calling specific address

	void opc_rst_0(); //0xC7
	void opc_rst_10(); //0xD7
	void opc_rst_20(); //0xE7
	void opc_rst_30(); //0xF7
	void opc_rst_8(); //0xCF
	void opc_rst_18(); //0xDF
	void opc_rst_28(); //0xEF
	void opc_rst_38(); //0xFF

	// 2 byte opcodes:

	// check bit at position:

	void opc_bit_a_0();//+0x47
	void opc_bit_a_1();//+0x4F
	void opc_bit_a_2();//+0x57
	void opc_bit_a_3();//+0x5F
	void opc_bit_a_4();//+0x67
	void opc_bit_a_5();//+0x6F
	void opc_bit_a_6();//+0x77
	void opc_bit_a_7();//+0x7F

	void opc_bit_b_0();//+0x40
	void opc_bit_b_1();//+0x48
	void opc_bit_b_2();//+0x50
	void opc_bit_b_3();//+0x58
	void opc_bit_b_4();//+0x60
	void opc_bit_b_5();//+0x68
	void opc_bit_b_6();//+0x70
	void opc_bit_b_7();//+0x78

	void opc_bit_c_0();//+0x41
	void opc_bit_c_1();//+0x49
	void opc_bit_c_2();//+0x51
	void opc_bit_c_3();//+0x59
	void opc_bit_c_4();//+0x61
	void opc_bit_c_5();//+0x69
	void opc_bit_c_6();//+0x71
	void opc_bit_c_7();//+0x79

	void opc_bit_d_0();//+0x42
	void opc_bit_d_1();//+0x4A
	void opc_bit_d_2();//+0x52
	void opc_bit_d_3();//+0x5A
	void opc_bit_d_4();//+0x62
	void opc_bit_d_5();//+0x6A
	void opc_bit_d_6();//+0x72
	void opc_bit_d_7();//+0x7A

	void opc_bit_e_0();//+0x43
	void opc_bit_e_1();//+0x4B
	void opc_bit_e_2();//+0x53
	void opc_bit_e_3();//+0x5B
	void opc_bit_e_4();//+0x63
	void opc_bit_e_5();//+0x6B
	void opc_bit_e_6();//+0x73
	void opc_bit_e_7();//+0x7B

	void opc_bit_h_0();//+0x44
	void opc_bit_h_1();//+0x4C
	void opc_bit_h_2();//+0x54
	void opc_bit_h_3();//+0x5C
	void opc_bit_h_4();//+0x64
	void opc_bit_h_5();//+0x6C
	void opc_bit_h_6();//+0x74
	void opc_bit_h_7();//+0x7C

	void opc_bit_l_0();//+0x45
	void opc_bit_l_1();//+0x4D
	void opc_bit_l_2();//+0x55
	void opc_bit_l_3();//+0x5D
	void opc_bit_l_4();//+0x65
	void opc_bit_l_5();//+0x6D
	void opc_bit_l_6();//+0x75
	void opc_bit_l_7();//+0x7D

	void opc_bit_p_hl_0();//+0x46
	void opc_bit_p_hl_1();//+0x4E
	void opc_bit_p_hl_2();//+0x56
	void opc_bit_p_hl_3();//+0x5E
	void opc_bit_p_hl_4();//+0x66
	void opc_bit_p_hl_5();//+0x6E
	void opc_bit_p_hl_6();//+0x76
	void opc_bit_p_hl_7();//+0x7E

	// set bit at position:

	void opc_set_a_0(); //+0xC7
	void opc_set_a_1(); //+0xCF
	void opc_set_a_2(); //+0xD7
	void opc_set_a_3(); //+0xDF
	void opc_set_a_4(); //+0xE7
	void opc_set_a_5(); //+0xEF
	void opc_set_a_6(); //+0xF7
	void opc_set_a_7(); //+0xFF

	void opc_set_b_0(); //+0xC0
	void opc_set_b_1(); //+0xC8
	void opc_set_b_2(); //+0xD0
	void opc_set_b_3(); //+0xD8
	void opc_set_b_4(); //+0xE0
	void opc_set_b_5(); //+0xE8
	void opc_set_b_6(); //+0xF0
	void opc_set_b_7(); //+0xF8

	void opc_set_c_0(); //+0xC1
	void opc_set_c_1(); //+0xC9
	void opc_set_c_2(); //+0xD1
	void opc_set_c_3(); //+0xD9
	void opc_set_c_4(); //+0xE1
	void opc_set_c_5(); //+0xE9
	void opc_set_c_6(); //+0xF1
	void opc_set_c_7(); //+0xF9

	void opc_set_d_0(); //+0xC2
	void opc_set_d_1(); //+0xCA
	void opc_set_d_2(); //+0xD2
	void opc_set_d_3(); //+0xDA
	void opc_set_d_4(); //+0xE2
	void opc_set_d_5(); //+0xEA
	void opc_set_d_6(); //+0xF2
	void opc_set_d_7(); //+0xFA

	void opc_set_e_0(); //+0xC3
	void opc_set_e_1(); //+0xCB
	void opc_set_e_2(); //+0xD3
	void opc_set_e_3(); //+0xDB
	void opc_set_e_4(); //+0xE3
	void opc_set_e_5(); //+0xEB
	void opc_set_e_6(); //+0xF3
	void opc_set_e_7(); //+0xFB

	void opc_set_h_0(); //+0xC4
	void opc_set_h_1(); //+0xCC
	void opc_set_h_2(); //+0xD4
	void opc_set_h_3(); //+0xDC
	void opc_set_h_4(); //+0xE4
	void opc_set_h_5(); //+0xEC
	void opc_set_h_6(); //+0xF4
	void opc_set_h_7(); //+0xFC

	void opc_set_l_0(); //+0xC5
	void opc_set_l_1(); //+0xCD
	void opc_set_l_2(); //+0xD5
	void opc_set_l_3(); //+0xDD
	void opc_set_l_4(); //+0xE5
	void opc_set_l_5(); //+0xED
	void opc_set_l_6(); //+0xF5
	void opc_set_l_7(); //+0xFD

	void opc_set_p_hl_0(); //+0xC6
	void opc_set_p_hl_1(); //+0xCE
	void opc_set_p_hl_2(); //+0xD6
	void opc_set_p_hl_3(); //+0xDE
	void opc_set_p_hl_4(); //+0xE6
	void opc_set_p_hl_5(); //+0xEE
	void opc_set_p_hl_6(); //+0xF6
	void opc_set_p_hl_7(); //+0xFE

	// reset bit at position:

	void opc_reset_a_0(); //+0x87
	void opc_reset_a_1(); //+0x8F
	void opc_reset_a_2(); //+0x97
	void opc_reset_a_3(); //+0x9F
	void opc_reset_a_4(); //+0xA7
	void opc_reset_a_5(); //+0xAF
	void opc_reset_a_6(); //+0xB7
	void opc_reset_a_7(); //+0xBF

	void opc_reset_b_0(); //+0x80
	void opc_reset_b_1(); //+0x88
	void opc_reset_b_2(); //+0x90
	void opc_reset_b_3(); //+0x98
	void opc_reset_b_4(); //+0xA0
	void opc_reset_b_5(); //+0xA8
	void opc_reset_b_6(); //+0xB0
	void opc_reset_b_7(); //+0xB8

	void opc_reset_c_0(); //+0x81
	void opc_reset_c_1(); //+0x89
	void opc_reset_c_2(); //+0x91
	void opc_reset_c_3(); //+0x99
	void opc_reset_c_4(); //+0xA1
	void opc_reset_c_5(); //+0xA9
	void opc_reset_c_6(); //+0xB1
	void opc_reset_c_7(); //+0xB9

	void opc_reset_d_0(); //+0x82
	void opc_reset_d_1(); //+0x8A
	void opc_reset_d_2(); //+0x92
	void opc_reset_d_3(); //+0x9A
	void opc_reset_d_4(); //+0xA2
	void opc_reset_d_5(); //+0xAA
	void opc_reset_d_6(); //+0xB2
	void opc_reset_d_7(); //+0xBA

	void opc_reset_e_0(); //+0x83
	void opc_reset_e_1(); //+0x8B
	void opc_reset_e_2(); //+0x93
	void opc_reset_e_3(); //+0x9B
	void opc_reset_e_4(); //+0xA3
	void opc_reset_e_5(); //+0xAB
	void opc_reset_e_6(); //+0xB3
	void opc_reset_e_7(); //+0xBB

	void opc_reset_h_0(); //+0x84
	void opc_reset_h_1(); //+0x8C
	void opc_reset_h_2(); //+0x94
	void opc_reset_h_3(); //+0x9C
	void opc_reset_h_4(); //+0xA4
	void opc_reset_h_5(); //+0xAC
	void opc_reset_h_6(); //+0xB4
	void opc_reset_h_7(); //+0xBC

	void opc_reset_l_0(); //+0x85
	void opc_reset_l_1(); //+0x8D
	void opc_reset_l_2(); //+0x95
	void opc_reset_l_3(); //+0x9D
	void opc_reset_l_4(); //+0xA5
	void opc_reset_l_5(); //+0xAD
	void opc_reset_l_6(); //+0xB5
	void opc_reset_l_7(); //+0xBD

	void opc_reset_p_hl_0(); //+0x86
	void opc_reset_p_hl_1(); //+0x8E
	void opc_reset_p_hl_2(); //+0x96
	void opc_reset_p_hl_3(); //+0x9E
	void opc_reset_p_hl_4(); //+0xA6
	void opc_reset_p_hl_5(); //+0xAE
	void opc_reset_p_hl_6(); //+0xB6
	void opc_reset_p_hl_7(); //+0xBE

	// bit shifts

	void opc_srl_a(); //+0x3F
	void opc_srl_b(); //+0x38
	void opc_srl_c(); //+0x39
	void opc_srl_d(); //+0x3A
	void opc_srl_e(); //+0x3B
	void opc_srl_h(); //+0x3C
	void opc_srl_l(); //+0x3D
	void opc_srl_p_hl(); //+0x3E

	// bitshift right, preserve sign

	void opc_sra_a(); //+0x2F
	void opc_sra_b(); //+0x28
	void opc_sra_c(); //+0x29
	void opc_sra_d(); //+0x2A
	void opc_sra_e(); //+0x2B
	void opc_sra_h(); //+0x2C
	void opc_sra_l(); //+0x2D
	void opc_sra_p_hl(); //+0x2E

	// bitshift left, preserve sign

	void opc_sla_a(); //+0x27
	void opc_sla_b(); //+0x20
	void opc_sla_c(); //+0x21
	void opc_sla_d(); //+0x22
	void opc_sla_e(); //+0x23
	void opc_sla_h(); //+0x24
	void opc_sla_l(); //+0x25
	void opc_sla_p_hl(); //+0x26

	// swap nybbles

	void swap_a(); //+0x37
	void swap_b(); //+0x30
	void swap_c(); //+0x31
	void swap_d(); //+0x32
	void swap_e(); //+0x33
	void swap_h(); //+0x34
	void swap_l(); //+0x35
	void swap_p_hl(); //+0x36

	// rotate right

	void opc_rr_a(); //+0x1F
	void opc_rr_b(); //+0x18
	void opc_rr_c(); //+0x19
	void opc_rr_d(); //+0x1A
	void opc_rr_e(); //+0x1B
	void opc_rr_h(); //+0x1C
	void opc_rr_l(); //+0x1D
	void opc_rr_p_hl(); //+0x1E

	// rotate left

	void opc_rl_a(); //+0x17
	void opc_rl_b(); //+0x10
	void opc_rl_c(); //+0x11
	void opc_rl_d(); //+0x12
	void opc_rl_e(); //+0x13
	void opc_rl_h(); //+0x14
	void opc_rl_l(); //+0x15
	void opc_rl_p_hl(); //+0x16

	// rotate right carry

	void opc_rrc_a(); //+0x0F
	void opc_rrc_b(); //+0x08
	void opc_rrc_c(); //+0x09
	void opc_rrc_d(); //+0x0A
	void opc_rrc_e(); //+0x0B
	void opc_rrc_h(); //+0x0C
	void opc_rrc_l(); //+0x0D
	void opc_rrc_p_hl(); //+0x0E

	// rotate left carry

	void opc_rlc_a(); //+0x07
	void opc_rlc_b(); //+0x00
	void opc_rlc_c(); //+0x01
	void opc_rlc_d(); //+0x02
	void opc_rlc_e(); //+0x03
	void opc_rlc_h(); //+0x04
	void opc_rlc_l(); //+0x05
	void opc_rlc_p_hl(); //+0x06

	// push 16bit onto stack

	void opc_push_bc(); //0xC5
	void opc_push_de(); //0xD5
	void opc_push_hl(); //0xE5
	void opc_push_af(); //0xF5

	// pop 16bit from stack into register

	void opc_pop_bc(); //0xC1
	void opc_pop_de(); //0xD1
	void opc_pop_hl(); //0xE1
	void opc_pop_af(); //0xF1


	// Misc:

	// load A from 0xFF00 + n
	void opc_ldh_a_p_n(); //0xF0
	// save A at 0xFF00 + n
	void opc_ldh_p_n_a(); //0xE0
	// save A at 0xFF00 + C
	void opc_ldh_p_c_a(); //0xE2
	// save A at nn
	void opc_ld_p_nn_a(); //0xEA
	// save SP at nn
	void opc_ld_p_nn_sp(); //0x08
	// copy HL to SP
	void opc_ld_sp_hl(); //0xF9
	// add signed n to SP, save result in HL
	void opc_ldhl_sp_n(); //F8
	// clear carry flag
	void opc_ccf(); //0x3F
	// set carry flag
	void opc_scf(); //0x37
	// compliment (logical NOT) on A
	void opc_cpl(); //0x2F

	// relative jump by n

	void opc_jr_n(); //0x18
	void opc_jr_z_n(); //0x28 - if ZERO is set
	void opc_jr_c_n(); //0x38 - if CARRY is set
	void opc_jr_nz_n(); //0x20 - if ZERO is NOT set
	void opc_jr_nc_n(); //0x30 - if CARRY is NOT set

	//TODO:
	void opc_reti(); //0xD9
	void opc_di(); //0xF3

	// no operation
	void opc_nop(); //0x00
	// STOP CPU
	void opc_stop(); //0x10
	// extended opcodes
	void opc_ext(); //0xCB

	// setting and unsetting flags

	void set_flag(u8 flag);
	void reset_flag(u8 flag);
	bool get_flag(u8 flag);

	// helper functions

	void add(u8 &a, u8 b); // adding two 8bit values
	void inc(u8 &val); // incrementing 8bit value
	void dec(u8 &val); // decrementing 8bit value
	void add16(u16 &a, u16 b); // adding two 16bit values
	void inc16(u16 &val); // incrementing 16bit value
	void dec16(u16 &val); // decrementing 16bit value
	void adc(u8 &a, u8 b); // adding two 8bit values + carry flag
	void sub(u8 &a, u8 b); // subtracting b from a, save in a
	void sbc(u8 &a, u8 b); // subtract with carry
	void logical_and(u8 &a, u8 b); // logical AND, save in a
	void logical_or(u8 &a, u8 b); // logical OR, save in a
	void logical_xor(u8 &a, u8 b); // logical XOR, save in a
	void compare(u8 a, u8 b); // compare, set flags accordingly
	void call_subroutine(u16 address); // call subroutine at address
	void return_subroutine(); // return from subroutine
	void reset_bit(u8 &reg, u8 bit); // reset bit at position bit in register
	void reset_bit16(u16 &reg, u8 bit); // same, 16 bit version
	void test_bit(u8 &reg, u8 bit); // test bit at position bit in register
	void test_bit16(u16 &reg, u8 bit); // test, 16 bit version
	void set_bit(u8 &reg, u8 bit); // set bit at position bit in register
	void set_bit16(u16 &reg, u8 bit); // same, 16 bit version
	void shift_right(u8 &reg); // shift reg right by amount
	void shift_right_preserve_sign(u8 &reg); // shift right, preserve the sign
	void shift_left_preserve_sign(u8 &reg); // shift left, preserve the sign
	void swap(u8 &reg); // swap nybbles in reg
	void rotate_right(u8 &reg); // rotate right by one bit, through carry flag
	void rotate_left(u8 &reg); // rotate left by one bit, through carry flag
	void rotate_right_carry(u8 &reg); // rotate right by one bit, jesus christ, this is the only real rotation, fuck this shit
	void rotate_left_carry(u8 &reg); // same
	void push(u16 value); // push value onto stack
	void pop(u16 &_reg); // pop stack at SP into reg
	void relative_jump(char value); // relative jump by value

#ifndef DEBUG_BUILD
/*
 *  memory map:
 *  0000 - 4000 -> ROM bank (cartridge)
 *  4000 - 8000 -> switchable ROM bank (cartridge)
 *  8000 - A000 -> video RAM
 *  A000 - C000 -> switchable RAM bank
 *  C000 - E000 -> internal RAM  - main RAM (i think...)
 *  E000 - FE00 -> echo of internal RAM
 *  FE00 - FEA0 -> sprite attribute memory (OAM)
 *  FEA0 - FF00 -> empty
 *  FF00 - FF4C -> I/O ports
 *  FF4C - FF80 -> empty
 *  FF80 - FFFE -> internal RAM
 *  FFFF -> interrupt enable register
 */
	Gameboy_Memory *memory;
#endif

public:

	void emulate_cycle();
	void startup();
	void load_file(string location, u16 starting_point);
	Gameboy_Cpu();

	registers reg;
	// TODO: move this to private, create setter
	shared_ptr<Gameboy_Display> display;
	shared_ptr<Gameboy_Memory> memory;
#ifdef DEBUG_BUILD
/*
 *  memory map:
 *  0000 - 4000 -> ROM bank (cartridge)
 *  4000 - 8000 -> switchable ROM bank (cartridge)
 *  8000 - A000 -> video RAM
 *  A000 - C000 -> switchable RAM bank
 *  C000 - E000 -> internal RAM  - main RAM (i think...)
 *  E000 - FE00 -> echo of internal RAM
 *  FE00 - FEA0 -> sprite attribute memory (OAM)
 *  FEA0 - FF00 -> empty
 *  FF00 - FF4C -> I/O ports
 *  FF4C - FF80 -> empty
 *  FF80 - FFFE -> internal RAM
 *  FFFF -> interrupt enable register
 */
#endif
};


#endif //GAMEBOY_EMU_GAMEBOY_CPU_H