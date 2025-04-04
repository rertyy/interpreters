#include <any>
#include "../include/lox/Expr.h"

Assign::Assign(Token name, std::shared_ptr<Expr> value) : name(std::move(name)), value(std::move(value)) {}

std::any Assign::accept(Visitor &visitor) {
    return visitor.visitAssignExpr(*this);
}

Binary::Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) : left(std::move(left)),
                                                                                    op(std::move(op)),
                                                                                    right(std::move(right)) {}

std::any Binary::accept(Visitor &visitor) {
    return visitor.visitBinaryExpr(*this);
}

Call::Call(std::shared_ptr<Expr> callee, Token paren, std::vector<std::shared_ptr<Expr>> arguments) : callee(
        std::move(callee)), paren(std::move(paren)), arguments(std::move(arguments)) {}

std::any Call::accept(Visitor &visitor) {
    return visitor.visitCallExpr(*this);
}

Ternary::Ternary(std::shared_ptr<Expr> left, Token op1, std::shared_ptr<Expr> middle, Token op2,
                 std::shared_ptr<Expr> right) : left(std::move(left)), op1(std::move(op1)), middle(std::move(middle)),
                                                op2(std::move(op2)), right(std::move(right)) {}

std::any Ternary::accept(Visitor &visitor) {
    return visitor.visitTernaryExpr(*this);
}

Grouping::Grouping(std::shared_ptr<Expr> expression) : expression(std::move(expression)) {}

std::any Grouping::accept(Visitor &visitor) {
    return visitor.visitGroupingExpr(*this);
}

Literal::Literal(std::any value) : value(std::move(value)) {}

std::any Literal::accept(Visitor &visitor) {
    return visitor.visitLiteralExpr(*this);
}

Logical::Logical(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) : left(std::move(left)),
                                                                                      op(std::move(op)),
                                                                                      right(std::move(right)) {}

std::any Logical::accept(Visitor &visitor) {
    return visitor.visitLogicalExpr(*this);
}

Unary::Unary(Token op, std::shared_ptr<Expr> right) : op(std::move(op)), right(std::move(right)) {}

std::any Unary::accept(Visitor &visitor) {
    return visitor.visitUnaryExpr(*this);
}

Variable::Variable(Token name) : name(std::move(name)) {}

std::any Variable::accept(Visitor &visitor) {
    return visitor.visitVariableExpr(*this);
}

