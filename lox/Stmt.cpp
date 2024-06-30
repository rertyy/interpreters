#include <any>
#include "../include/lox/Stmt.h"


Block::Block(std::vector<std::shared_ptr<Stmt>> statements) : statements(std::move(statements)) {}

std::any Block::accept(Visitor &visitor) {
    return visitor.visitBlockStmt(*this);
}

Expression::Expression(std::shared_ptr<Expr> expression) : expression(std::move(expression)) {}

std::any Expression::accept(Visitor &visitor) {
    return visitor.visitExpressionStmt(*this);
}

Print::Print(std::shared_ptr<Expr> expression) : expression(std::move(expression)) {}

std::any Print::accept(Visitor &visitor) {
    return visitor.visitPrintStmt(*this);
}

Var::Var(Token name, std::shared_ptr<Expr> initializer) : name(std::move(name)), initializer(std::move(initializer)) {}

std::any Var::accept(Visitor &visitor) {
    return visitor.visitVarStmt(*this);
}

