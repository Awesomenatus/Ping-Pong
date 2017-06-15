cmake_minimum_required(VERSION 2.8)

project(ping-pong)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})



find_package(Curses REQUIRED)

if(NOT Curses_FOUND)

	message(SEND_ERROR "Failed to find ncurses")
	
	return()
	
endif()

include_directories(${CURSES_INCLUDE_DIR})

add_library(utility STATIC
            Platform.cpp
            Ball.cpp
            utility.cpp)
            
target_link_libraries(utility ${CURSES_LIBRARIES})

add_executable(${PROJECT_NAME} 
               Source.cpp)

target_link_libraries(${PROJECT_NAME} utility)

add_executable(${PROJECT_NAME}_tests
               class_playingfield_test.cpp
               ball_tests.cpp
               ping_pong_test_main.cpp)

target_link_libraries(${PROJECT_NAME}_tests ${GTEST_LIBRARIES} pthread utility)