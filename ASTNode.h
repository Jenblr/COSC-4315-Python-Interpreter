#ifndef ASTNODE_H
#define ASTNODE_H

#include <memory>
#include <string>
#include <iostream>
#include <stdexcept> // Include for exception handling

// Forward declarations of other AST node classes
class ExpressionNode;
class StatementNode;

// Base class for all AST nodes
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void print(int indentation = 0) const = 0; // To print AST
};

// Class for ExpressionNode (Base class for all expression nodes)
class ExpressionNode : public ASTNode {
public:
    virtual ~ExpressionNode() = default;
};

// Class for Statement node
class StatementNode : public ASTNode {
public:
    virtual ~StatementNode() = default;
};

// Class for Addition node
class AdditionNode : public ASTNode {
public:
    AdditionNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right);

    const ASTNode* getLeftOperand() const;
    const ASTNode* getRightOperand() const;

    void print(int indentation = 0) const override;

private:
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
};

// Class for Subtraction node
class SubtractionNode : public ASTNode {
public:
    SubtractionNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right);

    const ASTNode* getLeftOperand() const;
    const ASTNode* getRightOperand() const;

    void print(int indentation = 0) const override;

private:
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
};

// Class for Multiplication node
class MultiplicationNode : public ASTNode {
public:
    MultiplicationNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right);

    const ASTNode* getLeftOperand() const;
    const ASTNode* getRightOperand() const;

    void print(int indentation = 0) const override;

private:
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
};

// Class for Division node
class DivisionNode : public ASTNode {
public:
    DivisionNode(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right);

    const ASTNode* getLeftOperand() const;
    const ASTNode* getRightOperand() const;

    void print(int indentation = 0) const override;

private:
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
};


// Class for Integer node
class IntegerNode : public ASTNode {
public:
    explicit IntegerNode(int value);

    int getValue() const;

    void print(int indentation = 0) const override;
private:
    int value;
};

// Class for Variable node
class VariableNode : public ASTNode {
public:
    explicit VariableNode(const std::string& name);

    std::string getName() const;

    void print(int indentation = 0) const override;
private:
    std::string name;
};

// Class for Assignment node
class AssignmentNode : public StatementNode {
public:
    AssignmentNode(std::unique_ptr<ASTNode> variable, std::unique_ptr<ASTNode> expression);

    const ASTNode* getVariable() const;

    const ASTNode* getExpression() const;

    void print(int indentation = 0) const override;
private:
    std::unique_ptr<ASTNode> variable;
    std::unique_ptr<ASTNode> expression;
};


// Class for Literal node
class LiteralNode : public ExpressionNode {
public:
    LiteralNode(const std::string& value) : value(value) {}

    std::string getValue() const;

    void print(int indentation = 0) const override;
private:
    std::string value;
};

#endif // ASTNODE_H
