cmake_minimum_required(VERSION 3.5)
project(gameboy_emu)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Gameboy_Cpu.cpp Gameboy_Cpu.h)
add_executable(gameboy_emu ${SOURCE_FILES})