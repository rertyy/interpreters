#ifndef INTERPRETERS_LOXFUNCTION_H
#define INTERPRETERS_LOXFUNCTION_H


#include <memory>
#include "LoxCallable.h"
#include "Stmt.h"

class LoxFunction : public LoxCallable {
public:
    explicit LoxFunction(const std::shared_ptr<Function> &declaration)
            : declaration(declaration) {};

    int arity() override;

    std::any call(Interpreter &interpreter, const std::vector<std::any> &arguments) override;


    std::string toString() const override;

private:
    std::shared_ptr<Function> declaration;
};


#endif //INTERPRETERS_LOXFUNCTION_H