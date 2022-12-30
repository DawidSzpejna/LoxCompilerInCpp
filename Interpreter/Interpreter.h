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
class Class;
class Get;
class Set;
class This;
class Super;


#include <iostream>
#include <sstream>
#include <vector>
#include <map>


#include "../Visitors/ExprVisitor.h"
#include "../Visitors/StmtVisitor.h"


class Interpreter : public StmtVisitor<void>, 
                    public ExprVisitor<Object *> 
{
public:
    Environment *globals;
    Environment *environment;
    std::map<Expr *, int> *locals;

public:
    Interpreter();
    void interpret(std::vector<Stmt*> *expression);

public:
    Object *visitBinaryExpr(Binary* expr) override;
    Object *visitCallExpr(Call *expr) override;
    Object *visitGetExpr(Get *expr) override;
    Object *visitUnaryExpr(Unary* expr) override;
    Object *visitGroupingExpr(Grouping* expr) override;
    Object *visitLiteralExpr(Literal* expr) override;
    Object *visitLogicalExpr(Logical* expr) override;
    Object *visitSetExpr(Set *expr) override;
    Object *visitSuperExpr(Super *expr) override;
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

    void executeBlock(std::vector<Stmt *> *statements, Environment *environment);
    void resolve(Expr *expr, int depth);
private:
    Object *evaluate(Expr *expr);
    void execute(Stmt *stmt);

    bool isTruthy(Object *object);
    bool isEqual(Object *a, Object *b);
    void checkNumberOperand(Token *oper, Object* operad);
    void checkNumberOperands(Token *oper, Object* left, Object* right);
    std::string stringify(Object *object);
    Object *lookUpVariable(Token *name, Expr *expr);
};

#endif /* _CPPLOX_INTERPRETER_ */
