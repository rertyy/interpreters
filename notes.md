### Visitor pattern for Expr.

* Visitor pattern is declared within Expr hierarchy because other classes have their own Visitor as well.
* Visitor pattern is normally used for double dispatch, i.e. virtual polymorphism on obj1.accept(obj2)
* where obj1 is the visitor and obj2 is the visited and **BOTH** obj1 and obj2 can have runtime polymorphism
* This is used in Ch5 for printing the AST.
* AstPrinter inherits from Expr::Visitor. Let expr, the visited, be Binary{}
* AstPrinter.cpp:  AstPrinter::print(expr) calls expr.accept(*this).
* Expr.cpp:        Binary::accept(AstPrinter{}) calls visitor.visitBinaryExpr(*this).
* Expr.cpp:        AstPrinter::visitBinaryExpr(expr) calls AstPrinter::parenthesize() which repeats the process
* This allows the visitor to automatically call the correct method based on the type of the visited object.
* Kinda like a switch statement within the Visitor method, so you shift onus of completeness onto the Visitor
* And you can modify the Visitor to your needs

### Recursive Descent (Parsing into Parse Tree)

