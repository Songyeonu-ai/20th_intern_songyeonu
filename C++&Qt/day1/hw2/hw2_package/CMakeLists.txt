cmake_minimum_required(VERSION 3.11)

project(hw2)

add_executable(test src/hw2.cpp) 	
target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR}/include/hw2)
