#ifndef _CPPLOX_INTERPRETER_
#define _CPPLOX_INTERPRETER_


#include "../Representation/Stmt.h"
#include "../Representation/Expressions.h"
#include "../Representation/Environment.h"
#include "../Errors/Runtime/RuntimeError.h"
#include "../Errors/CppLoxError.h"
#include <iostream>
#include <vector>


class Interpreter : public StmtVisitor<void>, 
                    public ExprVisitor<Object *> 
{
private:
    Environmnet *environment;

public:
    Interpreter();
    void interpret(std::vector<Stmt*> *expression);

public:
    Object *visitBinaryExpr(Binary* expr) override;
    Object *visitUnaryExpr(Unary* expr) override;
    Object *visitGroupingExpr(Grouping* expr) override;
    Object *visitLiteralExpr(Literal* expr) override;
    Object *visitLogicalExpr(Logical* expr) override;
    Object *visitVariableExpr(Variable *expr) override;
    Object *visitAssignExpr(Assign *expr) override;

    void visitBlockStmt(Block *stmt) override;
    void visitExpressionStmt(Expression *stmt) override;
    void visitIfStmt(If *stmt) override;
    void visitPrintStmt(Print *stmt) override;
    void visitVarStmt(Var *stmt) override;
    void visitWhileStmt(While *stmt) override;

private:
    Object *evaluate(Expr *expr);
    void execute(Stmt *stmt);
    void executeBlock(std::vector<Stmt *> *statements, Environmnet *environment);

    bool isTruthy(Object *object);
    bool isEqual(Object *a, Object *b);
    void checkNumberOperand(Token *oper, Object* operad);
    void checkNumberOperands(Token *oper, Object* left, Object* right);
    std::string stringify(Object *object);
};

#endif /* _CPPLOX_INTERPRETER_ */
