#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <cctype>
#include <unordered_set>

// Enum to represent different token types
enum class TokenType {
    IDENTIFIER,
    KEYWORD,
    OPERATOR,
    INTEGER_LITERAL,
    FLOAT_LITERAL,
    STRING_LITERAL
};

// Structure to represent a token
struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    Lexer(const std::string& input_code);
    std::vector<std::string> tokenize(); // Tokenize the input Python code

private:
    const std::string code;
    size_t position;

    /* HELPER FUNCTIONS: Below are different types of helper functions to 
    read and account for within a Python code.*/
    void consume(); 
    char peek() const;
    bool isEndOfFile() const;
    void skipWhitespace();
    void skipComment();
    bool is_operator_char(char c);
    bool is_float_literal(const std::string& str);
    std::string readIdentifierOrKeyword();
    std::string readNumber();
    std::string readStringLiteral();
    std::string readOperator();


    // Define keywords as a set for efficient lookup
    const std::unordered_set<std::string> keywords = {
        "if", "else", "while", "for", "def", "return", "True", "False"
    };

    // Token classification function
    TokenType classifyToken(const std::string& tokenValue);
};

#endif // LEXER_H