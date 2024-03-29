//
// Created by michi on 07.06.16.
//

#include <sstream>
#include <iomanip>
#include "Gameboy_Logger.h"

using namespace std;

constexpr char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
						   '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

Gameboy_Logger::Gameboy_Logger(string file) {
	logfile = file;
	cout << "\n";
}

void Gameboy_Logger::log(string text) {
	ofstream file_logger;
	file_logger.open(logfile, ios_base::app);

	cout << text;
	file_logger << text;

	file_logger.close();
}
void Gameboy_Logger::log_line(string text) {
	ofstream file_logger;
	file_logger.open(logfile, ios_base::app);

	cout << text << "\n";
	file_logger << text << "\n";

	file_logger.close();
}

void Gameboy_Logger::log_time() {
	ofstream file_logger;
	file_logger.open(logfile, ios_base::app);

	// format: hh:mm:ss
	time_t t = time(0);
	struct tm * now = localtime(&t);
	string log = to_string(now->tm_hour);
	log.append(":");
	log.append(to_string(now->tm_min));
	log.append(":");
	log.append(to_string(now->tm_sec));

	cout << log;
	file_logger << log;

	file_logger.close();
}

string Gameboy_Logger::char_to_hex(u8 val) {
	string result(2, ' ');
	result[0] = hexmap[(val & 0xF0) >> 4];
	result[1] = hexmap[val & 0x0F];

	return result;
}
string Gameboy_Logger::short_to_hex(u16 val) {
	string result(4, ' ');
	result[0] = hexmap[(val & 0xF000) >> 12];
	result[1] = hexmap[(val & 0x0F00) >> 8];
	result[2] = hexmap[(val & 0x00F0) >> 4];
	result[3] = hexmap[val & 0x000F];

	return result;
}
string Gameboy_Logger::int_to_hex(int val) {
	string result(8, ' ');
	result[0] = hexmap[(val & 0xF0000000) >> 28];
	result[1] = hexmap[(val & 0x0F000000) >> 24];
	result[2] = hexmap[(val & 0x00F00000) >> 20];
	result[3] = hexmap[(val & 0x000F0000) >> 16];
	result[4] = hexmap[(val & 0x0000F000) >> 12];
	result[5] = hexmap[(val & 0x00000F00) >> 8];
	result[6] = hexmap[(val & 0x000000F0) >> 4];
	result[7] = hexmap[val & 0x0000000F];

	return result;
}