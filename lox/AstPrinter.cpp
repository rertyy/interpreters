

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

std::any AstPrinter::visitUnaryExpr(Unary &expr) {
    return parenthesize(expr.op.lexeme, expr.right);
}

std::any AstPrinter::visitVariableExpr(Variable &expr) {
    return expr.name.lexeme;
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


