cmake_minimum_required(VERSION 3.17)
project(Lab_2_4)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab_2_4_v1 v1/main.cpp v1/classes.cpp v1/classes.h)

add_executable(Test_generator "test generator/main.cpp" "test generator/HTTPRequest.hpp")
