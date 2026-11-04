// Copyright 2016 Michael Madden

#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>

int main(int argc, char const *argv[]) {
    std::map<char, int> map;
    char c;

    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " file" << std::endl;
        exit(1);
    }

    std::ifstream text(argv[1]);
    if (!text) {
        std::cout << "Error opening file: " << argv[1] << std::endl;
        exit(1);
    }

    while (text.get(c)) {
        auto const uc = static_cast<unsigned char>(c);
        if (!std::isalpha(uc)) continue;

        map[static_cast<char>(std::toupper(uc))]++;
    }

    for (auto const &ent : map) {
        std::cout << ent.first << " " << ent.second << std::endl;
    }

    text.close();

    return 0;
}
