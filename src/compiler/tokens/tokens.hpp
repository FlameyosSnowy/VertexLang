#include <string>
#include <variant>
#include <map>

enum class TokenType {
    INTEGER,
    FLOAT,
    LONG,
    DOUBLE,
    LETTER,
    
    IDENTIFIER,
    STRING_LITERAL,

    PLUS,
    MINUS,
    MUL,
    DIV,
    LPAREN,
    RPAREN,
    END
};

static const std::map<TokenType, std::string_view> tokenTypeStrings{
    { TokenType::INTEGER, "integer" },
    { TokenType::LONG, "long" },
    { TokenType::FLOAT, "float" },
    { TokenType::DOUBLE, "double" },

    { TokenType::PLUS, "plus" },
    { TokenType::MINUS, "minus" },
    { TokenType::MUL, "mul" },
    { TokenType::DIV, "div" },

    { TokenType::LPAREN, "lparen" },
    { TokenType::RPAREN, "rparen" },

    { TokenType::LETTER, "letter" },
    { TokenType::END, "end" }
};

class Token {
public:
    TokenType type;
    std::string lexeme;
    
    u_int32_t line;
    u_int32_t pos;

    void printType() const {
        std::cout << lexeme << " (" << tokenTypeStrings.at(type) << ") ";
        std::cout << "at line " << line << ", position " << pos << std::endl;
    }
};

enum class ValueType {
    
};