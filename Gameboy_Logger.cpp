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

	// format: hh:mm:ss - doing stuff \n
	time_t t = time(0);
	struct tm * now = localtime( & t);
	string log = to_string(now->tm_hour);
	log.append(":");
	log.append(to_string(now->tm_min));
	log.append(":");
	log.append(to_string(now->tm_sec));
	log.append(" - ");
	log.append(text);
	log.append("\n");

	cout << text;
	file_logger << text;
}