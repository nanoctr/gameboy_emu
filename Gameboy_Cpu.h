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
	void opc_ld_hl_n(); //0x36

	// load r2 into r1:
	void opc_ld_a_b(); //0x78
	void opc_ld_a_c(); //0x79
	void opc_ld_a_d(); //0x7A
	void opc_ld_a_e(); //0x7B
	void opc_ld_a_h(); //0x7C
	void opc_ld_a_l(); //0x7D
	void opc_ld_a_hl(); //0x7E
	void opc_ld_a_a(); //0x7F -> NOP
	void opc_ld_a_bc(); //0x0A
	void opc_ld_a_de(); //0x1A
	void opc_ld_a_nn(); //0xFA
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
	void opc_ld_hl_a(); //0x77
	void opc_ld_hl_b(); //0x70
	void opc_ld_hl_c(); //0x71
	void opc_ld_hl_d(); //0x72
	void opc_ld_hl_e(); //0x73
	void opc_ld_hl_h(); //0x74
	void opc_ld_hl_l(); //0x75
	void opc_ld_bc_a(); //0x02
	void opc_ld_de_a(); //0x12

	// other load stuff
	void opc_ldi_hl_a(); //0x22; save A to memory pointed to by HL, HL += 1
	void opc_ldd_hl_a(); //0x32; save A to memory pointed to by HL, HL -= 1

	// increment registers
	void opc_inc_a(); //0x3C
	void opc_inc_b(); //0x04
	void opc_inc_c(); //0x0C
	void opc_inc_d(); //0x14
	void opc_inc_e(); //0x
	void opc_inc_h(); //0x24
	void opc_inc_l(); //0x
	void opc_inc_hl(); //0x24
	void opc_inc_bc(); //0x
	void opc_inc_de(); //0x13
	void opc_inc_sp(); //0x

public:
	void emulate_cycle();
	void startup();
};


#endif //GAMEBOY_EMU_GAMEBOY_CPU_H
