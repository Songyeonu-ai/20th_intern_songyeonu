cmake_minimum_required(VERSION 3.11)

project(hw3)

add_executable(test src/hw3.cpp) 
target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR}/include/hw3)

