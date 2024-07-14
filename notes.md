###

1. Scan tokens
2. Parse tokens into token tree
3. Evaluate token tree

### Scanner

* Scanner is basically just a massive switch case using maximal munching

### Visitor pattern for Expr.

* Visitor pattern is declared within Expr hierarchy because other classes have their own Visitor as well.
* Visitor pattern is normally used for double dispatch, i.e. virtual polymorphism on obj1.accept(obj2)
* where obj1 is the visitor and obj2 is the visited and **BOTH** obj1 and obj2 can have runtime polymorphism
* E.g. used in Ch5 for printing the AST.
* Call hierarchy:
    1. AstPrinter inherits from `Expr::Visitor`. Let `expr`, the visited, be `Binary{}`
    2. `AstPrinter.cpp`:  `AstPrinter::print(expr)` calls `expr.accept(*this)`.
    3. `Expr.cpp`:        `Binary::accept(AstPrinter{})` calls `visitor.visitBinaryExpr(*this)`.
    4. `Expr.cpp`:        `AstPrinter::visitBinaryExpr(expr)` calls `AstPrinter::parenthesize()` which repeats the
       process
* This allows the Visitor to automatically call the correct method based on the type of the visited object.
* Kinda like a `switch` statement within the Visitor method, but you shift onus of switch-case exhaustiveness onto the
  Visitor
* And you can modify the Visitor to your needs

### Recursive Descent (Parsing into Parse Tree)

See the (pseudo)-BNF in include/Parser.h

* In `Parser.cpp`, start by parsing the lowest precedence operator before recursively parsing into the remaining
  operators.
* With the BNF grammar, basically one function per grammar rule.
* Call the lowest precedence first (comma operator, then assignment, then equality, etc.)
* The syntax doesn't care that "and", "or" expressions short-circuit. That’s a semantic concern. (From the book)
* For loop can be desugared to while loop by doing while, then increment, then body
* Note to avoid accidentally calling `Parser::commaOperator` for arguments or expressions

### Interpreter (Evaluation)

* Dangling else problem resolved using most recent if statement
* `break`, `continue`, `return`: because they are nested, easiest way given a deeply nested recursive parse tree
  is to throw an exception and catch it within `Interpreter.cpp`. The current implementation of `for` loops desugars
  the loop into an `initializer; while{body; increment;}` loop. Hence with this current implementation `continue` is not
  possible for `for` loops because an exception will cut past the `increment` portion of the `for` loop. I think the
  only way to do it is to have a separate `Stmt::For` class and to not desugar to `while`.


* TODO: Refactor `match` and `consume` functions
* TODO: make things `const`
* TODO: make empty statements`;;` work
* TODO: do I really need to throw `std::shared_ptr` everywhere instead of `std::unique_ptr`?
* TODO: add utils namespace to `utils` methods
* TODO: I recall having problems with templates for Visitor and Expr, not sure if it makes sense to be added back
* TODO: make functions work... `printHi` works, but not return statements because the environment is somehow shared

# CPP Notes

* To build: https://stackoverflow.com/a/7859663
    1. cd build
    2. cmake ..
    3. make
    4. ./interpreters

* Use of shared_ptr since there may be multiple usages of the same object (RAII). Being very careful of accidentally
  using `new` or `.` operators.
* Const methods means the method doesn't change the object's state
    * I removed const methods because some of the visitor
      methods (`Interpreter::visitVarStmt`, `Interpreter::visitAssignExpr`) do mutate
      class fields. The usage of virtual methods (inheritance) means that the methods need to have the same signature
* Reference for Template varargs in `AstPrinter::parenthesize`
* Java `instanceof` keyword is done using `std::dynamic_cast` in C++ (`Parser::assignment`)
* Java generic classes and methods don't seem to translate very well to C++ template specialisation (looking
  specifically at the Visitor pattern)
* `std::string` and `std::vector` support move semantics, so you can return them by value without worrying about
  performance
* Beware of object slicing where `class A : public B {}` and `A a = b` will slice off the `B` part of `b` because of
  pass-by-value. No issue if using pointers.
