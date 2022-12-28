#ifndef _CPPLOX_INTERPRETER_
#define _CPPLOX_INTERPRETER_


class Object;
class Environment;
class Expr;
class Stmt;
class Token;

class Expression;
class Print;
class Var;
class Block;
class If;
class While;
class Function;
class Assign;
class Unary;
class Binary;
class Literal;
class Grouping;
class Variable;
class Logical;
class Call;


#include <iostream>
#include <sstream>
#include <vector>


#include "../Visitors/ExprVisitor.h"
#include "../Visitors/StmtVisitor.h"


class Interpreter : public StmtVisitor<void>, 
                    public ExprVisitor<Object *> 
{
public:
    Environment *globals;
    Environment *environment;

public:
    Interpreter();
    void interpret(std::vector<Stmt*> *expression);

public:
    Object *visitBinaryExpr(Binary* expr) override;
    Object *visitCallExpr(Call *expr) override;
    Object *visitUnaryExpr(Unary* expr) override;
    Object *visitGroupingExpr(Grouping* expr) override;
    Object *visitLiteralExpr(Literal* expr) override;
    Object *visitLogicalExpr(Logical* expr) override;
    Object *visitVariableExpr(Variable *expr) override;
    Object *visitAssignExpr(Assign *expr) override;

    void visitBlockStmt(Block *stmt) override;
    void visitExpressionStmt(Expression *stmt) override;
    void visitFunctionStmt(Function *stmt) override;
    void visitIfStmt(If *stmt) override;
    void visitPrintStmt(Print *stmt) override;
    void visitReturnStmt(Return *stmt) override;
    void visitVarStmt(Var *stmt) override;
    void visitWhileStmt(While *stmt) override;

    void executeBlock(std::vector<Stmt *> *statements, Environment *environment);

private:
    Object *evaluate(Expr *expr);
    void execute(Stmt *stmt);

    bool isTruthy(Object *object);
    bool isEqual(Object *a, Object *b);
    void checkNumberOperand(Token *oper, Object* operad);
    void checkNumberOperands(Token *oper, Object* left, Object* right);
    std::string stringify(Object *object);
};

#endif /* _CPPLOX_INTERPRETER_ */
