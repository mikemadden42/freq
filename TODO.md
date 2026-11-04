# TODO

Findings from a project review (2026-11-04).

## Bugs in `freq.cc`

- [x] **`argv[1]` is read before `argc` is checked.** `std::ifstream text(argv[1])`
      runs before the usage check, so with no arguments it receives `nullptr`
      (undefined behaviour; libc++ tolerates it, libstdc++ may crash). Open the
      file after the `argc` check.
- [x] **Non-ASCII input causes undefined behaviour and messy output.**
      `isspace`/`ispunct`/`isdigit` are passed a plain `char`; bytes >= 0x80 are
      negative where `char` is signed, which is UB. Each UTF-8 byte is also
      counted as its own "letter", and control characters slip through. Keep
      characters where `std::isalpha(static_cast<unsigned char>(c))` is true
      instead of excluding categories.
- [x] **Missing includes:** add `<locale>` (for `std::locale` and two-argument
      `toupper`) and `<cstdlib>` (for `exit`).

## Smaller code improvements

- [x] Send usage and error messages to `std::cerr` instead of `stdout`.
- [x] Use `std::uint64_t` counts (an `int` overflows on inputs over ~2 GB);
      consider `std::array<std::uint64_t, 256>` instead of `std::map`.
- [x] ~~Construct `std::locale()` once outside the loop.~~ No longer applies:
      `std::locale` was dropped in favour of `<cctype>` `std::toupper`.
- [x] Use `'\n'` instead of `std::endl`.
- [x] Replace `exit(1)` in `main` with `return 1`; drop the redundant
      `text.close()`.
- [x] Read from stdin when no file is given.

## Build and CI

- [x] CI runs `ctest`, but no tests are defined (no `enable_testing()` /
      `add_test()`); on recent CMake `ctest` exits 1 with "No test configuration
      file found!". Add a test (fixture file + expected output) or remove the step.
- [x] Replace `set(CMAKE_CXX_FLAGS ...)` with
      `target_compile_options(freq PRIVATE -Wall -Wextra -pedantic)` and add
      `set(CMAKE_CXX_STANDARD_REQUIRED ON)`.
- [x] Remove `target_link_libraries(freq ${CORELIBS})` (`CORELIBS` is undefined).
- [x] Bump `actions/checkout@v3` to v4 or later.
- [x] Add a sanitizer (ASan/UBSan) build to CI.
- [ ] Add clang-tidy / clang-format checks to CI.

## Makefile and repo

- [ ] Use `CXX`/`CXXFLAGS` instead of `CC`/`CFLAGS`.
- [ ] Use `rm -f` in `clean` and add `.PHONY: all clean`.
- [ ] Add the in-tree `freq` binary to `.gitignore`.
- [ ] Expand the README with build instructions and a usage example.
