//
// Created by michi on 07.06.16.
//

#include "Gameboy_Logger.h"

using namespace std;

Gameboy_Logger::Gameboy_Logger(string file) {
	logfile = file;
}

void Gameboy_Logger::log(string text) {
	ofstream file_logger;
	file_logger.open(logfile);

	cout << text;
	file_logger << text;
}
void Gameboy_Logger::log_line(string text) {
	ofstream file_logger;
	file_logger.open(logfile);

	cout << text;
	file_logger << text << "\n";
}

void Gameboy_Logger::log_time() {
	ofstream file_logger;
	file_logger.open(logfile);

	// format: hh:mm:ss - doing stuff \n
	time_t t = time(0);
	struct tm * now = localtime( & t);
	string log = to_string(now->tm_hour);
	log.append(":");
	log.append(to_string(now->tm_min));
	log.append(":");
	log.append(to_string(now->tm_sec));

	cout << log;
	file_logger << log;
}