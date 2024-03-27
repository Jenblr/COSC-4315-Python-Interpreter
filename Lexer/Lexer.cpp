#include "Lexer.h"

// Constructor
Lexer::Lexer(const std::string& input_code) : code(input_code), position(0) {}

// Helper function to consume characters from the input
void Lexer::consume() {
    if (position < code.size()) {
        position++;
    }
}

// Helper function to peek at the next character in the input
char Lexer::peek() const {
    if (position < code.size()) {
        return code[position];
    }
    return '\0'; // Return null character if end of input is reached
}

// Helper function to check if the end of input has been reached
bool Lexer::isEndOfFile() const {
    return position >= code.size();
}

// Helper function to skip whitespace characters
void Lexer::skipWhitespace() {
    while (!isEndOfFile() && std::isspace(peek())) {
        consume();
    }
}

void Lexer::skipComment() {
    if (peek() == '#' && !isEndOfFile()) {
        while (peek() != '\n' && !isEndOfFile()) {
            consume();
        }
    }
}

// Helper function to recognize different operators
bool Lexer::is_operator_char(char c) {
    // Define the characters that represent different types of operators
    static const std::string arithmeticOperators = "+-*/%**";
    static const std::string comparisonOperators = "=!<>";
    static const std::string punctuation = "()[]{}:;,.";

    // Check if the character is part of an arithmetic operator
    if (arithmeticOperators.find(c) != std::string::npos) {
        return true;
    }

    // Check if the character is part of a comparison operator
    if (comparisonOperators.find(c) != std::string::npos) {
        return true;
    }

    // Check if the character is part of punctuation
    if (punctuation.find(c) != std::string::npos) {
        return true;
    }

    // Check for logical operators
    if (c == '&' || c == '|' || c == '!') {
        return true;
    }

    // Check for assignment operators
    if (c == '=') {
        return true;
    }

    return false;
}

// Helper function to recognize floating point numbers
bool Lexer::is_float_literal(const std::string& str) {
    char* end;

    // Check if string is a floating point number by attempting to convert to floating-point value
    std::strtod(str.c_str(), &end);
    return *end == '\0';
}

// Helper function to read an identifier or keyword
std::string Lexer::readIdentifierOrKeyword() {
    std::string result;
    while (!isEndOfFile() && (std::isalnum(peek()) || peek() == '_')) {
        result += peek();
        consume();
    }
    // Check if the identifier is a keyword
    if (keywords.find(result) != keywords.end()) {
        return result; // Return the keyword
    }
    return result;
}

// Helper function to read a number (integer or float)
std::string Lexer::readNumber() {
    std::string result;
    while (!isEndOfFile() && (std::isdigit(peek()) || peek() == '.')) {
        result += peek();
        consume();
    }
    return result; 
}

// Helper function to read a string literal
std::string Lexer::readStringLiteral() {
    std::string result;
    consume(); // Consume the opening quote
    while (!isEndOfFile() && peek() != '"') {
        result += peek();
        consume();
    }
    consume(); // Consume the closing quote
    return result;
}

// Helper function to read operators
std::string Lexer::readOperator() {
    std::string result;
    while (!isEndOfFile() && is_operator_char(peek())) {
        result += peek();
        consume();
    }
    return result;
}

// Token classification function
TokenType Lexer::classifyToken(const std::string& tokenValue) {
    if (keywords.find(tokenValue) != keywords.end()) {
        return TokenType::KEYWORD;
    } else if (is_operator_char(tokenValue[0])) {
        return TokenType::OPERATOR;
    } else if (is_float_literal(tokenValue)) {
        return TokenType::FLOAT_LITERAL;
    } else if (std::isdigit(tokenValue[0])) {
        return TokenType::INTEGER_LITERAL;
    } else if (tokenValue.front() == '"' && tokenValue.back() == '"') {
        return TokenType::STRING_LITERAL;
    } else {
        return TokenType::IDENTIFIER;
    }
}

// Main function to tokenize the input Python code
std::vector<std::string> Lexer::tokenize() {
    std::vector<std::string> tokens;
    while (!isEndOfFile()) {
        skipWhitespace();
        skipComment();

        if (isEndOfFile()) {
            break;
        }

        char currentChar = peek();

        if (std::isalpha(currentChar) || currentChar == '_') {
            std::string tokenValue = readIdentifierOrKeyword();
            TokenType tokenType = classifyToken(tokenValue); 
            tokens.push_back(tokenValue);
        } else if (std::isdigit(currentChar)) {
            std::string tokenValue = readNumber();
            TokenType tokenType = classifyToken(tokenValue); 
            tokens.push_back(tokenValue);
        } else if (currentChar == '"') {
            std::string tokenValue = readStringLiteral();
            TokenType tokenType = classifyToken(tokenValue); 
            tokens.push_back(tokenValue);
        } else {
            std::string tokenValue = readOperator();
            TokenType tokenType = classifyToken(tokenValue); 
            tokens.push_back(tokenValue);
        }
    }
    return tokens;
}
