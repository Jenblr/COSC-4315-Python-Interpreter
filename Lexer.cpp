#include "Lexer.h"

// Constructor to call Lexer class in header
Lexer::Lexer(const std::string& input_code) : code(input_code), position(0), currentLineNumber(1) {}

// Helper function to read characters from the input
void Lexer::readNext() {
    if (position < code.size()) {
        if (code[position] == '\n') {
            currentLineNumber++; 
        }
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
        readNext();
    }
}

// Helper function to skip comments
void Lexer::skipComment() {
    char currentChar = peek();

    // Check if the current character indicates the start of a comment
    if (currentChar == '#') {
        // Skip until the end of the line or end of file
        while (!isEndOfFile() && peek() != '\n') {
            readNext();
        }
    }
}

// Helper function to recognize different operators
bool Lexer::is_operator_char(char c) {
    // Define the characters that represent different types of operators
    static const std::string arithmeticOperators = "+-*/%**";
    static const std::string comparisonOperators = "=!<>";
    static const std::string punctuation = "()[]{}:;,.";
    static const std::vector<std::string> logicalOperators = {"and", "or", "not"}; // Note: Define in phase 2

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

    // Check for assignment operator
    if (c == '=') {
        return true;
    }


    return false;
}

// Helper function to identify a function name
bool Lexer::is_function_name(const std::string& result) {
    // Check if the result starts with 'def', indicating a function definition
    if (result.substr(0, 3) != "def") {
        return false;
    }

    // Check if the rest of the string contains valid characters for a function name
    std::string functionName = result.substr(3); // Skip 'def'
    for (char c : functionName) {
        if (!std::isalnum(c) && c != '_') {
            return false;
        }
    }

    // Check if the result is not a keyword
    if (keywords.find(result) != keywords.end()) {
        return false;
    }

    return true;
}

bool Lexer::is_variable_name(const std::string& result) {
    // Variable names cannot start with a digit
    if (std::isdigit(result[0]))
        return false;

    // Check if each character is alphanumeric or underscore
    for (char c : result) {
        if (!std::isalnum(c) && c != '_')
            return false;
    }
    
    // Check if the name is not a keyword
    if (keywords.find(result) != keywords.end())
        return false;

    return true;
}

// Helper function to read an identifier or keyword
std::string Lexer::readIdentifierOrKeyword() {
    std::string result;
    while (!isEndOfFile() && (std::isalnum(peek()) || peek() == '_')) {
        result += peek();
        readNext();
    }
    // Check if the identifier is a keyword
    if (keywords.find(result) != keywords.end()) {
        return result; // Return the keyword
    }
    
    return result;
}

// Helper function to read a number (integer only)
std::string Lexer::readNumber() {
    std::string result;
    while (!isEndOfFile() && std::isdigit(peek())) {
        result += peek();
        readNext();
    }
    return result; 
}

// Helper function to read a string literal
std::string Lexer::readStringLiteral() {
    std::string result;
    readNext(); // Read the opening quote
    result += '"';
    while (!isEndOfFile() && peek() != '"') {
        result += peek();
        readNext();
    }
    if (!isEndOfFile()) {
        result += peek();
        readNext(); // Read the closing quote
    }
    return result;
}

// Helper function to read operators
std::string Lexer::readOperator() {
    std::string result;
    while (!isEndOfFile() && is_operator_char(peek())) {
        result += peek();
        readNext();
    }
    return result;
}

TokenType Lexer::classifyToken(const std::string& tokenValue) {
    if (keywords.find(tokenValue) != keywords.end()) {
        return TokenType::KEYWORD;
    } else if(is_function_name(tokenValue)) {
        return TokenType::FUNCTION_NAME;
    } else if(is_variable_name(tokenValue)) {
        return TokenType::VARIABLE_NAME;
    } else if (is_operator_char(tokenValue[0])) {
        return TokenType::OPERATOR;
    } else if (std::isdigit(tokenValue[0])) {
        return TokenType::INTEGER_LITERAL;
    } else if (tokenValue.front() == '"' && tokenValue.back() == '"') {
        return TokenType::STRING_LITERAL;
    } else {
        return TokenType::IDENTIFIER;
    }
}

// Main function to tokenize the input Python code
std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    std::string previousToken;
    size_t previousIndentationLevel = 0;

    // Perform tokenization until file is completely consumed
    while (!isEndOfFile()) {
        skipComment();

        char currentChar = peek(); // Get current character
        size_t indentationLevel = 0;

        if (std::isspace(currentChar)) {
            if (currentChar == '\n') {
                // Skip empty lines
                while (peek() == '\n') {
                    readNext();
                    currentLineNumber++;
                }

                // Count indentation spaces
                while (peek() == ' ') {
                    readNext();
                    indentationLevel++;
                }

                if (indentationLevel > previousIndentationLevel) {
                    tokens.push_back({TokenType::INDENT, ""});
                    indentation_stack.push(indentationLevel);
                } else if (indentationLevel < previousIndentationLevel) {
                    while (!indentation_stack.empty() && indentation_stack.top() > indentationLevel) {
                        tokens.push_back({TokenType::DEDENT, ""});
                        indentation_stack.pop();
                    }
                }
                previousIndentationLevel = indentationLevel;
            } else { // Space in-between code is not an indentation
                skipWhitespace();
            }
        } else if (std::isalpha(currentChar) || currentChar == '_') {
            std::string tokenValue = readIdentifierOrKeyword();
            TokenType tokenType = classifyToken(tokenValue);
            tokens.push_back({tokenType, tokenValue}); 
        } else if (std::isdigit(currentChar)) {
            std::string tokenValue = readNumber();
            TokenType tokenType = classifyToken(tokenValue);
            tokens.push_back({tokenType, tokenValue}); 
        } else if (currentChar == '"') {
            std::string tokenValue = readStringLiteral();
            TokenType tokenType = classifyToken(tokenValue);
            tokens.push_back({tokenType, tokenValue}); 
        } else if (currentChar == '\n') {
            // Skip consecutive newlines
            readNext();
        } else {
            std::string tokenValue = readOperator();
            TokenType tokenType = classifyToken(tokenValue);
            tokens.push_back({tokenType, tokenValue}); 
        }

    }

    // Add DEDENT tokens for remaining indentation levels
    while (!indentation_stack.empty()) {
        tokens.push_back({TokenType::DEDENT, ""});
        indentation_stack.pop();
    }

    if (isEndOfFile()) {
        tokens.push_back({TokenType::END_OF_FILE, ""});
    }

    return tokens;
}