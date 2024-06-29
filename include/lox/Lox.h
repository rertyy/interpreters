#ifndef INTERPRETERS_LOX_H
#define INTERPRETERS_LOX_H

#include <string>
#include "Token.h"
#include "RuntimeError.h"
#include "Interpreter.h"

class Lox {
public:
    static void main(int argc, char *argv[]);

    static bool hadError;

    static bool hadRuntimeError;

    static void runFile(const std::string &path);

    static void runPrompt();

    static void run(const std::string &source);

    static void runExpr(const std::string &source);


    static void error(int line, const std::string &message);

    static void error(const Token &token, const std::string &message);

    static void report(int line, const std::string &where, const std::string &message);

    static void runtimeError(const RuntimeError &error);

private:
    static Interpreter interpreter;

};

#endif //INTERPRETERS_LOX_H
