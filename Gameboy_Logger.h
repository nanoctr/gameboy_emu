//
// Created by michi on 07.06.16.
//

#include <string>
#include <iostream>
#include <fstream>

#ifndef GAMEBOY_EMU_GAMEBOY_LOGGER_H
#define GAMEBOY_EMU_GAMEBOY_LOGGER_H

using namespace std;

typedef unsigned char u8;
typedef unsigned short u16;

class Gameboy_Logger {
private:
	string logfile;
public:
	Gameboy_Logger(string file);
	void log(string text);
	void log_time();
	void log_line(string text);
	string char_to_hex(u8 val);
	string short_to_hex(u16 val);
};


#endif //GAMEBOY_EMU_GAMEBOY_LOGGER_H
