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
	void opc_ld_b_n();
	void opc_ld_c_n();
	void opc_ld_d_n();
	void opc_ld_e_n();
	void opc_ld_h_n();
	void opc_ld_l_n();
	void opc_ld_bc_nn();
	void opc_ld_de_nn();
	void opc_ld_hl_nn();
	void opc_ld_sp_nn();
	void opc_ld_hl_n();

	// load r2 into r1:
	void opc_ld_a_b();
	void opc_ld_a_c();
	void opc_ld_a_d();
	void opc_ld_a_e();
	void opc_ld_a_h();
	void opc_ld_a_l();
	void opc_ld_a_hl();
	void opc_ld_b_c();
	void opc_ld_b_d();
	void opc_ld_b_e();
	void opc_ld_b_h();
	void opc_ld_b_l();
	void opc_ld_b_hl();
	void opc_ld_c_b();
	void opc_ld_c_d();
	void opc_ld_c_e();
	void opc_ld_c_h();
	void opc_ld_c_l();
	void opc_ld_c_hl();
	void opc_ld_d_b();
	void opc_ld_d_c();
	void opc_ld_d_e();
	void opc_ld_d_h();
	void opc_ld_d_l();
	void opc_ld_d_hl();
	void opc_ld_e_b();
	void opc_ld_e_c();
	void opc_ld_e_d();
	void opc_ld_e_h();
	void opc_ld_e_l();
	void opc_ld_e_hl();
	void opc_ld_h_b();
	void opc_ld_h_c();
	void opc_ld_h_d();
	void opc_ld_h_e();
	void opc_ld_h_l();
	void opc_ld_h_hl();
	void opc_ld_l_b();
	void opc_ld_l_c();
	void opc_ld_l_d();
	void opc_ld_l_e();
	void opc_ld_l_h();
	void opc_ld_l_hl();
	void opc_ld_hl_b();
	void opc_ld_hl_c();
	void opc_ld_hl_d();
	void opc_ld_hl_e();
	void opc_ld_hl_h();
	void opc_ld_hl_l();

public:
	void emulate_cycle();
	void startup();
};


#endif //GAMEBOY_EMU_GAMEBOY_CPU_H
