cmake_minimum_required(VERSION 3.10)

project(freq CXX)

set (CMAKE_CXX_STANDARD 17)
if (NOT MSVC)
  set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
endif()

add_executable(freq freq.cc)
target_link_libraries(freq ${CORELIBS})

enable_testing()

set(RUN_TEST ${CMAKE_CURRENT_SOURCE_DIR}/tests/run_test.cmake)

add_test(NAME counts_ascii_letters_only
  COMMAND ${CMAKE_COMMAND}
    -DEXE=$<TARGET_FILE:freq>
    -DARGS=${CMAKE_CURRENT_SOURCE_DIR}/tests/mixed.txt
    -DEXPECTED_RC=0
    -DEXPECTED_OUTPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/mixed.expected
    -P ${RUN_TEST})

add_test(NAME no_args_prints_usage
  COMMAND ${CMAKE_COMMAND}
    -DEXE=$<TARGET_FILE:freq>
    -DEXPECTED_RC=1
    -DEXPECTED_REGEX=^Usage:
    -P ${RUN_TEST})

add_test(NAME missing_file_reports_error
  COMMAND ${CMAKE_COMMAND}
    -DEXE=$<TARGET_FILE:freq>
    -DARGS=${CMAKE_CURRENT_SOURCE_DIR}/tests/does-not-exist.txt
    -DEXPECTED_RC=1
    -DEXPECTED_REGEX=^Error\ opening\ file:
    -P ${RUN_TEST})
