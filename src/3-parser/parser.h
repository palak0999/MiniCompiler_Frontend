#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

struct Token {
    std::string type;      // e.g., INT, ID, NUM, PRINT
    std::string lexeme;    // actual text of token
    int line;              // line number
};

// Main function to start parsing
void parseProgram();

// Sub-functions
void parseStatement();
void parseDeclaration();
void parseAssignment();
void parsePrint();
void parseIf();
void parseWhile();

void parseExpression();
void parseTerm();
void parseFactor();

#endif
