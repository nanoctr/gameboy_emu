//
// Created by michi on 17.06.16.
//

#ifndef GAMEBOY_EMU_GAMEBOY_REGISTERS_H
#define GAMEBOY_EMU_GAMEBOY_REGISTERS_H

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
using u8 = unsigned char;
using u16 = unsigned short;

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

	u16 pc = 0;
	u16 sp = 0xFFFE;
};


#endif //GAMEBOY_EMU_GAMEBOY_REGISTERS_H
