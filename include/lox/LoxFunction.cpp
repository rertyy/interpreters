#include "LoxFunction.h"
#include "Environment.h"

/**
 * A new environment is made at each call
 * The parameters are defined in the new environment
 * The block is executed in the new environment
 */
std::any LoxFunction::call(Interpreter &interpreter, const std::vector<std::any> &arguments) {
    // It looks like the function is being called from the global environment???
    // Nvm this gets replaced later
    // Make a new copy of global functionExecutionEnvironment because the Function needs to be able to access the global variables
    std::shared_ptr<Environment> functionExecutionEnvironment =
            std::make_shared<Environment>(*interpreter.globals);

    // Ensure the new functionExecutionEnvironment created has access to the variables within the function body
    for (int i = 0; i < declaration->params.size(); i++) {
        functionExecutionEnvironment->define(declaration->params[i].lexeme,
                                             std::make_optional<>(arguments[i]));
    }

    // Execute the statements declaration->body within the new functionExecutionEnvironment
    // (executeBlock returns to the previous environment automatically after execution)
    interpreter.executeBlock(declaration->body, functionExecutionEnvironment);

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

