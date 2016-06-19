cmake_minimum_required(VERSION 3.5)
project(gameboy_emu)


#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lncurses -lglut")

set(SOURCE_FILES main.cpp Gameboy_Cpu.cpp Gameboy_Cpu.h Gameboy_Logger.cpp Gameboy_Logger.h Gameboy_Debugger.cpp Gameboy_Debugger.h Gameboy_Registers.h Debug_Register.h Debug_Register.cpp Gameboy_Display.h Gameboy_Display.cpp)
add_executable(gameboy_emu ${SOURCE_FILES})

target_link_libraries(gameboy_emu ${OPENGL_LIBRARIES})