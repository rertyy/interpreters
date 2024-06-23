
#ifndef INTERPRETERS_INTERPRETER_H
#define INTERPRETERS_INTERPRETER_H


#include "../include/lox/Expr.h"

class Interpreter : public Visitor {
public:
    std::any visitLiteralExpr(Literal &expr) override;

    std::any visitGroupingExpr(Grouping &expr) override;

private:
    std::any evaluate(Expr &expr);


};


#endif //INTERPRETERS_INTERPRETER_H
