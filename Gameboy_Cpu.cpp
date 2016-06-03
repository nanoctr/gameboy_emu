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

// sub registers
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

// sub with carry
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
void Gameboy_Cpu::unset_flag(u8 flag) {
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
		unset_flag(CARRY);
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
		unset_flag(ZERO);
	}

	// unset subtraction flag
	unset_flag(SUBTRACT);

	++pc;
}
void Gameboy_Cpu::add16(u16 &a, u16 b) {
	unsigned int result = a + b;
	// set carry flag?
	if (result & 0xFFFF0000) {
		set_flag(CARRY);
	}
	else {
		unset_flag(CARRY);
	}

	a = (u16) (result & 0xFFFF);

	// set half carry flag?
	if (((a & 0x0f) + (b & 0x0f)) > 0x0f) {
		set_flag(HALF_CARRY);
	}
	else {
		unset_flag(HALF_CARRY);
	}

	if (result == 0) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}

	unset_flag(SUBTRACT);
}

//TODO: pass this shit by value
void Gameboy_Cpu::inc(u8 &val) {
	if ((val & 0x0f) == 0x0f) {
		set_flag(HALF_CARRY);
	}
	else {
		unset_flag(HALF_CARRY);
	}

	++val;

	if (val) {
		unset_flag(ZERO);
	}
	else {
		set_flag(ZERO);
	}

	unset_flag(SUBTRACT);
}
void Gameboy_Cpu::dec(u8 &val) {
	if (val & 0x0f) {
		unset_flag(HALF_CARRY);
	}
	else {
		set_flag(HALF_CARRY);
	}

	--val;

	if (val) {
		unset_flag(ZERO);
	}
	else {
		set_flag(ZERO);
	}

	set_flag(SUBTRACT);
}
// TODO: check this, not sure about the way this is supposed to work
void Gameboy_Cpu::dec16(u16 &val) {
	if (val & 0x000f) {
		unset_flag(HALF_CARRY);
	}
	else {
		set_flag(HALF_CARRY);
	}

	--val;

	if (val) {
		unset_flag(ZERO);
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
		unset_flag(HALF_CARRY);
	}

	++val;

	if (val) {
		unset_flag(ZERO);
	}
	else {
		set_flag(ZERO);
	}

	unset_flag(ZERO);
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
		unset_flag(CARRY);
	}

	// set half carry flag
	if ((b & 0x0f) > (a & 0x0f)) {
		set_flag(HALF_CARRY);
	}
	else {
		unset_flag(HALF_CARRY);
	}

	// compute and store result
	a -= b;

	// set zero flag
	if (a == 0) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}

	// set subtract flag
	set_flag(SUBTRACT);
}

void Gameboy_Cpu::sbc(u8 &a, u8 b) {
	 sub(a, b+get_flag(CARRY));
}

void Gameboy_Cpu::logical_and(u8 &a, u8 b) {
	unset_flag(CARRY);
	unset_flag(SUBTRACT);
	set_flag(HALF_CARRY);

	a &= b;
	if (a == 0) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}
}

void Gameboy_Cpu::logical_or(u8 &a, u8 b) {
	unset_flag(CARRY);
	unset_flag(HALF_CARRY);
	unset_flag(SUBTRACT);

	a |= b;
	if (a == 0) {
		set_flag(ZERO);
	}
	else {
		unset_flag(ZERO);
	}
}