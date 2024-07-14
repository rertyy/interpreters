#include <iostream>
#include "../include/lox/LoxFunction.h"
#include "../include/lox/Environment.h"
#include "../include/lox/exceptions/ReturnException.h"

//LoxFunction::LoxFunction(std::shared_ptr<Function> declaration, std::shared_ptr<Environment> closure)
//        : declaration(std::move(declaration)), closure(std::move(closure)) {}



LoxFunction::LoxFunction(const std::shared_ptr<Function> &declaration)
        : declaration(declaration) {}

/**
 * A new environment is made at each call
 * The parameters are defined in the new environment
 * The block is executed in the new environment
 */
std::any LoxFunction::call(Interpreter &interpreter, const std::vector<std::any> &arguments) {
    // Make a new copy of global functionExecutionEnvironment because the Function needs to be able to access the global variables

    // TODO: I'm not sure why but fib(n-1) + fib(n-2) has child environments executed in the same environment
    // Create a new environment for the function to execute in
    auto functionExecutionEnvironment = std::make_shared<Environment>(*interpreter.environment);
//    auto functionExecutionEnvironment = std::make_shared<Environment>(*closure);

    // Ensure the new functionExecutionEnvironment created has access to the variables within the function body
    for (int i = 0; i < declaration->params.size(); ++i) {
        functionExecutionEnvironment->define(declaration->params[i].lexeme,
                                             arguments[i]);
    }

    try {
        // Execute the statements declaration->body within the new functionExecutionEnvironment
        // (executeBlock returns to the previous environment automatically after execution)
        interpreter.executeBlock(declaration->body, functionExecutionEnvironment);
    } catch (const ReturnException &returnValue) {
        return returnValue.value;
    }

    return nullptr;

}

int LoxFunction::arity() {
    return static_cast<int>(declaration->params.size());
}

std::string LoxFunction::toString() const {
    return "<fn " + declaration->name.lexeme + ">";
}

std::ostream &operator<<(std::ostream &os, const LoxFunction &function) {
    os << function.toString();
    return os;
}

