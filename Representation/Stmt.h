#ifndef _CPPLOX_STMT_
#define _CPPLOX_STMT_


class Expr;
class Token;
class Variable;


#include "../Visitors/StmtVisitor.h"


#include <vector>


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


class Class : public Stmt {
public: 
    Class (Token *name, Variable *superclass, std::vector<Function *> *methods);

    void accpetV(StmtVisitor<void> *visitor) override;

    Token *name;
    Variable *superclass;
    std::vector<Function *> *methods;
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


class Function : public Stmt {
public: 
    Function (Token *name, std::vector<Token *> *params, std::vector<Stmt *> *body);

    void accpetV(StmtVisitor<void> *visitor) override;

    Token *name;
    std::vector<Token *> *params;
    std::vector<Stmt *> *body;
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


class Return : public Stmt {
public: 
    Return (Token *keyword, Expr *value);

    void accpetV(StmtVisitor<void> *visitor) override;

    Token *keyword;
    Expr *value;
};


class While : public Stmt {
public: 
    While (Expr *condition, Stmt *body);

    void accpetV(StmtVisitor<void> *visitor) override;

    Expr *condition;
    Stmt *body;
};


#endif /* _CPPLOX_STMT_ */
