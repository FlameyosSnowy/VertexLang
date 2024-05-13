#include <iostream>
#include <vector>
#include <string>

#include "./lexer/lexer.cpp"

int main(int argc, char* argv[]) {
    while (true) {
        std::string input;

        std::cout << "Give me an input! multiple lines supported." << std::endl;
        std::getline(std::cin, input);

        if (input == "exit" || input == "quit") return 0;

        Lexer lexer = Lexer { input };
        lexer.tokenize();
        lexer.debugTokens();
    }
    return 0;
}