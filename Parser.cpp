/* PARSER.CPP = 
* Responsible for implentation of the functions declared in the Parser header
* Contains logic to parse expressions, statements, terms, and factors based on the Python grammer rules
* Constructs AST ndoes corresponding to Python's language constructs (e.g. arithmetic operation, variables, etc)
*/

#include "Parser.h"

Parser::Parser(Lexer& lexer) : lexer(lexer), tokens(lexer.tokenize()), currentToken(0) {}

std::unique_ptr<ASTNode> Parser::parse() {
    try {
        std::cout << "Starting parsing..." << std::endl;
        return parseAssignment(); 
    } catch (const std::exception& e) {
        // Print error message and rethrow the exception
        std::cerr << "Parsing error: " << e.what() << std::endl;
        throw;
    }
}

std::unique_ptr<ASTNode> Parser::parseExpression() {
    std::cout << "Parsing expression..." << std::endl;
    std::unique_ptr<ASTNode> left = parseTerm();

    while (currentToken < tokens.size()) {
        if (tokens[currentToken].type == TokenType::OPERATOR) {
            Token token = tokens[currentToken];
            std::cout << "Operator token found: " << token.value << std::endl;
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
    std::cout << "Parsing term..." << std::endl;
    std::unique_ptr<ASTNode> left = parseFactor();

    while (currentToken < tokens.size()) {
        if (tokens[currentToken].type == TokenType::OPERATOR &&
            (tokens[currentToken].value == "*" || tokens[currentToken].value == "/")) {
            Token token = tokens[currentToken];
            std::cout << "Operator token found: " << token.value << std::endl;
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
    std::cout << "Parsing factor..." << std::endl;

    // Continue parsing until there are no more tokens left
    while (currentToken < tokens.size()) {
        // Print current token information
        std::cout << "Current token: Type=" << static_cast<int>(tokens[currentToken].type)
                  << ", Value=" << tokens[currentToken].value << std::endl;

        // Check the type of the current token
        if (tokens[currentToken].type == TokenType::INTEGER_LITERAL) {
            // Parse integer literals
            auto value = std::stoi(tokens[currentToken].value); // Convert string to integer
            std::cout << "Integer literal found: " << value << std::endl;
            currentToken++; // Move to the next token
            return std::unique_ptr<IntegerNode>(new IntegerNode(value));
        } else if (tokens[currentToken].type == TokenType::VARIABLE_NAME) {
            // Parse variable names
            auto variableName = tokens[currentToken].value;
            std::cout << "Variable name found: " << variableName << std::endl;
            currentToken++; // Move to the next token
            return std::unique_ptr<VariableNode>(new VariableNode(variableName));
        } else if (tokens[currentToken].value == "(") {
            // If the token is a left parenthesis, parse a nested expression
            currentToken++; // Move past the left parenthesis
            std::cout << "Left parenthesis found." << std::endl;
            auto expression = parseExpression(); // Parse the nested expression
            // Check for matching right parenthesis
            if (currentToken < tokens.size() && tokens[currentToken].value == ")") {
                std::cout << "Right parenthesis found." << std::endl;
                currentToken++; // Move past the right parenthesis
                return expression;
            } else {
                // Error: Expected a right parenthesis
                std::cerr << "Error: Expected a right parenthesis." << std::endl;
                return nullptr;
            }
        } else {
            // Move to the next token
            currentToken++;
        }
    }

    // If no tokens are left, return the result of parsing a statement
    return parseAssignment();
}

std::unique_ptr<ASTNode> Parser::parseAssignment() {
    std::cout << "Parsing assignment..." << std::endl;

    // Check if the current token is a variable name
    if (tokens[currentToken].type != TokenType::VARIABLE_NAME) {
        std::cerr << "Error: Expected a variable name." << std::endl;
        return nullptr;
    }

    // Extract the variable name
    std::string variableName = tokens[currentToken].value;
    currentToken++; // Move to the next token

    // Check if the next token is '='
    if (tokens[currentToken].type != TokenType::OPERATOR || tokens[currentToken].value != "=") {
        std::cerr << "Error: Expected '=' after variable name." << std::endl;
        return nullptr;
    }
    currentToken++; // Move to the next token

    // Parse the expression on the right-hand side of the assignment
    std::unique_ptr<ASTNode> expression = parseExpression();
    if (!expression) {
        std::cerr << "Error: Failed to parse the expression on the right-hand side of the assignment." << std::endl;
        return nullptr;
    }

    // Check if the expression is an integer literal
    IntegerNode* integerNode = dynamic_cast<IntegerNode*>(expression.get());
    if (!integerNode) {
        std::cerr << "Error: Expected an integer literal on the right-hand side of the assignment." << std::endl;
        return nullptr;
    }

    // Assign the value of the integer literal to the variable name
    int value = integerNode->getValue();
    // Create assignment node
    return std::unique_ptr<AssignmentNode>(new AssignmentNode(
        std::unique_ptr<VariableNode>(new VariableNode(variableName)),
        std::unique_ptr<IntegerNode>(new IntegerNode(value))
    ));
}

std::unique_ptr<StatementNode> Parser::parseStatement() {
    std::cout << "Parsing statement..." << std::endl;

    // Continue parsing until there are no more tokens left
    while (currentToken < tokens.size()) {
        // Check if it's an assignment statement
        if (tokens[currentToken].type == TokenType::VARIABLE_NAME) {
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
            // Move to the next token if none of the conditions match
            currentToken++;
        }
    }

    // If no tokens are left, return nullptr
    return nullptr;
}