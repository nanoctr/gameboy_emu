//
// Created by michi on 30.05.16.
//

#ifndef GAMEBOY_EMU_GAMEBOY_CPU_H
#define GAMEBOY_EMU_GAMEBOY_CPU_H

typedef unsigned char u8;
typedef unsigned short u16;

/*
 *  stolen from https://cturt.github.io/cinoop.html
 *  allows accessing registers like: register.a, register.af
 *  a, b, c, d, e, f, h, l = 8bit registers, often combined to form 16 bit
 *  F = flag register. flags:
 *  4th bit -> CARRY flag
 *  5th bit -> half-carry flag; set if carry from bit 3
 *  6th bit -> subtract flag; if instruction is subtract -> set; otherwise unset
 *  7th bit -> zero flag; if result is 0 -> set; otherwise -> unset
 */
struct registers {
	struct {
		union {
			struct {
				u8 f;
				u8 a;
			};
			u16 af;
		};
	};
	struct {
		union {
			struct {
				u8 c;
				u8 b;
			};
			u16 bc;
		};
	};
	struct {
		union {
			struct {
				u8 e;
				u8 d;
			};
			u16 de;
		};
	};
	struct {
		union {
			struct {
				u8 l;
				u8 h;
			};
			u16 hl;
		};
	};
};

// stack pointer and program counter
u16 sp;
u16 pc;

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
u8 memory[0xFFFF];

u8 video_memory[256][256];




class Gameboy_Cpu {
private:
	registers reg;
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
	void opc_ld_b_hl(); //0x46
	void opc_ld_c_a(); //0x4F
	void opc_ld_c_b(); //0x48
	void opc_ld_c_c(); //0x49 -> NOP
	void opc_ld_c_d(); //0x4A
	void opc_ld_c_e(); //0x4B
	void opc_ld_c_h(); //0x4C
	void opc_ld_c_l(); //0x4D
	void opc_ld_c_hl(); //0x4E
	void opc_ld_d_a(); //0x57
	void opc_ld_d_b(); //0x50
	void opc_ld_d_c(); //0x51
	void opc_ld_d_d(); //0x52 -> NOP
	void opc_ld_d_e(); //0x53
	void opc_ld_d_h(); //0x54
	void opc_ld_d_l(); //0x55
	void opc_ld_d_hl(); //0x56
	void opc_ld_e_a(); //0x5F
	void opc_ld_e_b(); //0x58
	void opc_ld_e_c(); //0x59
	void opc_ld_e_d(); //0x5A
	void opc_ld_e_e(); //0x5B -> NOP
	void opc_ld_e_h(); //0x5C
	void opc_ld_e_l(); //0x5D
	void opc_ld_e_hl(); //0x5E
	void opc_ld_h_a(); //0x67
	void opc_ld_h_b(); //0x60
	void opc_ld_h_c(); //0x61
	void opc_ld_h_d(); //0x62
	void opc_ld_h_e(); //0x63
	void opc_ld_h_h(); //0x64 -> NOP
	void opc_ld_h_l(); //0x65
	void opc_ld_h_hl(); //0x66
	void opc_ld_l_a(); //0x6F
	void opc_ld_l_b(); //0x68
	void opc_ld_l_c(); //0x69
	void opc_ld_l_d(); //0x6A
	void opc_ld_l_e(); //0x6B
	void opc_ld_l_h(); //0x6C
	void opc_ld_l_l(); //0x6D -> NOP
	void opc_ld_l_hl(); //0x6E
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
	void opc_bit_a_0();//0x47
	void opc_bit_a_1();//0x4F
	void opc_bit_a_2();//0x57
	void opc_bit_a_3();//0x5F
	void opc_bit_a_4();//0x67
	void opc_bit_a_5();//0x6F
	void opc_bit_a_6();//0x77
	void opc_bit_a_7();//0x7F

