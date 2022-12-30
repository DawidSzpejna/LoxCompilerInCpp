#ifndef _CPPLOX_RESOLVER_
#define _CPPLOX_RESOLVER_

class Expr;
class Stmt;
class Interpreter;
class Object;
class Token;

class Assign;
class Unary;
class Binary;
class Literal;
class Grouping;
class Variable;
class Logical;
class Call;
class Expression;
class Print;
class Var;
class Block;
class If;
class While;
class Function;
class Return;
class Class;
class Get;
class Set;
class This;


#include "../Visitors/ExprVisitor.h"
#include "../Visitors/StmtVisitor.h"


#include <vector>
#include <vector>
#include <map>
#include <iostream>


enum class FunctionType {
    NONE,
    INITIALIZER,
    METHOD,
    FUNCTION
};


enum class ClassType {
    NONE,
    CLASS
};


/* 
 Variables declared at the top level in the global scope are not tracked 
 by the resolver since they are more dynamic in Lox. When resolving a variable, 
 if we can’t find it in the stack of local scopes, we assume it must be global. 
*/
class Resolver : public ExprVisitor<Object *>, 
                 public StmtVisitor<void> 
{
private:
    Interpreter* interpreter;

    // string - variable name (in program)
    std::vector<std::map<std::string, bool> *> *scopes;

    // point whether the body of function is checking
    FunctionType currentFunction;

    // point wheter the body of method is checking
    ClassType currentClass;

public:
    Resolver(Interpreter* interpreter);
    ~Resolver();

    Object *visitBinaryExpr(Binary* expr) override;
    Object *visitCallExpr(Call *expr) override;
    Object *visitGetExpr(Get *expr) override;
    Object *visitUnaryExpr(Unary* expr) override;
    Object *visitGroupingExpr(Grouping* expr) override;
    Object *visitLiteralExpr(Literal* expr) override;
    Object *visitLogicalExpr(Logical* expr) override;
    Object *visitSetExpr(Set *expr) override;
    Object *visitThisExpr(This *expr) override;
    Object *visitVariableExpr(Variable *expr) override;
    Object *visitAssignExpr(Assign *expr) override;

    void visitBlockStmt(Block *stmt) override;
    void visitClassStmt(Class *stmt) override;
    void visitExpressionStmt(Expression *stmt) override;
    void visitFunctionStmt(Function *stmt) override;
    void visitIfStmt(If *stmt) override;
    void visitPrintStmt(Print *stmt) override;
    void visitReturnStmt(Return *stmt) override;
    void visitVarStmt(Var *stmt) override;
    void visitWhileStmt(While *stmt) override;

    void resolve(std::vector<Stmt *> *statements);

private:
    void resolve(Stmt *stmt);
    void resolve(Expr *expr);
    void beginScope();
    void endScope();
    void declare(Token *token);
    void define(Token *token);
    void resolveLocal(Expr *expr, Token *name);
    void resolveFunctions(Function *function, FunctionType type);
};

#endif
