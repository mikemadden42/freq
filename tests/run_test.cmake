# Runs freq and checks its exit code and, optionally, its stdout and stderr.
#   EXE                    path to the freq binary
#   ARGS                   arguments to pass (may be empty)
#   INPUT                  file to feed on stdin (default: empty input)
#   EXPECTED_RC            expected exit code
#   EXPECTED_OUTPUT        file whose contents must match stdout exactly (optional)
#   EXPECTED_STDERR_REGEX  regex stderr must match (optional)

# Use an empty file rather than /dev/null, which doesn't exist on Windows.
if (NOT DEFINED INPUT)
  set(INPUT ${CMAKE_CURRENT_BINARY_DIR}/empty-input)
  file(WRITE ${INPUT} "")
endif()

execute_process(
  COMMAND ${EXE} ${ARGS}
  INPUT_FILE ${INPUT}
  RESULT_VARIABLE rc
  OUTPUT_VARIABLE out
  ERROR_VARIABLE err)

# Windows writes CRLF line endings in text mode; compare with LF only.
string(REPLACE "\r\n" "\n" out "${out}")
string(REPLACE "\r\n" "\n" err "${err}")

if (NOT rc STREQUAL EXPECTED_RC)
  message(FATAL_ERROR "exit code: expected ${EXPECTED_RC}, got ${rc}\n${out}${err}")
endif()

if (DEFINED EXPECTED_OUTPUT)
  file(READ ${EXPECTED_OUTPUT} expected)
  string(REPLACE "\r\n" "\n" expected "${expected}")
  if (NOT out STREQUAL expected)
    message(FATAL_ERROR "output mismatch\n--- expected\n${expected}--- got\n${out}")
  endif()
endif()

if (DEFINED EXPECTED_STDERR_REGEX AND NOT err MATCHES "${EXPECTED_STDERR_REGEX}")
  message(FATAL_ERROR "stderr does not match '${EXPECTED_STDERR_REGEX}':\n${err}")
endif()