	void opc_bit_b_0();//0x40
	void opc_bit_b_1();//0x48
	void opc_bit_b_2();//0x50
	void opc_bit_b_3();//0x58
	void opc_bit_b_4();//0x60
	void opc_bit_b_5();//0x68
	void opc_bit_b_6();//0x70
	void opc_bit_b_7();//0x78

	void opc_bit_c_0();//0x41
	void opc_bit_c_1();//0x49
	void opc_bit_c_2();//0x51
	void opc_bit_c_3();//0x59
	void opc_bit_c_4();//0x61
	void opc_bit_c_5();//0x69
	void opc_bit_c_6();//0x71
	void opc_bit_c_7();//0x79

	void opc_bit_d_0();//0x42
	void opc_bit_d_1();//0x4A
	void opc_bit_d_2();//0x52
	void opc_bit_d_3();//0x5A
	void opc_bit_d_4();//0x62
	void opc_bit_d_5();//0x6A
	void opc_bit_d_6();//0x72
	void opc_bit_d_7();//0x7A

	void opc_bit_e_0();//0x43
	void opc_bit_e_1();//0x4B
	void opc_bit_e_2();//0x53
	void opc_bit_e_3();//0x5B
	void opc_bit_e_4();//0x63
	void opc_bit_e_5();//0x6B
	void opc_bit_e_6();//0x73
	void opc_bit_e_7();//0x7B

	void opc_bit_h_0();//0x44
	void opc_bit_h_1();//0x4C
	void opc_bit_h_2();//0x54
	void opc_bit_h_3();//0x5C
	void opc_bit_h_4();//0x64
	void opc_bit_h_5();//0x6C
	void opc_bit_h_6();//0x74
	void opc_bit_h_7();//0x7C

	void opc_bit_l_0();//0x45
	void opc_bit_l_1();//0x4D
	void opc_bit_l_2();//0x55
	void opc_bit_l_3();//0x5D
	void opc_bit_l_4();//0x65
	void opc_bit_l_5();//0x6D
	void opc_bit_l_6();//0x75
	void opc_bit_l_7();//0x7D

	void opc_bit_hl_0();//0x46
	void opc_bit_hl_1();//0x4E
	void opc_bit_hl_2();//0x56
	void opc_bit_hl_3();//0x5E
	void opc_bit_hl_4();//0x66
	void opc_bit_hl_5();//0x6E
	void opc_bit_hl_6();//0x76
	void opc_bit_hl_7();//0x7E

	// setting bits
	void opc_set_a_0(); //0xC7
	void opc_set_a_1(); //0xCF
	void opc_set_a_2(); //0xD7
	void opc_set_a_3(); //0xDF
	void opc_set_a_4(); //0xE7
	void opc_set_a_5(); //0xEF
	void opc_set_a_6(); //0xF7
	void opc_set_a_7(); //0xFF

	void opc_set_b_0(); //0xC0
	void opc_set_b_1(); //0xC8
	void opc_set_b_2(); //0xD0
	void opc_set_b_3(); //0xD8
	void opc_set_b_4(); //0xE0
	void opc_set_b_5(); //0xE8
	void opc_set_b_6(); //0xF0
	void opc_set_b_7(); //0xF8

	void opc_set_c_0(); //0xC1
	void opc_set_c_1(); //0xC9
	void opc_set_c_2(); //0xD1
	void opc_set_c_3(); //0xD9
	void opc_set_c_4(); //0xE1
	void opc_set_c_5(); //0xE9
	void opc_set_c_6(); //0xF1
	void opc_set_c_7(); //0xF9

	void opc_set_d_0(); //0xC2
	void opc_set_d_1(); //0xCA
	void opc_set_d_2(); //0xD2
	void opc_set_d_3(); //0xDA
	void opc_set_d_4(); //0xE2
	void opc_set_d_5(); //0xEA
	void opc_set_d_6(); //0xF2
	void opc_set_d_7(); //0xFA

	void opc_set_e_0(); //0xC3
	void opc_set_e_1(); //0xCB
	void opc_set_e_2(); //0xD3
	void opc_set_e_3(); //0xDB
	void opc_set_e_4(); //0xE3
	void opc_set_e_5(); //0xEB
	void opc_set_e_6(); //0xF3
	void opc_set_e_7(); //0xFB

