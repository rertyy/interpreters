#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "../include/lox/Token.h"
#include "../include/lox/Lox.h"
#include "../include/lox/Scanner.h"
#include "../include/lox/Parser.h"
#include "../include/lox/AstPrinter.h"

// This can alternatively be declared within Lox.h as `inline static bool`
bool Lox::hadError = false;
bool Lox::hadRuntimeError = false;
Interpreter Lox::interpreter;

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
//        runExprOnly(line);
    }
}

void Lox::runExprOnly(const std::string &source) {
    Scanner scanner{source};
    std::vector<Token> tokens = scanner.scanTokens();

    std::cout << "=== Tokens Begin ===" << std::endl;
    for (const Token &token: tokens) {
        std::cout << token.toString() << std::endl;
    }
    std::cout << "=== Tokens End ===" << std::endl;
    std::cout << std::endl;

    Parser parser{tokens};
    std::shared_ptr<Expr> expression = parser.parseExpr();
    if (hadError) return;

    std::cout << "=== Tree Begin ===" << std::endl;
    AstPrinter printer;
    std::cout << printer.print(*expression) << std::endl;
    std::cout << "=== Tree End ===" << std::endl;
    std::cout << std::endl;
    std::cout << "=== Output Begin ===" << std::endl;
    interpreter.interpret(*expression);
    std::cout << "=== Output End ===" << std::endl;

}

void Lox::run(const std::string &source) {
    Scanner scanner{source};
    std::vector<Token> tokens = scanner.scanTokens();

    std::cout << "=== Tokens Begin ===" << std::endl;
    for (const Token &token: tokens) {
        std::cout << token.toString() << std::endl;
    }
    std::cout << "=== Tokens End ===" << std::endl;
    std::cout << std::endl;
    std::cout << "=== Output Begin ===" << std::endl;
    Parser parser{tokens};
    std::vector<std::shared_ptr<Stmt>> statements = parser.parse();
    if (hadError) return;

    interpreter.interpret(statements);
    std::cout << "=== Output End ===" << std::endl;
}

void Lox::error(int line, const std::string &message) {
    report(line, "", message);
}

void Lox::report(int line, const std::string &where, const std::string &message) {
    std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
}

void Lox::error(const Token &token, const std::string &message) {
    if (token.type == TokenType::EOF_TOKEN) {
        report(token.line, " at end", message);
    } else {
        report(token.line, " at '" + token.lexeme + "'", message);
    }

}

void Lox::runtimeError(const RuntimeError &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << "[line " << error.token.line << "]" << std::endl;
    hadRuntimeError = true;

}

