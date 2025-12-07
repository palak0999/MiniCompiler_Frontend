#include <iostream>
#include <fstream>
#include <sstream>
#include "../1-lexer/lexer.cpp"
#include "../2-parser/parser.cpp"

int main() {
    std::ifstream file("test_input.txt");
    if (!file.is_open()) {
        std::cout << "Error: test_input.txt not found!" << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string input = buffer.str();

    Lexer lexer(input);
    Parser parser(lexer);

    try {
        parser.parse();
        std::cout << "Parsing Successful!" << std::endl;
    }
    catch (std::exception &e) {
        std::cout << "Syntax Error: " << e.what() << std::endl;
    }
}