	void opc_set_h_0(); //0xC4
	void opc_set_h_1(); //0xCC
	void opc_set_h_2(); //0xD4
	void opc_set_h_3(); //0xDC
	void opc_set_h_4(); //0xE4
	void opc_set_h_5(); //0xEC
	void opc_set_h_6(); //0xF4
	void opc_set_h_7(); //0xFC

	void opc_set_l_0(); //0xC5
	void opc_set_l_1(); //0xCD
	void opc_set_l_2(); //0xD5
	void opc_set_l_3(); //0xDD
	void opc_set_l_4(); //0xE5
	void opc_set_l_5(); //0xED
	void opc_set_l_6(); //0xF5
	void opc_set_l_7(); //0xFD

	void opc_set_hl_0(); //0xC6
	void opc_set_hl_1(); //0xCE
	void opc_set_hl_2(); //0xD6
	void opc_set_hl_3(); //0xDE
	void opc_set_hl_4(); //0xE6
	void opc_set_hl_5(); //0xEE
	void opc_set_hl_6(); //0xF6
	void opc_set_hl_7(); //0xFE

	// resetting bits
	void opc_reset_a_0(); //0xC7
	void opc_reset_a_1(); //0xCF
	void opc_reset_a_2(); //0xD7
	void opc_reset_a_3(); //0xDF
	void opc_reset_a_4(); //0xE7
	void opc_reset_a_5(); //0xEF
	void opc_reset_a_6(); //0xF7
	void opc_reset_a_7(); //0xFF

	void opc_reset_b_0(); //0xC0
	void opc_reset_b_1(); //0xC8
	void opc_reset_b_2(); //0xD0
	void opc_reset_b_3(); //0xD8
	void opc_reset_b_4(); //0xE0
	void opc_reset_b_5(); //0xE8
	void opc_reset_b_6(); //0xF0
	void opc_reset_b_7(); //0xF8

	void opc_reset_c_0(); //0xC1
	void opc_reset_c_1(); //0xC9
	void opc_reset_c_2(); //0xD1
	void opc_reset_c_3(); //0xD9
	void opc_reset_c_4(); //0xE1
	void opc_reset_c_5(); //0xE9
	void opc_reset_c_6(); //0xF1
	void opc_reset_c_7(); //0xF9

	void opc_reset_d_0(); //0xC2
	void opc_reset_d_1(); //0xCA
	void opc_reset_d_2(); //0xD2
	void opc_reset_d_3(); //0xDA
	void opc_reset_d_4(); //0xE2
	void opc_reset_d_5(); //0xEA
	void opc_reset_d_6(); //0xF2
	void opc_reset_d_7(); //0xFA

	void opc_reset_e_0(); //0xC3
	void opc_reset_e_1(); //0xCB
	void opc_reset_e_2(); //0xD3
	void opc_reset_e_3(); //0xDB
	void opc_reset_e_4(); //0xE3
	void opc_reset_e_5(); //0xEB
	void opc_reset_e_6(); //0xF3
	void opc_reset_e_7(); //0xFB

	void opc_reset_h_0(); //0xC4
	void opc_reset_h_1(); //0xCC
	void opc_reset_h_2(); //0xD4
	void opc_reset_h_3(); //0xDC
	void opc_reset_h_4(); //0xE4
	void opc_reset_h_5(); //0xEC
	void opc_reset_h_6(); //0xF4
	void opc_reset_h_7(); //0xFC

	void opc_reset_l_0(); //0xC5
	void opc_reset_l_1(); //0xCD
	void opc_reset_l_2(); //0xD5
	void opc_reset_l_3(); //0xDD
	void opc_reset_l_4(); //0xE5
	void opc_reset_l_5(); //0xED
	void opc_reset_l_6(); //0xF5
	void opc_reset_l_7(); //0xFD

