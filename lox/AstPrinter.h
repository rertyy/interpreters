#ifndef INTERPRETERS_ASTPRINTER_H
#define INTERPRETERS_ASTPRINTER_H

#include "Expr.h"
#include <string>

class AstPrinter : public Visitor<std::string> {
public:
    std::string print(const Expr<std::string> &expr);

    std::string visitBinaryExpr(const Binary<std::string> &expr) const override;


    std::string visitGroupingExpr(const Grouping<std::string> &expr) const override;

    std::string visitLiteralExpr(const Literal<std::string> &expr) const override;

    std::string visitUnaryExpr(const Unary<std::string> &expr);

};


#endif //INTERPRETERS_ASTPRINTER_H
