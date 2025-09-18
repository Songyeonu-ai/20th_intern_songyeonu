cmake_minimum_required(VERSION 3.10)
project(cv_hw1)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(cv_hw1 src/cv_hw1.cpp)
target_link_libraries(cv_hw1 ${OpenCV_LIBS})