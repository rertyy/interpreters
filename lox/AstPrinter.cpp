

#include "../include/lox/AstPrinter.h"
#include <string>
#include <iostream>
#include "../include/lox/Expr.h"
#include "../include/utils/utils.h"


std::string AstPrinter::print(const Expr &expr) {
    return castAnyToString(expr.accept(*this));
}

std::any AstPrinter::visitBinaryExpr(const Binary &expr) const {
    return parenthesize(expr.op.lexeme, expr.left, expr.right);
}

std::any AstPrinter::visitGroupingExpr(const Grouping &expr) const {
    return parenthesize("group", expr.expression);
}

std::any AstPrinter::visitLiteralExpr(const Literal &expr) const {
    try {
        return castAnyToString(expr.value);
    } catch (const std::bad_any_cast &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

std::any AstPrinter::visitUnaryExpr(const Unary &expr) const {
    return parenthesize(expr.op.lexeme, expr.right);
}

template<typename... Exprs>
std::string
AstPrinter::parenthesize(const std::string &name,
                         Exprs &&... expressions) const {
    std::string result = "(" + name;
    ((result += " " + std::any_cast<std::string>(expressions->accept(*this))), ...);
    result += ")";
    return result;
}


