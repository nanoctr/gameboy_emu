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


	// setting and unsetting flags
	void set_flag(u8 flag);
	void unset_flag(u8 flag);
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

public:
	void emulate_cycle();
	void startup();
};


#endif //GAMEBOY_EMU_GAMEBOY_CPU_H
