# Runs freq and checks its exit code and, optionally, its stdout.
#   EXE              path to the freq binary
#   ARGS             arguments to pass (may be empty)
#   EXPECTED_RC      expected exit code
#   EXPECTED_OUTPUT  file whose contents must match stdout exactly (optional)
#   EXPECTED_REGEX   regex stdout must match (optional)

execute_process(
  COMMAND ${EXE} ${ARGS}
  RESULT_VARIABLE rc
  OUTPUT_VARIABLE out)

if (NOT rc STREQUAL EXPECTED_RC)
  message(FATAL_ERROR "exit code: expected ${EXPECTED_RC}, got ${rc}\n${out}")
endif()

if (DEFINED EXPECTED_OUTPUT)
  file(READ ${EXPECTED_OUTPUT} expected)
  if (NOT out STREQUAL expected)
    message(FATAL_ERROR "output mismatch\n--- expected\n${expected}--- got\n${out}")
  endif()
endif()

if (DEFINED EXPECTED_REGEX AND NOT out MATCHES "${EXPECTED_REGEX}")
  message(FATAL_ERROR "output does not match '${EXPECTED_REGEX}':\n${out}")
endif()
