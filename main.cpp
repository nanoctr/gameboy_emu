#include <iostream>
#include "Gameboy_Cpu.h"

using namespace std;



int main() {
	Gameboy_Cpu cpu;
	cpu.startup();


	for (int i = 0; i < 20; i++) {
		cpu.emulate_cycle();
	}

	//cpu.startup();
	return 0;
}

