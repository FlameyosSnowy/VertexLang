#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#include "../tokens/tokens.hpp"

class Lexer {
public:
    explicit Lexer(const std::string_view &input) : input(input), start(0), current(0), line(1), pos(1) {
        this->tokens = new std::vector<Token>();
    }

    ~Lexer() {
        delete this->tokens;
    }

    std::vector<Token> *getTokens();

    void tokenize();

    void scanToken();

    void scanTokenType();

    void scanNumber();

    void validateNumber() const;

    bool isAtEnd() const;

    void consume();

    int getLine() const;

    int getPos() const;

    void addToken(TokenType type, std::string lexeme = "") {
        this->tokens->push_back(Token { type, lexeme, this->line, this->pos });
    }

    void debugTokens() const;

private:
    std::string_view input;
    u_int32_t start;
    u_int32_t current;
    u_int32_t line;
    u_int32_t pos;
    std::vector<Token> *tokens;
};