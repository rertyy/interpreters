

#include "../include/lox/AstPrinter.h"
#include <string>
#include <iostream>
#include "../include/lox/Expr.h"
#include "../include/utils/utils.h"


std::string AstPrinter::print(Expr &expr) {
    return castAnyToString(expr.accept(*this));
}

std::any AstPrinter::visitBinaryExpr(Binary &expr) {
    return parenthesize(expr.op.lexeme, expr.left, expr.right);
}

std::any AstPrinter::visitGroupingExpr(Grouping &expr) {
    return parenthesize("group", expr.expression);
}

std::any AstPrinter::visitLiteralExpr(Literal &expr) {
    try {
        return castAnyToString(expr.value);
    } catch (const std::bad_any_cast &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return {};
}

std::any AstPrinter::visitLogicalExpr(Logical &expr) {
    return parenthesize(expr.op.lexeme, expr.left, expr.right);
}

std::any AstPrinter::visitUnaryExpr(Unary &expr) {
    return parenthesize(expr.op.lexeme, expr.right);
}

std::any AstPrinter::visitVariableExpr(Variable &expr) {
    return expr.name.lexeme;
}

std::any AstPrinter::visitTernaryExpr(Ternary &expr) {
    return parenthesize("ternary", expr.left, expr.middle, expr.right);
}

std::any AstPrinter::visitAssignExpr(Assign &expr) {
    const std::string name = "= " + expr.name.lexeme;
    return parenthesize(name, expr.value);
}

std::any AstPrinter::visitCallExpr(Call &expr) {
    std::string result = "(call " + std::any_cast<std::string>(expr.callee->accept(*this));

    for (const auto &argument: expr.arguments) {
        result += " " + std::any_cast<std::string>(argument->accept(*this));
    }

    result += ")";
    return result;
}

template<typename... Exprs>
std::string
AstPrinter::parenthesize(const std::string &name,
                         Exprs &&... expressions) {
    std::string result = "(" + name;
    ((result += " " + std::any_cast<std::string>(expressions->accept(*this))), ...);
    result += ")";
    return result;
}


