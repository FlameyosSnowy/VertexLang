#include "lexer.hpp"

std::vector<Token> *Lexer::getTokens() {
    return this->tokens;
}

void Lexer::tokenize() {
    while (!isAtEnd()) scanToken();
}

void Lexer::scanToken() {
    this->start = this->current;
    this->scanTokenType();
}

void Lexer::scanTokenType() {
    if (this->isAtEnd()) {
        this->addToken(TokenType::END);
    } else if (std::isspace(this->input[this->current])) {
        this->consume();
        this->scanToken();
    } else if (std::isalpha(this->input[this->current])) {
        this->addToken(TokenType::LETTER, std::string{ this->input[this->current] });
        this->consume();
    } else if (std::isdigit(this->input[this->current])) {
        this->scanNumber();
    } else if (this->input[this->current] == '+') {
        this->addToken(TokenType::PLUS);
        this->consume();
    } else if (this->input[this->current] == '-') {
        this->addToken(TokenType::MINUS);
        this->consume();
    } else if (this->input[this->current] == '*') {
        this->addToken(TokenType::MUL);
        this->consume();
    } else if (this->input[this->current] == '/') {
        this->addToken(TokenType::DIV);
        this->consume();
    } else if (this->input[this->current] == '(') {
        this->addToken(TokenType::LPAREN);
        this->consume();
    } else if (this->input[this->current] == ')') {
        this->addToken(TokenType::RPAREN);
        this->consume();
    } else {
        std::cerr << "Error: Unexpected character at line " << this->line << ", position " << this->pos << std::endl;
        std::cerr << "Unknown character that was inputted: " << this->input[this->current] << std::endl;
        this->consume();
    }
}

void Lexer::scanNumber() {
    TokenType type = TokenType::INTEGER;

    bool foundDot = false;
    while (std::isdigit(this->input[this->current]) || 
                this->input[this->current] == '.' || 
                char(std::tolower(this->input[this->current])) == 'f'|| 
                char(std::tolower(this->input[this->current])) == 'l') {
        this->consume();
        if (char(std::tolower(this->input[this->current])) == 'f') {
            type = TokenType::FLOAT;
            validateNumber();
            break;
        } else if (char(std::tolower(this->input[this->current])) == 'l') {
            type = TokenType::LONG;
            validateNumber();

            if (foundDot) { // this is a guaranteed 64bit integer type? and also a decimal?
                std::cerr << "Found Mistake" << std::endl;
            }
            break;
        } else if (this->input[this->current] == '.') {
            type = TokenType::DOUBLE;
            validateNumber();
            foundDot = true;
        }
    }

    this->addToken(type, std::string(this->input.begin() + this->start, this->input.begin() + this->current));
}

void Lexer::validateNumber() const {
    char currentChar = this->input[this->current + 1];
    char lowercase = char(std::tolower(currentChar));
    if (this->input[this->current] == '.' && 
                (&currentChar == nullptr || 
                    currentChar == ';' ||
                    lowercase == 'f' ||
                    lowercase == 'l')) {
        std::cerr << "Found mistake" << std::endl;
    }
}

bool Lexer::isAtEnd() const {
    return this->current >= this->input.size();
}

void Lexer::consume() {
    this->current++;
    this->pos++;

    if (this->input[this->current - 1] == '\n') {
        this->line++;
        this->pos = 1;
    }
}

int Lexer::getLine() const {
    return this->line;
}

int Lexer::getPos() const {
    return this->pos;
}

void Lexer::debugTokens() const {
    for (const Token &token : *tokens) {
        token.printType();
    }
}