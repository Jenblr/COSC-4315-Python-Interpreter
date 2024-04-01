#include "ASTNode.h"

// AdditionNode constructor
AdditionNode::AdditionNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
    : left(std::move(left)), right(std::move(right)) {
    // Check if left operand is valid
    if (!this->left) {
        throw std::invalid_argument("Invalid left operand for AdditionNode.");
    }

    // Check if right operand is valid
    if (!this->right) {
        throw std::invalid_argument("Invalid right operand for AdditionNode.");
    }
}

// Getter function for left operand
const ASTNode* AdditionNode::getLeftOperand() const {
    return left.get();
}

// Getter function for right operand
const ASTNode* AdditionNode::getRightOperand() const {
    return right.get();
}

// Print function
void AdditionNode::print(int indentation) const {
    std::cout << std::string(indentation, ' ') << "Addition Node" << std::endl;
    left->print(indentation + 2);
    right->print(indentation + 2);
}

// SubtractionNode constructor
SubtractionNode::SubtractionNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
    : left(std::move(left)), right(std::move(right)) {
    // Check if left operand is valid
    if (!this->left) {
        throw std::invalid_argument("Invalid left operand for SubtractionNode.");
    }

    // Check if right operand is valid
    if (!this->right) {
        throw std::invalid_argument("Invalid right operand for SubtractionNode.");
    }
}

const ASTNode* SubtractionNode::getLeftOperand() const {
    return left.get();
}

const ASTNode* SubtractionNode::getRightOperand() const {
    return right.get();
}

void SubtractionNode::print(int indentation) const {
    std::cout << std::string(indentation, ' ') << "Subtraction Node" << std::endl;
    left->print(indentation + 2);
    right->print(indentation + 2);
}

// MultiplicationNode constructor
MultiplicationNode::MultiplicationNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
    : left(std::move(left)), right(std::move(right)) {
    // Check if left operand is valid
    if (!this->left) {
        throw std::invalid_argument("Invalid left operand for MultiplicationNode.");
    }

    // Check if right operand is valid
    if (!this->right) {
        throw std::invalid_argument("Invalid right operand for MultiplicationNode.");
    }
}

const ASTNode* MultiplicationNode::getLeftOperand() const {
    return left.get();
}

const ASTNode* MultiplicationNode::getRightOperand() const {
    return right.get();
}

void MultiplicationNode::print(int indentation) const {
    std::cout << std::string(indentation, ' ') << "Multiplication Node" << std::endl;
    left->print(indentation + 2);
    right->print(indentation + 2);
}

// DivisionNode constructor
DivisionNode::DivisionNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
    : left(std::move(left)), right(std::move(right)) {
    // Check if left operand is valid
    if (!this->left) {
        throw std::invalid_argument("Invalid left operand for DivisionNode.");
    }

    // Check if right operand is valid
    if (!this->right) {
        throw std::invalid_argument("Invalid right operand for DivisionNode.");
    }
}

const ASTNode* DivisionNode::getLeftOperand() const {
    return left.get();
}

const ASTNode* DivisionNode::getRightOperand() const {
    return right.get();
}

void DivisionNode::print(int indentation) const {
    std::cout << std::string(indentation, ' ') << "Division Node" << std::endl;
    left->print(indentation + 2);
    right->print(indentation + 2);
}

// Implementation for IntegerNode
IntegerNode::IntegerNode(int value) : value(value) {}

int IntegerNode::getValue() const {
    return value;
}

void IntegerNode::print(int indentation) const {
    std::cout << std::string(indentation, ' ') << "Integer Node: " << value << std::endl;
}

// Implementation for VariableNode
VariableNode::VariableNode(const std::string& name) : name(name) {}

std::string VariableNode::getName() const {
    return name;
}

void VariableNode::print(int indentation) const {
    std::cout << std::string(indentation, ' ') << "Variable Node: " << name << std::endl;
}

AssignmentNode::AssignmentNode(std::unique_ptr<ASTNode> variable, std::unique_ptr<ASTNode> expression)
    : variable(std::move(variable)), expression(std::move(expression)) {
    // Check if variable and expression are valid
    if (!this->variable) {
        throw std::invalid_argument("Invalid variable for AssignmentNode.");
    }
    if (!this->expression) {
        throw std::invalid_argument("Invalid expression for AssignmentNode.");
    }
}

const ASTNode* AssignmentNode::getVariable() const {
    return variable.get();
}

const ASTNode* AssignmentNode::getExpression() const {
    return expression.get();
}

void AssignmentNode::print(int indentation) const {
    std::cout << std::string(indentation, ' ') << "Assignment Node" << std::endl;
    std::cout << std::string(indentation + 2, ' ') << "Variable: ";
    variable->print(); // Print the variable node
    std::cout << std::string(indentation + 2, ' ') << "Expression: ";
    if (dynamic_cast<IntegerNode*>(expression.get())) {
        dynamic_cast<IntegerNode*>(expression.get())->print(); // Print the integer node
    } else {
        std::cerr << "Error: Expected an integer expression in AssignmentNode." << std::endl;
    }
}


// Implementation for LiteralNode
void LiteralNode::print(int indentation) const {
    std::cout << std::string(indentation, ' ') << "Literal Node: " << value << std::endl;
}
