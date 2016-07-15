#include <iostream>
#include "Gameboy_Cpu.h"
#include "Gameboy_Gpu.h"
#include "Gameboy_Debugger.h"
#include <string>
#include <stdlib.h>
#include <QApplication>

using namespace std;

Gameboy_Logger logger = Gameboy_Logger("/tmp/gameboy_cpu.log");

void debug();

int main(int argc, char **argv) {

#ifdef DEBUG_BUILD
	logger.log_line("\n\n--------------------");
	logger.log_line("DEBUG BUILD ENABLED");
	logger.log_line("\n--------------------");
	bool debugger = true;
#endif
	string input = "";
#ifndef DEBUG_BUILD
	bool debugger = false;
	cout << "Enable Debugger?" << endl;
	getline(cin, input);
	if (input == "y" || input == "yes") {
		debugger = true;
		logger.log_line("\n\n--------------------");
		logger.log_line("DEBUGGER ENABLED");
		logger.log_line("\n--------------------\n\n");

	}
#endif

	if (debugger) {
		Gameboy_Debugger emulator;
		emulator.run();
	}

	// debugger disabled, create emulator object, run
	//else {
	//	for (int i = 0; i < 30000; i++) {
	//			cpu.emulate_cycle();
	//		}
	//	}


	return 0;
}


