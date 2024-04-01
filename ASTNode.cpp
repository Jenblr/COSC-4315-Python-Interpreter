#include "ASTNode.h"

// AdditionNode constructor
AdditionNode::AdditionNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
    : left(std::move(left)), right(std::move(right)) {
    // Check if left and right operands are valid
    if (!this->left || !this->right) {
        throw std::invalid_argument("Invalid left or right operand for AdditionNode.");
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

// Implementation for SubtractionNode
SubtractionNode::SubtractionNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
    : left(std::move(left)), right(std::move(right)) {
    // Check if left and right operands are valid
    if (!this->left || !this->right) {
        throw std::invalid_argument("Invalid left or right operand for SubtractionNode.");
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

// Implementation for MultiplicationNode
MultiplicationNode::MultiplicationNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
    : left(std::move(left)), right(std::move(right)) {
    // Check if left and right operands are valid
    if (!this->left || !this->right) {
        throw std::invalid_argument("Invalid left or right operand for MultiplicationNode.");
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

// Implementation for DivisionNode
DivisionNode::DivisionNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
    : left(std::move(left)), right(std::move(right)) {
    // Check if left and right operands are valid
    if (!this->left || !this->right) {
        throw std::invalid_argument("Invalid left or right operand for DivisionNode.");
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

// Implementation for AssignmentNode
AssignmentNode::AssignmentNode(std::unique_ptr<ASTNode> variable, std::unique_ptr<ASTNode> expression)
    : variable(std::move(variable)), expression(std::move(expression)) {
    // Check if variable and expression are valid
    if (!this->variable || !this->expression) {
        throw std::invalid_argument("Invalid variable or expression for AssignmentNode.");
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
    variable->print(indentation + 2);
    expression->print(indentation + 2);
}

// Implementation for LiteralNode
void LiteralNode::print(int indentation) const {
    std::cout << std::string(indentation, ' ') << "Literal Node: " << value << std::endl;
}
