#include <iostream>
#include <fstream>
#include <vector>
#include "parser.h"

using namespace std;

vector<Token> tokens;
int currentIndex = 0;
bool hadError = false;

Token currentToken() {
    if (currentIndex < (int)tokens.size()) {
        return tokens[currentIndex];
    }
    return {"EOF", "EOF", tokens.empty() ? 0 : tokens.back().line};
}

void advance() {
    if (currentIndex < (int)tokens.size()) {
        currentIndex++;
    }
}

bool match(const string &expectedType) {
    if (currentToken().type == expectedType) {
        advance();
        return true;
    }
    return false;
}

void error(const string &msg) {
    hadError = true;
    Token t = currentToken();
    cerr << "Syntax error at line " << t.line 
         << ": " << msg 
         << " (found '" << t.type << "')" << endl;

    advance();
}

void parseProgram() {
    while (currentToken().type != "EOF") {
        parseStatement();
    }
}

void parseStatement() {
    Token t = currentToken();

    if (t.type == "INT") parseDeclaration();
    else if (t.type == "ID") parseAssignment();
    else if (t.type == "PRINT") parsePrint();
    else if (t.type == "IF") parseIf();
    else if (t.type == "WHILE") parseWhile();
    else if (t.type == "EOF") return;
    else error("Unknown statement");
}

void parseDeclaration() {
    match("INT") ? void() : error("Expected 'INT'");
    match("ID") ? void() : error("Expected identifier");
    match("SEMICOLON") ? void() : error("Missing ';'");
}

void parseAssignment() {
    match("ID") ? void() : error("Expected identifier");
    match("ASSIGN") ? void() : error("Expected '='");
    parseExpression();
    match("SEMICOLON") ? void() : error("Missing ';'");
}

void parsePrint() {
    match("PRINT") ? void() : error("Expected 'print'");
    match("LPAREN") ? void() : error("Expected '('");
    match("ID") ? void() : error("Expected identifier");
    match("RPAREN") ? void() : error("Expected ')'");
    match("SEMICOLON") ? void() : error("Missing ';'");
}

void parseIf() {
    match("IF") ? void() : error("Expected 'if'");
    match("LPAREN") ? void() : error("Expected '('");
    match("ID") ? void() : error("Expected identifier");
    match("EQ") ? void() : error("Expected '=='");
    parseExpression();
    match("RPAREN") ? void() : error("Expected ')'");
    match("LBRACE") ? void() : error("Expected '{'");

    while (currentToken().type != "RBRACE" && currentToken().type != "EOF") {
        parseStatement();
    }

    match("RBRACE") ? void() : error("Expected '}'");
}

void parseWhile() {
    match("WHILE") ? void() : error("Expected 'while'");
    match("LPAREN") ? void() : error("Expected '('");
    match("ID") ? void() : error("Expected identifier");
    match("EQ") ? void() : error("Expected '=='");
    parseExpression();
    match("RPAREN") ? void() : error("Expected ')'");
    match("LBRACE") ? void() : error("Expected '{'");

    while (currentToken().type != "RBRACE" && currentToken().type != "EOF") {
        parseStatement();
    }

    match("RBRACE") ? void() : error("Expected '}'");
}

void parseExpression() {
    parseTerm();
    while (currentToken().type == "PLUS" || currentToken().type == "MINUS") {
        advance();
        parseTerm();
    }
}

void parseTerm() {
    parseFactor();
    while (currentToken().type == "MULT" || currentToken().type == "DIV") {
        advance();
        parseFactor();
    }
}

void parseFactor() {
    if (currentToken().type == "NUM" || currentToken().type == "ID") {
        advance();
    } else {
        error("Expected number or identifier");
    }
}

int main() {
    ifstream in("tokens_output.txt");
    if (!in) {
        cerr << "Cannot open tokens_output.txt\n";
        return 1;
    }

    string type, lexeme;
    int line;

    while (in >> type >> lexeme >> line) {
        tokens.push_back({type, lexeme, line});
    }

    parseProgram();

    ofstream out("parse_output.txt");
    if (!hadError)
        out << "Parsing completed successfully.\n";
    else
        out << "Parsing finished with errors.\n";

    return 0;
}
