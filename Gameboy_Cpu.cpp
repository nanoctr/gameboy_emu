//
// Created by michi on 30.05.16.
//

#include "Gameboy_Cpu.h"

typedef unsigned char u8;
typedef unsigned short u16;

void Gameboy_Cpu::emulate_cycle() {

}

void Gameboy_Cpu::startup() {

}

// LOAD group - load value into register

// load free value into register
// 0x06 - load n in B
void Gameboy_Cpu::opc_ld_b_n() {
	reg.b = memory[pc+1];
	pc += 2;
}
// 0x0E - load in C
void Gameboy_Cpu::opc_ld_c_n() {
	reg.c = memory[pc+1];
	pc += 2;
}
// 0x16 - load in D
void Gameboy_Cpu::opc_ld_d_n() {
	reg.d = memory[pc+1];
	pc += 2;
}
// 0x1E - load in E
void Gameboy_Cpu::opc_ld_e_n() {
	reg.e = memory[pc+1];
	pc += 2;
}
// 0x26 - load in H
void Gameboy_Cpu::opc_ld_h_n() {
	reg.h = memory[pc+1];
	pc += 2;
}
// 0x2E - load in L
void Gameboy_Cpu::opc_ld_l_n() {
	reg.l = memory[pc+1];
	pc += 2;
}
// 0x01 - load 16bit in BC
void Gameboy_Cpu::opc_ld_bc_nn() {
	reg.bc = (memory[pc+1] << 8) & memory[pc+2];
	pc += 3;
}
// 0x11 - load 16bit in DE
void Gameboy_Cpu::opc_ld_de_nn() {
	reg.de = (memory[pc+1] << 8) & memory[pc+2];
	pc += 3;
}
// 0x21 - load 16bit in HL
void Gameboy_Cpu::opc_ld_hl_nn() {
	reg.hl = (memory[pc+1] << 8) & memory[pc+2];
	pc += 3;
}
// 0x31 - load 16bit in SP
void Gameboy_Cpu::opc_ld_sp_nn() {
	sp = (memory[pc+1] << 8) & memory[pc+2];
	pc += 3;
}
// 0x36 - load 8bit in HL
void Gameboy_Cpu::opc_ld_hl_n() {
	memory[reg.hl] = memory[pc+1];
	pc += 2;
}

// copy register r2 into r1
// 0x7F - load A into A => NOP

