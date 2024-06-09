#include <memory>
#include "include/lox/Lox.h"
#include "include/tool/GenerateAST.h"
#include "include/lox/Expr.h"
#include "include/lox/AstPrinter.h"


int testAst() {
    // Only pass in strings or there will be errors
    std::shared_ptr<Expr> expression = std::make_shared<Binary>(
            std::make_shared<Unary>(
                    Token(TokenType::MINUS, "-", std::any(), 1),
                    std::make_shared<Literal>(123)),
            Token(TokenType::STAR, "*", std::any(), 1),
            std::make_shared<Grouping>(
                    std::make_shared<Literal>(45.67)));

//    std::shared_ptr<Expr> expression = std::make_shared<Literal>("45.67");

    AstPrinter printer;
    std::cout << printer.print(*expression) << std::endl;
    return 0;
}

int codegen() {
    char *args[] = {const_cast<char *>("generate_ast"), const_cast<char *>("/home/ian/interpreters/lox")};
    GenerateAST::main(2, args);

    return 0;
}


int main(int argc, char *argv[]) {
//    codegen();
//    testAst();
    Lox::main(argc, argv);
    return 0;
}
