#ifndef INTERPRETERS_RUNTIMEERROR_H
#define INTERPRETERS_RUNTIMEERROR_H


#include <stdexcept>
#include "Token.h"

class RuntimeError : public std::runtime_error {
public:
    RuntimeError(Token token, const std::string &message) :
            std::runtime_error(message), token(std::move(token)) {
    }

    const Token token;
};


#endif //INTERPRETERS_RUNTIMEERROR_H
