cmake_minimum_required(VERSION 2.8)

project(Ping-Pong)

set(SOURCE_EXE Source.cpp Ball.cpp Platform.cpp)

find_package(Curses REQUIRED)

if(NOT Curses_FOUND)

	message(SEND_ERROR "Failed to find ncurses")
	
	return()
	
endif()

include_directories(${CURSES_INCLUDE_DIR})

add_executable(source ${SOURCE_EXE})

target_link_libraries(source ${CURSES_LIBRARIES})

