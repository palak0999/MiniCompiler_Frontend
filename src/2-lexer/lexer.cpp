#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
using namespace std;

struct Token {
    string type;
    string value;
};

bool isKeyword(string s) {
    return (s == "int" || s == "print" || s == "if" || s == "while" || s == "text");
}

int main() {
    ifstream file("input.txt");
    ofstream out("tokens_output.txt");

    if (!file.is_open()) {
        cout << "Error: input.txt not found\n";
        return 1;
    }

    char ch;
    string buffer;

    while (file.get(ch)) {

        // Skip whitespace
        if (isspace(ch))
            continue;

        // Identifiers or Keywords
        if (isalpha(ch)) {
            buffer = ch;
            while (file.get(ch) && isalnum(ch)) {
                buffer += ch;
            }
            file.unget();

            if (isKeyword(buffer))
                out << "KEYWORD(" << buffer << ")\n";
            else
                out << "ID(" << buffer << ")\n";
        }

        // Numbers
        else if (isdigit(ch)) {
            buffer = ch;
            while (file.get(ch) && isdigit(ch)) {
                buffer += ch;
            }
            file.unget();
            out << "NUM(" << buffer << ")\n";
        }

        // Operators
        else if (ch == '=') {
            if (file.get(ch) && ch == '=')
                out << "OP(EQ)\n";
            else {
                file.unget();
                out << "OP(ASSIGN)\n";
            }
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
            out << "OP(" << ch << ")\n";

        // Symbols
        else if (ch == ';' || ch == '(' || ch == ')' || ch == '{' || ch == '}')
            out << "SYM(" << ch << ")\n";

        else {
            out << "UNKNOWN(" << ch << ")\n";
        }
    }

    return 0;
}
