cmake_minimum_required(VERSION 2.8)

project(modern_cc CXX)

add_definitions(-Wall -O2 -std=c++14 -march=native)

add_executable(freq freq.cc)
target_link_libraries(freq ${CORELIBS})
