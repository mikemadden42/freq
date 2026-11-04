# freq

Frequency analysis utility: counts how often each letter appears in a text.

Letters are counted case-insensitively (`a` and `A` both count as `A`).
Only ASCII letters are counted; digits, punctuation, whitespace, control
characters and non-ASCII bytes are ignored.

## Building

With CMake:

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

The binary is `build/freq`.

Or with make, which builds `freq` in the current directory:

```sh
make
```

## Usage

```sh
freq [file]
```

`freq` reads `file`, or stdin if no file is given or the file is `-`. It
prints one line per letter that appears, in alphabetical order, with the
letter and its count. Usage and error messages go to stderr, and the exit
code is 1 on error.

## Example

```console
$ echo "Hello, World!" | freq
D 1
E 1
H 1
L 3
O 2
R 1
W 1
```

## Testing

```sh
cmake -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## License

Apache License 2.0. See [LICENSE](LICENSE).
