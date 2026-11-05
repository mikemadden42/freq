// Copyright 2016 Michael Madden

#include <array>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

namespace {

struct FileCloser {
    void operator()(std::FILE *file) const { std::fclose(file); }
};

}  // namespace

int main(int argc, char const *argv[]) {
    if (argc > 2) {
        std::cerr << "Usage: " << argv[0] << " [file]\n";
        return 1;
    }

    // Read stdin when no file is given or the file is "-". Reading goes
    // through C stdio because libc++'s std::cin is slow even when unsynced.
    std::unique_ptr<std::FILE, FileCloser> file;
    std::FILE *text = stdin;
    if (argc == 2 && std::string(argv[1]) != "-") {
        file.reset(std::fopen(argv[1], "r"));
        if (!file) {
            std::cerr << "Error opening file: " << argv[1] << '\n';
            return 1;
        }
        text = file.get();
    }

    // Count every byte in blocks, then fold the letters together once at
    // the end, keeping isalpha/toupper out of the hot loop.
    std::array<std::uint64_t, 256> bytes{};
    std::array<unsigned char, 1 << 16> buffer{};
    std::size_t n = 0;

    while ((n = std::fread(buffer.data(), 1, buffer.size(), text)) > 0) {
        for (std::size_t i = 0; i < n; ++i) {
            bytes[buffer[i]]++;
        }
    }

    if (std::ferror(text) != 0) {
        std::cerr << "Error reading input\n";
        return 1;
    }

    std::array<std::uint64_t, 256> counts{};
    for (std::size_t b = 0; b < bytes.size(); ++b) {
        if (std::isalpha(static_cast<int>(b)) == 0) {
            continue;
        }
        counts[static_cast<unsigned char>(std::toupper(static_cast<int>(b)))] +=
            bytes[b];
    }

    for (std::size_t i = 0; i < counts.size(); ++i) {
        if (counts[i] == 0) {
            continue;
        }
        std::cout << static_cast<char>(i) << ' ' << counts[i] << '\n';
    }

    return 0;
}
