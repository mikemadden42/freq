// Copyright 2016 Michael Madden

#include <cctype>
#include <fstream>
#include <iostream>
#include <map>

int main(int argc, char const *argv[]) {
    std::ifstream text(argv[1]);
    std::map<char, int> map;
    char c;

    if (argc == 1) {
        std::cout << "Usage: " << argv[0] << " file" << std::endl;
        exit(1);
    }

    if (!text) {
        std::cout << "Error opening file: " << argv[1] << std::endl;
        exit(1);
    }

    while (text.get(c)) {
        if (isspace(c) || ispunct(c) || isdigit(c)) continue;

        map[toupper(c, std::locale())]++;
    }

    for (auto const &ent : map) {
        std::cout << ent.first << " " << ent.second << std::endl;
    }

    text.close();

    return 0;
}
