cmake_minimum_required(VERSION 3.10)

project(modern_cc CXX)

set (CMAKE_CXX_STANDARD 14)
if (NOT MSVC)
  set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -march=native")
endif()

add_executable(freq freq.cc)
target_link_libraries(freq ${CORELIBS})
