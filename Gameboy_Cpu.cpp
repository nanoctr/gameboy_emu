//
// Created by michi on 30.05.16.
//

#include <iostream>
#include "Gameboy_Cpu.h"

typedef unsigned char u8;
typedef unsigned short u16;

const int CARRY = 4;
const int HALF_CARRY = 5;
const int SUBTRACT = 6;
const int ZERO = 7;

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
void Gameboy_Cpu::opc_ld_p_hl_n() {
	memory[reg.hl] = memory[pc+1];
	pc += 2;
}

// copy register r2 into r1

void Gameboy_Cpu::opc_ld_a_b() {
	reg.a = reg.b;
	++pc;
}
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
void Gameboy_Cpu::opc_ld_a_p_hl() {
	reg.a = memory[reg.hl];
	++pc;
}
void Gameboy_Cpu::opc_ld_a_p_bc() {
	reg.a = memory[reg.bc];
	++pc;
}
void Gameboy_Cpu::opc_ld_a_p_de() {
	reg.a = memory[reg.de];
	++pc;
}
void Gameboy_Cpu::opc_ld_a_p_nn() {
	reg.a = memory[(memory[pc+1] << 8) & memory[pc+2]];
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
void Gameboy_Cpu::opc_ld_p_hl_a() {
	memory[reg.hl] = reg.a;
	++pc;
}
void Gameboy_Cpu::opc_ld_p_hl_b() {
	memory[reg.hl] = reg.b;
	++pc;
}
void Gameboy_Cpu::opc_ld_p_hl_c() {
	memory[reg.hl] = reg.c;
	++pc;
}
void Gameboy_Cpu::opc_ld_p_hl_d() {
	memory[reg.hl] = reg.d;
	++pc;
}
void Gameboy_Cpu::opc_ld_p_hl_e() {
	memory[reg.hl] = reg.e;
	++pc;
}
void Gameboy_Cpu::opc_ld_p_hl_h() {
	memory[reg.hl] = reg.h;
	++pc;
}
void Gameboy_Cpu::opc_ld_p_hl_l() {
	memory[reg.hl] = reg.l;
	++pc;
}

void Gameboy_Cpu::opc_ld_p_bc_a() {
	memory[reg.bc] = reg.a;
	++pc;
} //0x02
void Gameboy_Cpu::opc_ld_p_de_a() {
	memory[reg.de] = reg.a;
	++pc;
} //0x12

void Gameboy_Cpu::opc_ldi_hl_a() {
	memory[reg.hl] = reg.a;
	inc16(reg.hl);
	++pc;
}
void Gameboy_Cpu::opc_ldd_hl_a() {
	memory[reg.hl] = reg.a;
	dec16(reg.hl);
	++pc;
}

// increment values

void Gameboy_Cpu::opc_inc_bc() {
	inc16(reg.bc);
	++pc;
}
void Gameboy_Cpu::opc_inc_de() {
	inc16(reg.de);
	++pc;
}
void Gameboy_Cpu::opc_inc_hl() {
	inc16(reg.hl);
	++pc;
}
void Gameboy_Cpu::opc_inc_sp() {
	inc16(sp);
	++pc;
}
void Gameboy_Cpu::opc_inc_a() {
	inc(reg.a);
	++pc;
}
void Gameboy_Cpu::opc_inc_b() {
	inc(reg.b);
	++pc;
}
void Gameboy_Cpu::opc_inc_c() {
	inc(reg.c);
	++pc;
}
void Gameboy_Cpu::opc_inc_d() {
	inc(reg.d);
	++pc;
}
void Gameboy_Cpu::opc_inc_e() {
	inc(reg.e);
	++pc;
}
void Gameboy_Cpu::opc_inc_h() {
	inc(reg.h);
	++pc;
}
void Gameboy_Cpu::opc_inc_l() {
	inc(reg.l);
	++pc;
}

void Gameboy_Cpu::opc_inc_p_hl() {
	inc(memory[reg.hl]);
	++pc;
}

// decrement values

void Gameboy_Cpu::opc_dec_hl() {
	dec16(reg.hl);
	++pc;
}
void Gameboy_Cpu::opc_dec_bc() {
	dec16(reg.bc);
	++pc;
}
void Gameboy_Cpu::opc_dec_de() {
	dec16(reg.de);
	++pc;
}
void Gameboy_Cpu::opc_dec_sp() {
	dec16(sp);
	++pc;
}
void Gameboy_Cpu::opc_dec_a() {
	dec(reg.a);
	++pc;
}
void Gameboy_Cpu::opc_dec_b() {
	dec(reg.b);
	++pc;
}
void Gameboy_Cpu::opc_dec_c() {
	dec(reg.c);
	++pc;
}
void Gameboy_Cpu::opc_dec_d() {
	dec(reg.d);
	++pc;
}
void Gameboy_Cpu::opc_dec_e() {
	dec(reg.e);
	++pc;
}
void Gameboy_Cpu::opc_dec_h() {
	dec(reg.h);
	++pc;
}
void Gameboy_Cpu::opc_dec_l() {
	dec(reg.l);
	++pc;
}
void Gameboy_Cpu::opc_dec_p_hl() {
	dec(memory[reg.hl]);
	++pc;
}


void Gameboy_Cpu::opc_ldi_a_hl() {
	reg.a = memory[reg.hl];
	++reg.hl;
	++pc;
}
void Gameboy_Cpu::opc_ldd_a_hl() {
	reg.a = memory[reg.hl];
	--reg.hl;
	++pc;
}

//TODO: you gotta set flags in DEC / INC too, retard
//TODO: check other opcodes for flags that need to be set


// add stuff into A

void Gameboy_Cpu::opc_add_a_a() {
	add(reg.a, reg.a);
	++pc;
}
void Gameboy_Cpu::opc_add_a_b() {
	add(reg.a, reg.b);
	++pc;
}
void Gameboy_Cpu::opc_add_a_c() {
	add(reg.a, reg.c);
	++pc;
}
void Gameboy_Cpu::opc_add_a_d() {
	add(reg.a, reg.d);
	++pc;
}
void Gameboy_Cpu::opc_add_a_e() {
	add(reg.a, reg.e);
	++pc;
}
void Gameboy_Cpu::opc_add_a_h() {
	add(reg.a, reg.h);
	++pc;
}
void Gameboy_Cpu::opc_add_a_l() {
	add(reg.a, reg.l);
	++pc;
}
void Gameboy_Cpu::opc_add_a_p_hl() {
	add(reg.a, memory[reg.hl]);
	++pc;
}
void Gameboy_Cpu::opc_add_a_n() {
	add(reg.a, memory[pc+1]);
	pc += 2;
}

void Gameboy_Cpu::opc_add_sp_d() {
	add16(sp, reg.d);
	++pc;
}


// add with carry

void Gameboy_Cpu::opc_adc_a_a() {
	adc(reg.a, reg.a);
	++pc;
}
void Gameboy_Cpu::opc_adc_a_b() {
	adc(reg.a, reg.b);
	++pc;
}
void Gameboy_Cpu::opc_adc_a_c() {
	adc(reg.a, reg.c);
	++pc;
}
void Gameboy_Cpu::opc_adc_a_d() {
	adc(reg.a, reg.d);
	++pc;
}
void Gameboy_Cpu::opc_adc_a_e() {
	adc(reg.a, reg.e);
	++pc;
}
void Gameboy_Cpu::opc_adc_a_h() {
	adc(reg.a, reg.h);
	++pc;
}
void Gameboy_Cpu::opc_adc_a_l() {
	adc(reg.a, reg.l);
	++pc;
}
void Gameboy_Cpu::opc_adc_a_p_hl() {
	adc(reg.a, memory[reg.hl]);
	++pc;
}
void Gameboy_Cpu::opc_adc_a_n() {
	adc(reg.a, memory[pc+1]);
	pc += 2;
}

// subtract registers

void Gameboy_Cpu::opc_sub_a_a() {
	sub(reg.a, reg.a);
	++pc;
}
void Gameboy_Cpu::opc_sub_a_b() {
	sub(reg.a, reg.b);
	++pc;
}
void Gameboy_Cpu::opc_sub_a_c() {
	sub(reg.a, reg.c);
	++pc;
}
void Gameboy_Cpu::opc_sub_a_d() {
	sub(reg.a, reg.d);
	++pc;
}
void Gameboy_Cpu::opc_sub_a_e() {
	sub(reg.a, reg.e);
	++pc;
}
void Gameboy_Cpu::opc_sub_a_h() {
	sub(reg.a, reg.h);
	++pc;
}
void Gameboy_Cpu::opc_sub_a_l() {
	sub(reg.a, reg.l);
	++pc;
}
void Gameboy_Cpu::opc_sub_a_p_hl() {
	sub(reg.a, memory[reg.hl]);
	++pc;
}
void Gameboy_Cpu::opc_sub_a_n() {
	sub(reg.a, memory[pc]);
	++pc;
}

// subtract with carry

void Gameboy_Cpu::opc_sbc_a_a() {
	sbc(reg.a, reg.a);
	++pc;
}
void Gameboy_Cpu::opc_sbc_a_b() {
	sbc(reg.a, reg.a);
	++pc;
}
void Gameboy_Cpu::opc_sbc_a_c() {
	sbc(reg.a, reg.a);
	++pc;
}
void Gameboy_Cpu::opc_sbc_a_d() {
	sbc(reg.a, reg.a);
	++pc;
}
void Gameboy_Cpu::opc_sbc_a_e() {
	sbc(reg.a, reg.a);
	++pc;
}
void Gameboy_Cpu::opc_sbc_a_h() {
	sbc(reg.a, reg.a);
	++pc;
}
void Gameboy_Cpu::opc_sbc_a_l() {
	sbc(reg.a, reg.a);
	++pc;
}
void Gameboy_Cpu::opc_sbc_a_n() {
	sbc(reg.a, memory[pc+1]);
	pc += 2;
}
void Gameboy_Cpu::opc_sbc_a_p_hl() {
	sbc(reg.a, memory[reg.hl]);
	++pc;
}

// add 16 bit values

void Gameboy_Cpu::opc_add_hl_hl() {
	add16(reg.hl, reg.hl);
	++pc;
}
void Gameboy_Cpu::opc_add_hl_bc() {
	add16(reg.hl, reg.bc);
	++pc;
}
void Gameboy_Cpu::opc_add_hl_de() {
	add16(reg.hl, reg.de);
	++pc;
}
void Gameboy_Cpu::opc_add_hl_sp() {
	add16(reg.hl, sp);
	++pc;
}

// logical AND

void Gameboy_Cpu::opc_and_a_a() {
	logical_and(reg.a, reg.a);
	++pc;
}
void Gameboy_Cpu::opc_and_a_b() {
	logical_and(reg.a, reg.b);
	++pc;
}
void Gameboy_Cpu::opc_and_a_c() {
	logical_and(reg.a, reg.c);
	++pc;
}
void Gameboy_Cpu::opc_and_a_d() {
	logical_and(reg.a, reg.d);
	++pc;
}
void Gameboy_Cpu::opc_and_a_e() {
	logical_and(reg.a, reg.e);
	++pc;
}
void Gameboy_Cpu::opc_and_a_h() {
	logical_and(reg.a, reg.h);
	++pc;
}
void Gameboy_Cpu::opc_and_a_l() {
	logical_and(reg.a, reg.l);
	++pc;
}
void Gameboy_Cpu::opc_and_a_n() {
	logical_and(reg.a, memory[pc+1]);
	pc += 2;
}
void Gameboy_Cpu::opc_and_a_p_hl() {
	logical_and(reg.a, memory[reg.hl]);
	pc += 2;
}


// logical OR

void Gameboy_Cpu::opc_or_a_a() {
	logical_or(reg.a, reg.a);
	++pc;
}
void Gameboy_Cpu::opc_or_a_b() {
	logical_or(reg.a, reg.b);
	++pc;
}
void Gameboy_Cpu::opc_or_a_c() {
	logical_or(reg.a, reg.c);
	++pc;
}
void Gameboy_Cpu::opc_or_a_d() {
	logical_or(reg.a, reg.d);
	++pc;
}
void Gameboy_Cpu::opc_or_a_e() {
	logical_or(reg.a, reg.e);
	++pc;
}
void Gameboy_Cpu::opc_or_a_h() {
	logical_or(reg.a, reg.h);
	++pc;
}
void Gameboy_Cpu::opc_or_a_l() {
	logical_or(reg.a, reg.l);
	++pc;
}
void Gameboy_Cpu::opc_or_a_n() {
	logical_or(reg.a, memory[pc+1]);
	pc += 2;
}
void Gameboy_Cpu::opc_or_a_p_hl() {
	logical_or(reg.a, memory[reg.hl]);
	++pc;
}

// logical XOR

void Gameboy_Cpu::opc_xor_a_a() {
	logical_xor(reg.a, reg.a);
	++pc;
}
void Gameboy_Cpu::opc_xor_a_b() {
	logical_xor(reg.a, reg.b);
	++pc;
}
void Gameboy_Cpu::opc_xor_a_c() {
	logical_xor(reg.a, reg.c);
	++pc;
}
void Gameboy_Cpu::opc_xor_a_d() {
	logical_xor(reg.a, reg.d);
	++pc;
}
void Gameboy_Cpu::opc_xor_a_e() {
	logical_xor(reg.a, reg.e);
	++pc;
}
void Gameboy_Cpu::opc_xor_a_h() {
	logical_xor(reg.a, reg.h);
	++pc;
}
void Gameboy_Cpu::opc_xor_a_l() {
	logical_xor(reg.a, reg.l);
	++pc;
}
void Gameboy_Cpu::opc_xor_a_n() {
	logical_xor(reg.a, memory[pc+1]);
	pc += 2;
}
void Gameboy_Cpu::opc_xor_a_p_hl() {
	logical_xor(reg.a, memory[reg.hl]);
	++pc;
}

// compare against a

void Gameboy_Cpu::opc_cp_a_a() {
	compare(reg.a, reg.a);
	++pc;
}
void Gameboy_Cpu::opc_cp_a_b() {
	compare(reg.a, reg.b);
	++pc;
}
void Gameboy_Cpu::opc_cp_a_c() {
	compare(reg.a, reg.c);
	++pc;
}
void Gameboy_Cpu::opc_cp_a_d() {
	compare(reg.a, reg.d);
	++pc;
}
void Gameboy_Cpu::opc_cp_a_e() {
	compare(reg.a, reg.e);
	++pc;
}
void Gameboy_Cpu::opc_cp_a_h() {
	compare(reg.a, reg.h);
	++pc;
}
void Gameboy_Cpu::opc_cp_a_l() {
	compare(reg.a, reg.l);
	++pc;
}
void Gameboy_Cpu::opc_cp_a_n() {
	compare(reg.a, memory[pc+1]);
	pc += 2;
}
void Gameboy_Cpu::opc_cp_a_p_hl() {
	compare(reg.a, memory[reg.hl]);
	pc += 2;
}

// calling subroutine

void Gameboy_Cpu::opc_call_nn() {
	call_subroutine((memory[pc+1] << 8) | memory[pc+2]);
}
void Gameboy_Cpu::opc_call_nz_nn() {
	if (!get_flag(ZERO)) {
		call_subroutine((memory[pc+1] << 8) | memory[pc+2]);
	}
}
void Gameboy_Cpu::opc_call_nc_nn() {
	if (!get_flag(CARRY)) {
		call_subroutine((memory[pc+1] << 8) | memory[pc+2]);
	}
}
void Gameboy_Cpu::opc_call_z_nn() {
	if (get_flag(ZERO)) {
		call_subroutine((memory[pc+1] << 8) | memory[pc+2]);
	}
}
void Gameboy_Cpu::opc_call_c_nn() {
	if (get_flag(CARRY)) {
		call_subroutine((memory[pc+1] << 8) | memory[pc+2]);
	}
}

// return from subroutine

void Gameboy_Cpu::opc_ret() {
	return_subroutine();
}
void Gameboy_Cpu::opc_ret_nz() {
	if (!get_flag(ZERO)) {
		return_subroutine();
	}
}
void Gameboy_Cpu::opc_ret_nc() {
	if (!get_flag(CARRY)) {
		return_subroutine();
	}
}
void Gameboy_Cpu::opc_ret_z() {
	if (get_flag(ZERO)) {
		return_subroutine();
	}
}
void Gameboy_Cpu::opc_ret_n() {
	if (get_flag(CARRY)) {
		return_subroutine();
	}
}

// jumping to address

void Gameboy_Cpu::opc_jump_nn() {
	pc = (memory[pc+1] << 8) | memory[pc+2];
}
void Gameboy_Cpu::opc_jump_nz_nn() {
	if (!get_flag(ZERO)) {
		pc = (memory[pc+1] << 8) | memory[pc+2];
	}
}
void Gameboy_Cpu::opc_jump_nc_nn() {
	if (!get_flag(CARRY)) {
		pc = (memory[pc+1] << 8) | memory[pc+2];
	}
}
void Gameboy_Cpu::opc_jump_z_nn() {
	if (get_flag(ZERO)) {
		pc = (memory[pc+1] << 8) | memory[pc+2];
	}
}
void Gameboy_Cpu::opc_jump_c_nn() {
	if (get_flag(CARRY)) {
		pc = (memory[pc+1] << 8) | memory[pc+2];
	}
}
void Gameboy_Cpu::opc_jump_hl() {
	pc = reg.hl;
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

void Gameboy_Cpu::opc_bit_hl_0() { test_bit16(reg.hl, 0); }
void Gameboy_Cpu::opc_bit_hl_1() { test_bit16(reg.hl, 1); }
void Gameboy_Cpu::opc_bit_hl_2() { test_bit16(reg.hl, 2); }
void Gameboy_Cpu::opc_bit_hl_3() { test_bit16(reg.hl, 3); }
void Gameboy_Cpu::opc_bit_hl_4() { test_bit16(reg.hl, 4); }
void Gameboy_Cpu::opc_bit_hl_5() { test_bit16(reg.hl, 5); }
void Gameboy_Cpu::opc_bit_hl_6() { test_bit16(reg.hl, 6); }
void Gameboy_Cpu::opc_bit_hl_7() { test_bit16(reg.hl, 7); }

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

void Gameboy_Cpu::opc_set_hl_0() { set_bit((u8) reg.hl, 0); }
void Gameboy_Cpu::opc_set_hl_1() { set_bit((u8) reg.hl, 1); }
void Gameboy_Cpu::opc_set_hl_2() { set_bit((u8) reg.hl, 2); }
void Gameboy_Cpu::opc_set_hl_3() { set_bit((u8) reg.hl, 3); }
void Gameboy_Cpu::opc_set_hl_4() { set_bit((u8) reg.hl, 4); }
void Gameboy_Cpu::opc_set_hl_5() { set_bit((u8) reg.hl, 5); }
void Gameboy_Cpu::opc_set_hl_6() { set_bit((u8) reg.hl, 6); }
void Gameboy_Cpu::opc_set_hl_7() { set_bit((u8) reg.hl, 7); }

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

void Gameboy_Cpu::opc_reset_hl_0() { reset_bit((u8) reg.hl, 0); }
void Gameboy_Cpu::opc_reset_hl_1() { reset_bit((u8) reg.hl, 1); }
void Gameboy_Cpu::opc_reset_hl_2() { reset_bit((u8) reg.hl, 2); }
void Gameboy_Cpu::opc_reset_hl_3() { reset_bit((u8) reg.hl, 3); }
void Gameboy_Cpu::opc_reset_hl_4() { reset_bit((u8) reg.hl, 4); }
void Gameboy_Cpu::opc_reset_hl_5() { reset_bit((u8) reg.hl, 5); }
void Gameboy_Cpu::opc_reset_hl_6() { reset_bit((u8) reg.hl, 6); }
void Gameboy_Cpu::opc_reset_hl_7() { reset_bit((u8) reg.hl, 7); }


// bitshift right

void Gameboy_Cpu::opc_srl_a() {
	shift_right(reg.a);
	++pc;
}
void Gameboy_Cpu::opc_srl_b() {
	shift_right(reg.b);
	++pc;
}
void Gameboy_Cpu::opc_srl_c() {
	shift_right(reg.c);
	++pc;
}
void Gameboy_Cpu::opc_srl_d() {
	shift_right(reg.d);
	++pc;
}
void Gameboy_Cpu::opc_srl_e() {
	shift_right(reg.e);
	++pc;
}
void Gameboy_Cpu::opc_srl_h() {
	shift_right(reg.h);
	++pc;
}
void Gameboy_Cpu::opc_srl_l() {
	shift_right(reg.l);
	++pc;
}
void Gameboy_Cpu::opc_srl_p_hl() {
	shift_right(memory[reg.hl]);
	++pc;
}

// bitshift right, preserve sign

void Gameboy_Cpu::opc_sra_a() {
	shift_right_preserve_sign(reg.a);
	++pc;
}
void Gameboy_Cpu::opc_sra_b() {
	shift_right_preserve_sign(reg.b);
	++pc;
}
void Gameboy_Cpu::opc_sra_c() {
	shift_right_preserve_sign(reg.c);
	++pc;
}
void Gameboy_Cpu::opc_sra_d() {
	shift_right_preserve_sign(reg.d);
	++pc;
}
void Gameboy_Cpu::opc_sra_e() {
	shift_right_preserve_sign(reg.e);
	++pc;
}
void Gameboy_Cpu::opc_sra_h() {
	shift_right_preserve_sign(reg.h);
	++pc;
}
void Gameboy_Cpu::opc_sra_l() {
	shift_right_preserve_sign(reg.l);
	++pc;
}
void Gameboy_Cpu::opc_sra_p_hl() {
	shift_right_preserve_sign(memory[reg.hl]);
	++pc;
}

// bitshift left, preserve sign

void Gameboy_Cpu::opc_sla_a() {
	shift_left_preserve_sign(reg.a);
	++pc;
}
void Gameboy_Cpu::opc_sla_b() {
	shift_left_preserve_sign(reg.b);
	++pc;
}
void Gameboy_Cpu::opc_sla_c() {
	shift_left_preserve_sign(reg.c);
	++pc;
}
void Gameboy_Cpu::opc_sla_d() {
	shift_left_preserve_sign(reg.d);
	++pc;
}
void Gameboy_Cpu::opc_sla_e() {
	shift_left_preserve_sign(reg.e);
	++pc;
}
void Gameboy_Cpu::opc_sla_h() {
	shift_left_preserve_sign(reg.h);
	++pc;
}
void Gameboy_Cpu::opc_sla_l() {
	shift_left_preserve_sign(reg.l);
	++pc;
}
void Gameboy_Cpu::opc_sla_p_hl() {
	shift_left_preserve_sign(memory[reg.hl]);
	++pc;
}

// swap nybbles

void Gameboy_Cpu::swap_a() {
	swap(reg.a);
	++pc;
}
void Gameboy_Cpu::swap_b() {
	swap(reg.b);
	++pc;
}
void Gameboy_Cpu::swap_c() {
	swap(reg.c);
	++pc;
}
void Gameboy_Cpu::swap_d() {
	swap(reg.d);
	++pc;
}
void Gameboy_Cpu::swap_e() {
	swap(reg.e);
	++pc;
}
void Gameboy_Cpu::swap_h() {
	swap(reg.h);
	++pc;
}
void Gameboy_Cpu::swap_l() {
	swap(reg.l);
	++pc;
}
void Gameboy_Cpu::swap_p_hl() {
	swap(memory[reg.hl]);
	++pc;
}

// rotate right

void Gameboy_Cpu::rr_a() {
	rotate_right(reg.a);
	++pc;
}
void Gameboy_Cpu::rr_b() {
	rotate_right(reg.b);
	++pc;
}
void Gameboy_Cpu::rr_c() {
	rotate_right(reg.c);
	++pc;
}
void Gameboy_Cpu::rr_d() {
	rotate_right(reg.d);
	++pc;
}
void Gameboy_Cpu::rr_e() {
	rotate_right(reg.e);
	++pc;
}
void Gameboy_Cpu::rr_h() {
	rotate_right(reg.h);
	++pc;
}
void Gameboy_Cpu::rr_l() {
	rotate_right(reg.l);
	++pc;
}
void Gameboy_Cpu::rr_p_hl() {
	rotate_right(memory[reg.hl]);
	++pc;
}

// rotate left

void Gameboy_Cpu::rl_a() {
	rotate_left(reg.a);
	++pc;
}
void Gameboy_Cpu::rl_b() {
	rotate_left(reg.b);
	++pc;
}
void Gameboy_Cpu::rl_c() {
	rotate_left(reg.c);
	++pc;
}
void Gameboy_Cpu::rl_d() {
	rotate_left(reg.d);
	++pc;
}
void Gameboy_Cpu::rl_e() {
	rotate_left(reg.e);
	++pc;
}
void Gameboy_Cpu::rl_h() {
	rotate_left(reg.h);
	++pc;
}
void Gameboy_Cpu::rl_l() {
	rotate_left(reg.l);
	++pc;
}
void Gameboy_Cpu::rl_p_hl() {
	rotate_left(memory[reg.hl]);
	++pc;
}

// rotate right carry

void Gameboy_Cpu::rrc_a() {
	rotate_right_carry(reg.a);
	++pc;
}
void Gameboy_Cpu::rrc_b() {
	rotate_right_carry(reg.b);
	++pc;
}
void Gameboy_Cpu::rrc_c() {
	rotate_right_carry(reg.c);
	++pc;
}
void Gameboy_Cpu::rrc_d() {
	rotate_right_carry(reg.d);
	++pc;
}
void Gameboy_Cpu::rrc_e() {
	rotate_right_carry(reg.e);
	++pc;
}
void Gameboy_Cpu::rrc_h() {
	rotate_right_carry(reg.h);
	++pc;
}
void Gameboy_Cpu::rrc_l() {
	rotate_right_carry(reg.l);
	++pc;
}
void Gameboy_Cpu::rrc_p_hl() {
	rotate_right_carry(memory[reg.hl]);
	++pc;
}

// rotate left carry

void Gameboy_Cpu::rlc_a() {
	rotate_left_carry(reg.a);
	++pc;
}
void Gameboy_Cpu::rlc_b() {
	rotate_left_carry(reg.b);
	++pc;
}
void Gameboy_Cpu::rlc_c() {
	rotate_left_carry(reg.c);
	++pc;
}
void Gameboy_Cpu::rlc_d() {
	rotate_left_carry(reg.d);
	++pc;
}
void Gameboy_Cpu::rlc_e() {
	rotate_left_carry(reg.e);
	++pc;
}
void Gameboy_Cpu::rlc_h() {
	rotate_left_carry(reg.h);
	++pc;
}
void Gameboy_Cpu::rlc_l() {
	rotate_left_carry(reg.l);
	++pc;
}
void Gameboy_Cpu::rlc_p_hl() {
	rotate_left_carry(memory[reg.hl]);
	++pc;
}

// push 16bit onto stack

void Gameboy_Cpu::push_bc() {
	push(reg.bc);
	++pc;
}
void Gameboy_Cpu::push_de() {
	push(reg.de);
	++pc;
}
void Gameboy_Cpu::push_hl() {
	push(reg.hl);
	++pc;
}
void Gameboy_Cpu::push_af() {
	push(reg.af);
	++pc;
}

// pop 16bit from stack into register

void Gameboy_Cpu::pop_bc() {
	pop(reg.bc);
	++pc;
}
void Gameboy_Cpu::pop_de() {
	pop(reg.de);
	++pc;
}
void Gameboy_Cpu::pop_hl() {
	pop(reg.hl);
	++pc;
}
void Gameboy_Cpu::pop_af() {
	pop(reg.af);
	++pc;
}



// helper functions

void Gameboy_Cpu::set_flag(u8 flag) {
	switch (flag)
	{
		case 4: reg.f |= 1 << 4; break;
		case 5: reg.f |= 1 << 5; break;
		case 6: reg.f |= 1 << 6; break;
		case 7: reg.f |= 1 << 7; break;
		default: std::cout << "ERROR: invalid value for flag to be set.";
	}
}
void Gameboy_Cpu::reset_flag(u8 flag) {
	switch (flag)
	{
		case 4: reg.f &= ~(1 << 4); break;
		case 5: reg.f &= ~(1 << 5); break;
		case 6: reg.f &= ~(1 << 6); break;
		case 7: reg.f &= ~(1 << 7); break;
		default: std::cout << "ERROR: invalid value for flag to be unset.";
	}
}
bool Gameboy_Cpu::get_flag(u8 flag) {
	switch (flag)
	{
		case 4: return reg.f & 0x10; break;
		case 5: return reg.f & 0x20; break;
		case 6: return reg.f & 0x40; break;
		case 7: return reg.f & 0x80; break;
		default: std::cout << "ERROR: invalid value for flag!";
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

	++pc;
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
	sp -= 2;
	memory[sp] = pc >> 8;
	memory[sp+1] = pc;

	pc = address;
}

void Gameboy_Cpu::return_subroutine() {
	pc = (memory[sp] << 8) | memory[sp+1];
	sp += 2;
	//TODO: cinoop doesn't do this...check this
	pc += 3;
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
void Gameboy_Cpu::reset_bit(u8 &reg, u8 bit) {
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
	sp -= 2;
	memory[sp] = value >> 8;
	memory[sp+1] = value;
}

void Gameboy_Cpu::pop(u16 &reg) {
	reg = (memory[sp] << 8) | memory[sp+1];
	sp += 2;
}