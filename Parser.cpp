/* PARSER.CPP = 
* Responsible for implentation of the functions declared in the Parser header
* Contains logic to parse expressions, statements, terms, and factors based on the Python grammer rules
* Constructs AST ndoes corresponding to Python's language constructs (e.g. arithmetic operation, variables, etc)
*/

#include "Parser.h"

Parser::Parser(Lexer& lexer) : lexer(lexer), tokens(lexer.tokenize()), currentToken(0) {}

std::unique_ptr<ASTNode> Parser::parse() {
    try {
        return parseExpression();
    } catch (const std::exception& e) {
        // Print error message and rethrow the exception
        std::cerr << "Parsing error: " << e.what() << std::endl;
        throw;
    }
}

void Parser::throwError(const std::string& message) {
    throw std::runtime_error(message);
}

std::unique_ptr<ASTNode> Parser::parseExpression() {
    std::unique_ptr<ASTNode> left = parseTerm();

    while (currentToken < tokens.size()) {
        if (tokens[currentToken].type == TokenType::OPERATOR) {
            Token token = tokens[currentToken];
            currentToken++; // Increment token index

            // Bounds checking
            if (currentToken >= tokens.size()) {
                // Error: Unexpected end of input after operator
                std::cerr << "Parsing error: Unexpected end of input after operator." << std::endl;
                return nullptr;
            }

            std::unique_ptr<ASTNode> right = parseTerm();
            if (!right) {
                // Propagate parsing error from parseTerm()
                return nullptr;
            }

            // Create parent node based on operator precedence and associativity
            if (token.value == "+" || token.value == "-") {
                left = std::unique_ptr<AdditionNode>(new AdditionNode(std::move(left), std::move(right)));
            } else {
                // Error: Unexpected operator
                std::cerr << "Parsing error: Unexpected operator '" << token.value << "'." << std::endl;
                return nullptr;
            }
        } else {
            break;
        }
    }

    return left;
}


std::unique_ptr<ASTNode> Parser::parseTerm() {
    std::unique_ptr<ASTNode> left = parseFactor();

    while (currentToken < tokens.size()) {
        if (tokens[currentToken].type == TokenType::OPERATOR &&
            (tokens[currentToken].value == "*" || tokens[currentToken].value == "/")) {
            Token token = tokens[currentToken];
            currentToken++; // Increment token index

            // Bounds checking
            if (currentToken >= tokens.size()) {
                // Error: Unexpected end of input after operator
                return nullptr;
            }

            std::unique_ptr<ASTNode> right = parseFactor();
            if (!right) {
                // Error: Failed to parse right factor
                return nullptr;
            }

            // Create parent node based on operator precedence and associativity
            if (token.value == "*") {
                left = std::unique_ptr<MultiplicationNode>(new MultiplicationNode(std::move(left), std::move(right)));
            } else if (token.value == "/") {
                left = std::unique_ptr<DivisionNode>(new DivisionNode(std::move(left), std::move(right)));
            }
        } else {
            break;
        }
    }

    return left;
}


std::unique_ptr<ASTNode> Parser::parseFactor() {
    // If there are no more tokens, return nullptr
    if (currentToken >= tokens.size()) {
        return nullptr;
    }

    // Check the type of the current token
    if (tokens[currentToken].type == TokenType::INTEGER_LITERAL) {
        // Parse integer literals
        auto value = std::stoi(tokens[currentToken].value); // Convert string to integer
        currentToken++; // Move to the next token
        return std::unique_ptr<IntegerNode>(new IntegerNode(value));
    } else if (tokens[currentToken].type == TokenType::VARIABLE_NAME) {
        // Parse variable names
        auto variableName = tokens[currentToken].value;
        currentToken++; // Move to the next token
        return std::unique_ptr<VariableNode>(new VariableNode(variableName));
    } else if (tokens[currentToken].value == "(") {
        // If the token is a left parenthesis, parse a nested expression
        currentToken++; // Move past the left parenthesis
        auto expression = parseExpression(); // Parse the nested expression
        // Check for matching right parenthesis
        if (currentToken < tokens.size() && tokens[currentToken].value == ")") {
            currentToken++; // Move past the right parenthesis
            return expression;
        } else {
            // Error: Expected a right parenthesis
            return nullptr;
        }
    } else {
        // Error: Unexpected token
        return nullptr;
    }
}

std::unique_ptr<StatementNode> Parser::parseStatement() {
    // Check if it's an assignment statement
    if (currentToken < tokens.size() && tokens[currentToken].type == TokenType::VARIABLE_NAME) {
        std::string variableName = tokens[currentToken].value;
        currentToken++; // Move to next token
        // Ensure next token is '='
        if (currentToken < tokens.size() && tokens[currentToken].type == TokenType::OPERATOR && tokens[currentToken].value == "=") {
            currentToken++; // Move to next token
            // Parse expression on right-hand side of assignment
            std::unique_ptr<ASTNode> expression = parseExpression();
            if (expression) {
                // Create assignment node
                return std::unique_ptr<AssignmentNode>(new AssignmentNode(
                    std::unique_ptr<VariableNode>(new VariableNode(variableName)),
                    std::move(expression)
                ));
            } else {
                // Error: Invalid expression
                std::cerr << "Error: Failed to parse the expression on the right-hand side of the assignment." << std::endl;
                return nullptr;
            }
        } else {
            // Error: Expected '=' after variable name
            std::cerr << "Error: Expected '=' after variable name." << std::endl;
            return nullptr;
        }
    } else {
        // Error: Expected statement
        std::cerr << "Error: Expected a variable name." << std::endl;
        return nullptr;
    }
}



std::unique_ptr<ASTNode> Parser::parseAssignment() {
    // Parse variable name
    if (currentToken < tokens.size() && tokens[currentToken].type == TokenType::VARIABLE_NAME) {
        std::string variableName = tokens[currentToken].value;
        currentToken++; // Move to next token
        // Ensure next token is '='
        if (currentToken < tokens.size() && tokens[currentToken].type == TokenType::OPERATOR && tokens[currentToken].value == "=") {
            currentToken++; // Move to next token
            // Parse expression on right-hand side of assignment
            std::unique_ptr<ASTNode> expression = parseExpression();
            if (expression) {
                // Create assignment node
                return std::unique_ptr<AssignmentNode>(new AssignmentNode(std::unique_ptr<VariableNode>(new VariableNode(variableName)), std::move(expression)));
            } else {
                // Error: Invalid expression
                return nullptr;
            }
        } else {
            // Error: Expected '=' after variable name
            return nullptr;
        }
    } else {
        // Error: Expected variable name
        return nullptr;
    }
}