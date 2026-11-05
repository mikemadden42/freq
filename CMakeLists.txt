cmake_minimum_required(VERSION 3.10)

project(freq CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(freq freq.cc)
if (MSVC)
  target_compile_options(freq PRIVATE /W4)
else()
  target_compile_options(freq PRIVATE -Wall -Wextra -pedantic)
endif()

enable_testing()

set(RUN_TEST ${CMAKE_CURRENT_SOURCE_DIR}/tests/run_test.cmake)

add_test(NAME counts_ascii_letters_only
  COMMAND ${CMAKE_COMMAND}
    -DEXE=$<TARGET_FILE:freq>
    -DARGS=${CMAKE_CURRENT_SOURCE_DIR}/tests/mixed.txt
    -DEXPECTED_RC=0
    -DEXPECTED_OUTPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/mixed.expected
    -P ${RUN_TEST})

add_test(NAME no_args_reads_stdin
  COMMAND ${CMAKE_COMMAND}
    -DEXE=$<TARGET_FILE:freq>
    -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/mixed.txt
    -DEXPECTED_RC=0
    -DEXPECTED_OUTPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/mixed.expected
    -P ${RUN_TEST})

add_test(NAME dash_reads_stdin
  COMMAND ${CMAKE_COMMAND}
    -DEXE=$<TARGET_FILE:freq>
    -DARGS=-
    -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/mixed.txt
    -DEXPECTED_RC=0
    -DEXPECTED_OUTPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/mixed.expected
    -P ${RUN_TEST})

add_test(NAME too_many_args_prints_usage
  COMMAND ${CMAKE_COMMAND}
    -DEXE=$<TARGET_FILE:freq>
    -DARGS=a$<SEMICOLON>b
    -DEXPECTED_RC=1
    -DEXPECTED_OUTPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/empty.expected
    -DEXPECTED_STDERR_REGEX=^Usage:
    -P ${RUN_TEST})

add_test(NAME missing_file_reports_error
  COMMAND ${CMAKE_COMMAND}
    -DEXE=$<TARGET_FILE:freq>
    -DARGS=${CMAKE_CURRENT_SOURCE_DIR}/tests/does-not-exist.txt
    -DEXPECTED_RC=1
    -DEXPECTED_OUTPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/empty.expected
    -DEXPECTED_STDERR_REGEX=^Error\ opening\ file:
    -P ${RUN_TEST})

add_test(NAME directory_reports_error
  COMMAND ${CMAKE_COMMAND}
    -DEXE=$<TARGET_FILE:freq>
    -DARGS=${CMAKE_CURRENT_SOURCE_DIR}/tests
    -DEXPECTED_RC=1
    -DEXPECTED_OUTPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/empty.expected
    "-DEXPECTED_STDERR_REGEX=^Error (opening file|reading input)"
    -P ${RUN_TEST})
