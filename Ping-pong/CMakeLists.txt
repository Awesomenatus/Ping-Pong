cmake_minimum_required(VERSION 2.8)

project(Ping-Pong)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_library(Ball STATIC Ball.cpp)

set(SOURCE_EXE Source.cpp Platform.cpp draw.cpp fill_vector.cpp)

find_package(Curses REQUIRED)

if(NOT Curses_FOUND)

	message(SEND_ERROR "Failed to find ncurses")
	
	return()
	
endif()

include_directories(${CURSES_INCLUDE_DIR})

add_executable(source ${SOURCE_EXE} )

target_link_libraries(source ${CURSES_LIBRARIES} Ball)

add_executable(runTests ball_tests.cpp ping_pong_test_main.cpp )

target_link_libraries(runTests ${GTEST_LIBRARIES} pthread Ball)