// 0x78 - load B into A
void Gameboy_Cpu::opc_ld_a_b() {
	reg.a = reg.b;
	++pc;
}
//
void Gameboy_Cpu::opc_ld_a_c() {
	reg.a = reg.c;
	++pc;
}
void Gameboy_Cpu::opc_ld_a_d() {
	reg.a = reg.d;
	++pc;
}
void Gameboy_Cpu::opc_ld_a_e() {
	reg.a = reg.e;
	++pc;
}
void Gameboy_Cpu::opc_ld_a_h() {
	reg.a = reg.h;
	++pc;
}
void Gameboy_Cpu::opc_ld_a_l() {
	reg.a = reg.l;
	++pc;
}
void Gameboy_Cpu::opc_ld_a_hl() {
	reg.a = memory[reg.hl];
	++pc;
}
void Gameboy_Cpu::opc_ld_a_bc() {
	reg.a = reg.bc;
	++pc;
}
void Gameboy_Cpu::opc_ld_a_de() {
	reg.a = reg.de;
	++pc;
}
void Gameboy_Cpu::opc_ld_a_nn() {
	reg.a = (memory[pc+1] << 8) & memory[pc+2];
	pc += 3;
}
void Gameboy_Cpu::opc_ld_a_n() {
	reg.a = memory[pc+1];
	pc += 2;
}
void Gameboy_Cpu::opc_ld_b_a() {
	reg.b = reg.a;
	++pc;
} //0x47
void Gameboy_Cpu::opc_ld_b_c() {
	reg.b = reg.c;
	++pc;
}
void Gameboy_Cpu::opc_ld_b_d() {
	reg.b = reg.d;
	++pc;
}
void Gameboy_Cpu::opc_ld_b_e() {
	reg.b = reg.e;
	++pc;
}
void Gameboy_Cpu::opc_ld_b_h() {
	reg.b = reg.h;
	++pc;
}
void Gameboy_Cpu::opc_ld_b_l() {
	reg.b = reg.l;
	++pc;
}
void Gameboy_Cpu::opc_ld_b_hl() {
	reg.b = memory[reg.hl];
	++pc;
}
void Gameboy_Cpu::opc_ld_c_a() {
	reg.c = reg.a;
	++pc;
}
void Gameboy_Cpu::opc_ld_c_b() {
	reg.c = reg.b;
	++pc;
}
void Gameboy_Cpu::opc_ld_c_d() {
	reg.c = reg.d;
	++pc;
}
void Gameboy_Cpu::opc_ld_c_e() {
	reg.c = reg.e;
	++pc;
}
void Gameboy_Cpu::opc_ld_c_h() {
	reg.c = reg.h;
	++pc;
}
void Gameboy_Cpu::opc_ld_c_l() {
	reg.c = reg.l;
	++pc;
}
void Gameboy_Cpu::opc_ld_c_hl() {
	reg.c = memory[reg.hl];
	++pc;
}
void Gameboy_Cpu::opc_ld_d_a() {
	reg.d = reg.a;
	++pc;
}
void Gameboy_Cpu::opc_ld_d_b() {
	reg.d = reg.b;
	++pc;
}
void Gameboy_Cpu::opc_ld_d_c() {
	reg.d = reg.c;
	++pc;
}
void Gameboy_Cpu::opc_ld_d_e() {
	reg.d = reg.e;
	++pc;
}
void Gameboy_Cpu::opc_ld_d_h() {
	reg.d = reg.h;
	++pc;
}
void Gameboy_Cpu::opc_ld_d_l() {
	reg.d = reg.l;
	++pc;
}
void Gameboy_Cpu::opc_ld_d_hl() {
	reg.d = memory[reg.hl];
	++pc;
}
void Gameboy_Cpu::opc_ld_e_a() {
	reg.e = reg.a;
	++pc;
}
void Gameboy_Cpu::opc_ld_e_b() {
	reg.e = reg.b;
	++pc;
}
void Gameboy_Cpu::opc_ld_e_c() {
	reg.e = reg.c;
	++pc;
}
void Gameboy_Cpu::opc_ld_e_d() {
	reg.e = reg.d;
	++pc;
}
void Gameboy_Cpu::opc_ld_e_h() {
	reg.e = reg.h;
	++pc;
}
void Gameboy_Cpu::opc_ld_e_l() {
	reg.e = reg.l;
	++pc;
}
void Gameboy_Cpu::opc_ld_e_hl() {
	reg.e = memory[reg.hl];
	++pc;
}
void Gameboy_Cpu::opc_ld_h_a() {
	reg.h = reg.a;
	++pc;
}
void Gameboy_Cpu::opc_ld_h_b() {
	reg.h = reg.b;
	++pc;
}
void Gameboy_Cpu::opc_ld_h_c() {
	reg.h = reg.c;
	++pc;
}
void Gameboy_Cpu::opc_ld_h_d() {
	reg.h = reg.d;
	++pc;
}
void Gameboy_Cpu::opc_ld_h_e() {
	reg.h = reg.e;
	++pc;
}
void Gameboy_Cpu::opc_ld_h_l() {
	reg.h = reg.l;
	++pc;
}
void Gameboy_Cpu::opc_ld_h_hl() {
	reg.h = memory[reg.hl];
	++pc;
}
void Gameboy_Cpu::opc_ld_l_a() {
	reg.l = reg.a;
	++pc;
}
void Gameboy_Cpu::opc_ld_l_b() {
	reg.l = reg.b;
	++pc;
}
void Gameboy_Cpu::opc_ld_l_c() {
	reg.l = reg.c;
	++pc;
}
void Gameboy_Cpu::opc_ld_l_d() {
	reg.l = reg.d;
	++pc;
}
void Gameboy_Cpu::opc_ld_l_e() {
	reg.l = reg.e;
	++pc;
}
void Gameboy_Cpu::opc_ld_l_h() {
	reg.l = reg.h;
	++pc;
}
void Gameboy_Cpu::opc_ld_l_hl() {
	reg.l = memory[reg.hl];
	++pc;
}
void Gameboy_Cpu::opc_ld_hl_a() {
	memory[reg.hl] = reg.a;
	++pc;
}
void Gameboy_Cpu::opc_ld_hl_b() {
	memory[reg.hl] = reg.b;
	++pc;
}
void Gameboy_Cpu::opc_ld_hl_c() {
	memory[reg.hl] = reg.c;
	++pc;
}
void Gameboy_Cpu::opc_ld_hl_d() {
	memory[reg.hl] = reg.d;
	++pc;
}
void Gameboy_Cpu::opc_ld_hl_e() {
	memory[reg.hl] = reg.e;
	++pc;
}
void Gameboy_Cpu::opc_ld_hl_h() {
	memory[reg.hl] = reg.h;
	++pc;
}
void Gameboy_Cpu::opc_ld_hl_l() {
	memory[reg.hl] = reg.l;
	++pc;
}

void Gameboy_Cpu::opc_ld_bc_a() {
	memory[reg.bc] = reg.a;
	++pc;
} //0x02
void Gameboy_Cpu::opc_ld_de_a() {
	memory[reg.de] = reg.a;
	++pc;
} //0x12

void Gameboy_Cpu::opc_ldi_hl_a() {
	memory[reg.hl] = reg.a;
	++reg.hl;
	++pc;
}
void Gameboy_Cpu::opc_ldd_hl_a() {
	memory[reg.hl] = reg.a;
	--reg.hl;
	++pc;
}