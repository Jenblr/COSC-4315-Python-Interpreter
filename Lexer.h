#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <cctype>
#include <unordered_set>
#include <stack>

// Enum to represent different token types
enum class TokenType {
    IDENTIFIER, // 0
    FUNCTION_NAME, // 1
    VARIABLE_NAME, // 2
    KEYWORD, // 3
    OPERATOR, // 4
    INTEGER_LITERAL, // 5
    STRING_LITERAL, // 6
    END_OF_FILE, // 7
    INDENT, // 8
    DEDENT, // 9
    NEWLINE, //10
};

// Structure to represent a token
struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    Lexer(const std::string& input_code);
    std::vector<Token> tokenize(); // Tokenize the input Python code

private:
    const std::string code;
    size_t position;
    size_t currentLineNumber;
    std::stack<size_t> indentation_stack; // Maintain a stack to track indentation levels
    
    /* HELPER FUNCTIONS: Below are different types of helper functions to 
    read and account for within a Python code.*/
    void readNext(); 
    char peek() const;
    bool isEndOfFile() const;
    void skipWhitespace();
    void skipComment();
    bool is_operator_char(char c);
    bool is_function_name(const std::string& result);
    bool is_variable_name(const std::string& result);
    std::string readIdentifierOrKeyword();
    std::string readNumber();
    std::string readStringLiteral();
    std::string readOperator();

    // Define keywords as a set for efficient lookup
    const std::unordered_set<std::string> keywords = {
        "if", "else", "while", "for", "def", "return", "True", "False", "print"
    };

    // Token classification functions
    TokenType classifyToken(const std::string& tokenValue);
};

#endif // LEXER_H