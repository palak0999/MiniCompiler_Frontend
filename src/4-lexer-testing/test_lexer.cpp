#include <iostream>
#include <fstream>
#include <vector>
#include "token.h"

// Declaration of tokenize() from lexer.cpp
std::vector<Token> tokenize(std::istream &in);

int main() {
    std::ifstream in("input.mc");
    if (!in) {
        std::cerr << "Error: input.mc not found\n";
        return 1;
    }

    std::vector<Token> tokens = tokenize(in);

    std::cout << "=== LEXER TEST OUTPUT ===\n";
    for (const auto &t : tokens) {
        std::cout << t.type << " " << t.lexeme << " line " << t.line << "\n";
    }

    return 0;
}
