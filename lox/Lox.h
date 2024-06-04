#ifndef INTERPRETERS_LOX_H
#define INTERPRETERS_LOX_H

#include <string>

class Lox {
public:
    static void main(int argc, char *argv[]);

    static bool hadError;

    static void runFile(const std::string &path);

    static void runPrompt();

    static void run(const std::string &source);

    static void error(int line, const std::string &message);

    static void report(int line, const std::string &where, const std::string &message);
};

#endif //INTERPRETERS_LOX_H
