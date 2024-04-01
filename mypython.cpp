#include <iostream>
#include <fstream>
#include <sstream>
#include "Lexer.h"
#include "Parser.h"
#include "ASTNode.h"

int main(int argc, char* argv[]) {
    // Parse command line arguments
    if (argc != 2) { 
        std::cerr << "Usage: " << argv[0] << " <file.py>" << std::endl;
        return 1;
    }

    // Open the input file
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << argv[1] << std::endl;
        return 1;
    }

    // Read the contents of the file
    std::ostringstream oss;
    oss << file.rdbuf();
    std::string fileContents = oss.str();

    // Tokenize Python code using Lexer
    Lexer lexer(fileContents);
    std::vector<Token> tokens = lexer.tokenize();

    // Output tokens for testing
    std::cout << "Tokens:" << std::endl;
    for (const auto& token : tokens) {
        std::cout << "Type: " << static_cast<int>(token.type) << ", Value: " << token.value << std::endl;
    }

    // Parse tokens to build the AST
    Parser parser(lexer);
    try {
        std::unique_ptr<ASTNode> ast = parser.parse();

        // Print the AST
        if (ast) {
            std::cout << "Abstract Syntax Tree:" << std::endl;
            ast->print();
        } else {
            std::cerr << "Error: Unable to parse input." << std::endl;
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}


// TO run in terminal: 
// g++ -std=c++11 *.cpp -o mypython
// ./mypython <file name.py>