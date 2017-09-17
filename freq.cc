// Copyright 2016 Michael Madden

#include <cctype>
#include <fstream>
#include <iostream>
#include <map>

int main(int argc, char const *argv[]) {
    std::ifstream text(argv[1]);
    std::map<char, int> freqmap;
    char c;

    if (argc == 1) {
        std::cout << "Usage: " << argv[0] << " file" << std::endl;
        exit(1);
    }

    if (!text) {
        std::cout << "Eror opening file: " << argv[1] << std::endl;
        exit(1);
    }

    while (text.get(c)) {
        if (isspace(c) || ispunct(c) || isdigit(c))
            continue;

        freqmap[tolower(c)]++;
    }

    for (auto const &ent : freqmap) {
        std::cout << ent.first << " " << ent.second << std::endl;
    }

    text.close();

    return 0;
}
