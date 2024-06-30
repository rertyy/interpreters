#include <iostream>
#include <utility>
#include "../include/lox/Interpreter.h"
#include "../include/utils/utils.h"
#include "../include/lox/RuntimeError.h"
#include "../include/lox/Lox.h"

using
enum TokenType;

std::any Interpreter::visitLiteralExpr(Literal &expr) {
    return expr.value;
}

std::any Interpreter::visitGroupingExpr(Grouping &expr) {
    return evaluate(*expr.expression);
}

std::any Interpreter::evaluate(Expr &expr) {
    return expr.accept(*this);
}

std::any Interpreter::visitUnaryExpr(Unary &expr) {
    std::any right = evaluate(*expr.right);

    switch (expr.op.type) {
        case MINUS:
            return -std::any_cast<double>(right);
        case BANG:
            return !isTruthy(right);
        default:
            return nullptr;
    }
}

std::any Interpreter::visitVariableExpr(Variable &expr) {
    return environment->get(expr.name);
}

bool Interpreter::isTruthy(const std::any &object) const {
    if (object.type() == typeid(bool)) {
        return std::any_cast<bool>(object);
    }
    return object.type() != typeid(std::nullptr_t);
}

std::any Interpreter::visitBinaryExpr(Binary &expr) {
    std::any left = evaluate(*expr.left);
    std::any right = evaluate(*expr.right);

    switch (expr.op.type) {
        case TokenType::COMMA:
            return right;
        case TokenType::GREATER:
            checkNumberOperands(expr.op, left, right);
            return std::any_cast<double>(left) > std::any_cast<double>(right);
        case TokenType::GREATER_EQUAL:
            checkNumberOperands(expr.op, left, right);
            return std::any_cast<double>(left) >= std::any_cast<double>(right);
        case TokenType::LESS:
            checkNumberOperands(expr.op, left, right);
            return std::any_cast<double>(left) < std::any_cast<double>(right);
        case TokenType::LESS_EQUAL:
            checkNumberOperands(expr.op, left, right);
            return std::any_cast<double>(left) <= std::any_cast<double>(right);
        case TokenType::BANG_EQUAL:
            return !isEqual(left, right);
        case TokenType::EQUAL_EQUAL:
            return isEqual(left, right);
        case TokenType::MINUS:
            return std::any_cast<double>(left) - std::any_cast<double>(right);
        case TokenType::PLUS:
            if (isNumber(left) && isNumber(right)) {
                return std::any_cast<double>(left) + std::any_cast<double>(right);
            } else if (isString(left) || isString(right)) {
                return castAnyToString(left) + castAnyToString(right);
            }
            throw RuntimeError(expr.op, "Operands must be two numbers or at least one string");
        case TokenType::SLASH: {
            checkNumberOperands(expr.op, left, right);
            const auto leftOperand = std::any_cast<double>(left);
            const auto rightOperand = std::any_cast<double>(right);
            if (rightOperand == 0) {
                throw RuntimeError(expr.op, "Division by zero");
            }
            return leftOperand / rightOperand;
        }
        case TokenType::STAR:
            checkNumberOperands(expr.op, left, right);
            return std::any_cast<double>(left) * std::any_cast<double>(right);
        default:
            return nullptr;
    }
}


std::any Interpreter::visitTernaryExpr(Ternary &expr) {
    if (expr.op1.type == QUESTION && expr.op2.type == COLON) {
        std::any condition = evaluate(*expr.left);
        if (isTruthy(condition)) {
            return evaluate(*expr.middle);
        } else {
            return evaluate(*expr.right);
        }
    }
    return nullptr;
}

bool Interpreter::isEqual(const std::any &a, const std::any &b) const {
    return ::isEquals(a, b);
}

void Interpreter::checkNumberOperand(const Token &op, const std::any &operand) {
    if (isNumber(operand)) return;
    if (operand.type() == typeid(double)) return;
    throw RuntimeError(op, "Operand must be a number");
}

void Interpreter::checkNumberOperands(const Token &op, const std::any &left, const std::any &right) const {
    if (isNumber(left) && isNumber(right)) return;
    throw RuntimeError(op, "Operands must be numbers");
}

void Interpreter::interpret(Expr &expr) {
    try {
        std::any value = evaluate(expr);
        std::cout << castAnyToString(value) << std::endl;
    } catch (const RuntimeError &e) {
        Lox::error(0, e.what());
    }
}

void Interpreter::interpret(const std::vector<std::shared_ptr<Stmt>> &statements) {
    try {
        for (const std::shared_ptr<Stmt> &stmt: statements) {
            execute(*stmt);
        }
    } catch (const RuntimeError &e) {
        Lox::runtimeError(e);
    }

}

void Interpreter::execute(Stmt &stmt) {
    stmt.accept(*this);
}


std::any Interpreter::visitExpressionStmt(Expression &stmt) {
    evaluate(*stmt.expression);
    return nullptr;
}

std::any Interpreter::visitPrintStmt(Print &stmt) {
    std::any value = evaluate(*stmt.expression);
    std::cout << castAnyToString(value) << std::endl;
    return nullptr;
}

std::any Interpreter::visitVarStmt(Var &stmt) {
    std::any value = nullptr;
    if (stmt.initializer != nullptr) {
        value = evaluate(*stmt.initializer);
    }

    environment->define(stmt.name.lexeme, value);
    return nullptr;
}

std::any Interpreter::visitAssignExpr(Assign &expr) {
    std::any value = evaluate(*expr.value);
    environment->assign(expr.name, value);
    return value;
}

std::any Interpreter::visitBlockStmt(Block &stmt) {
    executeBlock(stmt.statements, std::make_shared<Environment>(environment));
    return nullptr;
}

void Interpreter::executeBlock(const std::vector<std::shared_ptr<Stmt>>& statements,
                               const std::shared_ptr<Environment> &executionEnvironment) {
    std::shared_ptr<Environment> previous = this->environment;

    // The more common way to do it is to pass an executionEnvironment parameter to each visit method
    try {
        this->environment = executionEnvironment;
        for (const auto &statement: statements) {
            if (statement == nullptr) {
                continue;
            }
            execute(*statement);
        }
    } catch (const RuntimeError &e) {
        this->environment = previous;
        Lox::runtimeError(e);
    }
    this->environment = previous;
}

