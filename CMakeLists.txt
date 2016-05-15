cmake_minimum_required(VERSION 3.5)
project(testcpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lcpprest -Wall")
set(SOURCE_FILES main.cpp result.h result.cpp result.h)

link_libraries(cpprest boost_program_options)
add_executable(testcpp ${SOURCE_FILES})