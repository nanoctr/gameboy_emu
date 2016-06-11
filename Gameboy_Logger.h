//
// Created by michi on 07.06.16.
//

#include <string>
#include <iostream>
#include <fstream>

#ifndef GAMEBOY_EMU_GAMEBOY_LOGGER_H
#define GAMEBOY_EMU_GAMEBOY_LOGGER_H

using namespace std;

class Gameboy_Logger {
private:
	string logfile;
public:
	Gameboy_Logger(string file);
	void log(string text);
	void log_time();
	void log_line(string text);
};


#endif //GAMEBOY_EMU_GAMEBOY_LOGGER_H
