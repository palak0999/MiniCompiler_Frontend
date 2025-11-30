#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
#include "token.h"

bool isLetter(char c) {
    return std::isalpha(static_cast<unsigned char>(c));
}

bool isDigit(char c) {
    return std::isdigit(static_cast<unsigned char>(c));
}

bool isKeyword(const std::string &word) {
    return (word == "int" || word == "print" || word == "if" || word == "while");
}

std::string keywordType(const std::string &word) {
    if (word == "int")   return "INT";
    if (word == "print") return "PRINT";
    if (word == "if")    return "IF";
    if (word == "while") return "WHILE";
    return "ID";
}

std::vector<Token> tokenize(std::istream &in) {
    std::vector<Token> tokens;
    std::string line;
    int lineNo = 0;

    while (std::getline(in, line)) {
        lineNo++;
        size_t i = 0;

        while (i < line.size()) {
            char c = line[i];

            // Whitespace ignore
            if (std::isspace((unsigned char)c)) {
                i++;
                continue;
            }

            // Identifier or keyword
            if (isLetter(c)) {
                std::string word;
                while (i < line.size() && (isLetter(line[i]) || isDigit(line[i]))) {
                    word.push_back(line[i]);
                    i++;
                }
                Token t;
                t.type = isKeyword(word) ? keywordType(word) : "ID";
                t.lexeme = word;
                t.line = lineNo;
                tokens.push_back(t);
                continue;
            }

            // Number
            if (isDigit(c)) {
                std::string number;
                while (i < line.size() && isDigit(line[i])) {
                    number.push_back(line[i]);
                    i++;
                }
                Token t{"NUM", number, lineNo};
                tokens.push_back(t);
                continue;
            }

            // == operator
            if (c == '=' && i + 1 < line.size() && line[i+1] == '=') {
                tokens.push_back({"EQ", "==", lineNo});
                i += 2;
                continue;
            }

            // Single character tokens
            Token t;
            t.line = lineNo;

            switch (c) {
                case '+': t = {"PLUS", "+", lineNo}; break;
                case '-': t = {"MINUS", "-", lineNo}; break;
                case '*': t = {"MULT", "*", lineNo}; break;
                case '/': t = {"DIV", "/", lineNo}; break;
                case '=': t = {"ASSIGN", "=", lineNo}; break;
                case ';': t = {"SEMICOLON", ";", lineNo}; break;
                case '(': t = {"LPAREN", "(", lineNo}; break;
                case ')': t = {"RPAREN", ")", lineNo}; break;
                case '{': t = {"LBRACE", "{", lineNo}; break;
                case '}': t = {"RBRACE", "}", lineNo}; break;

                default:
                    t = {"INVALID", std::string(1, c), lineNo};
            }

            tokens.push_back(t);
            i++;
        }
    }

    return tokens;
}

int main() {
    std::ifstream in("input.mc");
    if (!in) {
        std::cerr << "Cannot open input file\n";
        return 1;
    }

    std::vector<Token> tokens = tokenize(in);

    std::ofstream out("tokens_output.txt");
    for (const auto &t : tokens) {
        out << t.type << " " << t.lexeme << " line " << t.line << "\n";
    }

    return 0;
}
