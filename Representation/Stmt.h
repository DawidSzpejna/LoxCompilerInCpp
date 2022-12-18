#ifndef _CPPLOX_STMT_
#define _CPPLOX_STMT_


#include "Expressions.h"
#include <vector>


class Expression;
class Print;
class Var;
class Block;
class If;
class While;


template <typename R>
class StmtVisitor{
public:
    virtual R visitBlockStmt(Block *stmt) = 0;
    //virtual R visitClassStmt(Class stmt) = 0;
    virtual R visitExpressionStmt(Expression *stmt) = 0;
    //virtual R visitFunctionStmt(Function stmt) = 0;
    virtual R visitIfStmt(If *stmt) = 0;
    virtual R visitPrintStmt(Print *stmt) = 0;
    //virtual R visitReturnStmt(Return stmt) = 0;
    virtual R visitVarStmt(Var *stmt) = 0;
    virtual R visitWhileStmt(While *stmt) = 0;
};


class Stmt {
public:
    virtual void accpetV(StmtVisitor<void> *visitor) {}
};


class Block : public Stmt {
public: 
    Block(std::vector<Stmt *> *statements);
    
    void accpetV(StmtVisitor<void> *visitor) override;

    std::vector<Stmt *> *statements;
};


class Expression : public Stmt {
public: 
    Expression (Expr *expression);

    void accpetV(StmtVisitor<void> *visitor) override;

    Expr *expression;
};


class If : public Stmt {
public: 
    If (Expr *condition, Stmt *thenBranch, Stmt *elseBranch);

    void accpetV(StmtVisitor<void> *visitor) override;

    Expr *condition;
    Stmt *thenBranch;
    Stmt *elseBranch;
};


class Print : public Stmt {
public: 
    Print (Expr *expression);

    void accpetV(StmtVisitor<void> *visitor) override;

    Expr *expression;
};


class Var : public Stmt {
public: 
    Var( Token *name, Expr *initializer);

    void accpetV(StmtVisitor<void> *visitor) override;

    Token *name;
    Expr *initializer;
};


class While : public Stmt {
public: 
    While (Expr *condition, Stmt *body);

    void accpetV(StmtVisitor<void> *visitor) override;

    Expr *condition;
    Stmt *body;
};


#endif /* _CPPLOX_STMT_ */