	void opc_reset_hl_0(); //0xC6
	void opc_reset_hl_1(); //0xCE
	void opc_reset_hl_2(); //0xD6
	void opc_reset_hl_3(); //0xDE
	void opc_reset_hl_4(); //0xE6
	void opc_reset_hl_5(); //0xEE
	void opc_reset_hl_6(); //0xF6
	void opc_reset_hl_7(); //0xFE

	// bit shifts
	void opc_srl_a(); //0x3F
	void opc_srl_b(); //0x38
	void opc_srl_c(); //0x39
	void opc_srl_d(); //0x3A
	void opc_srl_e(); //0x3B
	void opc_srl_h(); //0x3C
	void opc_srl_l(); //0x3D
	void opc_srl_p_hl(); //0x3E

	// bitshift right, preserve sign
	void opc_sra_a(); //0x2F
	void opc_sra_b(); //0x28
	void opc_sra_c(); //0x29
	void opc_sra_d(); //0x2A
	void opc_sra_e(); //0x2B
	void opc_sra_h(); //0x2C
	void opc_sra_l(); //0x2D
	void opc_sra_p_hl(); //0x2E

	// bitshift left, preserve sign
	void opc_sla_a(); //0x27
	void opc_sla_b(); //0x20
	void opc_sla_c(); //0x21
	void opc_sla_d(); //0x22
	void opc_sla_e(); //0x23
	void opc_sla_h(); //0x24
	void opc_sla_l(); //0x25
	void opc_sla_p_hl(); //0x26

	// swap nybbles
	void swap_a(); //0x37
	void swap_b(); //0x30
	void swap_c(); //0x31
	void swap_d(); //0x32
	void swap_e(); //0x33
	void swap_h(); //0x34
	void swap_l(); //0x35
	void swap_p_hl(); //0x36

	// rotate right
	void rr_a(); //0x1F
	void rr_b(); //0x18
	void rr_c(); //0x19
	void rr_d(); //0x1A
	void rr_e(); //0x1B
	void rr_h(); //0x1C
	void rr_l(); //0x1D
	void rr_p_hl(); //0x1E

	// rotate left
	void rl_a(); //0x17
	void rl_b(); //0x10
	void rl_c(); //0x11
	void rl_d(); //0x12
	void rl_e(); //0x13
	void rl_h(); //0x14
	void rl_l(); //0x15
	void rl_p_hl(); //0x16

	// rotate right carry
	void rrc_a(); //0x0F
	void rrc_b(); //0x08
	void rrc_c(); //0x09
	void rrc_d(); //0x0A
	void rrc_e(); //0x0B
	void rrc_h(); //0x0C
	void rrc_l(); //0x0D
	void rrc_p_hl(); //0x0E

	// rotate left carry
	void rlc_a(); //0x07
	void rlc_b(); //0x00
	void rlc_c(); //0x01
	void rlc_d(); //0x02
	void rlc_e(); //0x03
	void rlc_h(); //0x04
	void rlc_l(); //0x05
	void rlc_p_hl(); //0x06


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
	void test_bit(u8 &reg, u8 bit); // test bit at position bit in register
	void test_bit16(u16 &reg, u8 bit); // test, 16 bit version
	void set_bit(u8 &reg, u8 bit); // set bit at position bit in register
	void shift_right(u8 &reg); // shift reg right by amount
	void shift_right_preserve_sign(u8 &reg); // shift right, preserve the sign
	void shift_left_preserve_sign(u8 &reg); // shift left, preserve the sign
	void swap(u8 &reg); // swap nybbles in reg
	void rotate_right(u8 &reg); // rotate right by one bit, through carry flag
	void rotate_left(u8 &reg); // rotate left by one bit, through carry flag
	void rotate_right_carry(u8 &reg); // rotate right by one bit, jesus christ, this is the only real rotation, fuck this shit
	void rotate_left_carry(u8 &reg); // same


public:
	void emulate_cycle();
	void startup();
};


#endif //GAMEBOY_EMU_GAMEBOY_CPU_H
