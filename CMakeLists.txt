cmake_minimum_required(VERSION 3.5)
project(gameboy_emu)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lncurses")

set(SOURCE_FILES main.cpp Gameboy_Cpu.cpp Gameboy_Cpu.h Gameboy_Logger.cpp Gameboy_Logger.h Gameboy_Debugger.cpp Gameboy_Debugger.h Gameboy_Registers.h Debug_Register.h Debug_Register.cpp)
add_executable(gameboy_emu ${SOURCE_FILES})