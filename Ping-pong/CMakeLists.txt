cmake_minimum_required(VERSION 2.8)

project(ping-pong)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")

set (CMAKE_BUILD_TYPE Debug)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

find_package(Boost 1.58.0 REQUIRED system)

find_package(Curses REQUIRED)

if(NOT Curses_FOUND)

  message(SEND_ERROR "Failed to find ncurses")
	
  return()
	
endif()

include_directories(${CURSES_INCLUDE_DIR})

add_library(utility STATIC
            game_settings.cpp
            game_object.cpp
            Platform.cpp
            platform_controller.cpp
            playing_field.cpp
            Ball.cpp
            network.cpp
            utility.cpp)
            
target_link_libraries(utility ${CURSES_LIBRARIES} ${Boost_LIBRARIES} pthread)

add_executable(${PROJECT_NAME} 
               Source.cpp)

target_link_libraries(${PROJECT_NAME} utility)

add_executable(${PROJECT_NAME}_tests
               class_playingfield_test.cpp
               ball_tests.cpp
               ping_pong_test_main.cpp)

target_link_libraries(${PROJECT_NAME}_tests ${GTEST_LIBRARIES} utility)