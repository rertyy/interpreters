#ifndef INTERPRETERS_ASTPRINTER_H
#define INTERPRETERS_ASTPRINTER_H

#include "Expr.h"
#include <string>

class AstPrinter : public Expr::Visitor {
public:
    std::string print(Expr &expr);

    std::any visitBinaryExpr(Binary &expr) override;

    std::any visitGroupingExpr(Grouping &expr) override;

    std::any visitLiteralExpr(Literal &expr) override;

    std::any visitUnaryExpr(Unary &expr) override;

    std::any visitVariableExpr(Variable &expr) override;

    /**
     * @brief Parenthesize the given expressions into Polish notation
     */
    template<typename... Exprs>
    std::string parenthesize(const std::string &name,
                             Exprs &&... expressions);
};

#endif //INTERPRETERS_ASTPRINTER_H
