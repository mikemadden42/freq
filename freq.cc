// Copyright 2016 Michael Madden

#include <array>
#include <cctype>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
    if (argc > 2) {
        std::cerr << "Usage: " << argv[0] << " [file]\n";
        return 1;
    }

    // Read stdin when no file is given or the file is "-".
    std::ifstream file;
    std::istream *text = &std::cin;
    if (argc == 2 && std::string(argv[1]) != "-") {
        file.open(argv[1]);
        if (!file) {
            std::cerr << "Error opening file: " << argv[1] << '\n';
            return 1;
        }
        text = &file;
    }

    std::array<std::uint64_t, 256> counts{};
    char c;

    while (text->get(c)) {
        auto const uc = static_cast<unsigned char>(c);
        if (std::isalpha(uc) == 0) {
            continue;
        }

        counts[static_cast<unsigned char>(std::toupper(uc))]++;
    }

    for (std::size_t i = 0; i < counts.size(); ++i) {
        if (counts[i] == 0) {
            continue;
        }
        std::cout << static_cast<char>(i) << ' ' << counts[i] << '\n';
    }

    return 0;
}
