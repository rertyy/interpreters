#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Token.h"
#include "Lox.h"

// This can alternatively be declared within Lox.h as `inline static bool`
bool Lox::hadError = false;

void Lox::main(int argc, char *argv[]) {
    if (argc > 2) {
        std::cerr << "Usage: jlox [script]" << std::endl;
        exit(64);
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        runPrompt();
    }
}


void Lox::runFile(const std::string &path) {
    if (hadError) {
        exit(65);
    }
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Could not open file: " << path << std::endl;
        exit(65);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    run(buffer.str());
}

void Lox::runPrompt() {

    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        run(line);
    }
}

void Lox::run(const std::string &source) {
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();

    for (const auto &token: tokens) {
        std::cout << token << std::endl;
    }
}

void Lox::error(int line, const std::string &message) {
    report(line, "", message);
}

void Lox::report(int line, const std::string &where, const std::string &message) {
    std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
}

