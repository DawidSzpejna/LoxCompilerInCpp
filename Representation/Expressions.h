#ifndef _CPPLOX_EXPRESSIONS_
#define _CPPLOX_EXPRESSIONS_


#include "Token.h"


class Expr;
class Assign;
class Unary;
class Binary;
class Literal;
class Grouping;
class Variable;
class Logical;


template <typename R>
class ExprVisitor{
public:
    virtual R visitAssignExpr(Assign* expr) = 0;
    virtual R visitBinaryExpr(Binary *expr) = 0;
    //virtual R visitCallExpr(Call* expr) = 0;
    //virtual R visitGetExpr(Get* expr) = 0;
    virtual R visitGroupingExpr(Grouping *expr) = 0;
    virtual R visitLiteralExpr(Literal *expr) = 0;
    virtual R visitLogicalExpr(Logical* expr) = 0;
    //virtual R visitSetExpr(Set* expr) = 0;
    //virtual R visitSuperExpr(Super* expr) = 0;
    //virtual R visitThisExpr(This* expr); = 0;
    virtual R visitUnaryExpr(Unary *expr) = 0;
    virtual R visitVariableExpr(Variable *expr) = 0;
};


class Expr {
public:
    virtual std::string acceptS(ExprVisitor<std::string> *visitor) { return ""; }
    virtual Object* accpetO(ExprVisitor<Object *> *visitor) { return nullptr; }
};


class Assign : public Expr {
public: 
    Assign (Token *name, Expr *value);

    std::string acceptS(ExprVisitor<std::string> *visitor) override;
    Object *accpetO(ExprVisitor<Object *> *visitor) override;

    Token *name;
    Expr *value;
};


class Binary : public Expr {
public: 
    Binary ( Expr *left, Token *this_operator, Expr *right);
    ~Binary();

    std::string acceptS(ExprVisitor<std::string> *visitor) override;
    Object *accpetO(ExprVisitor<Object *> *visitor) override;

    Expr *left;
    Token *this_operator;
    Expr *right;
};


class Grouping : public Expr {
public: 
    Grouping ( Expr* expression);
    ~Grouping();

    std::string acceptS(ExprVisitor<std::string> *visitor) override;
    Object *accpetO(ExprVisitor<Object *> *visitor) override;

    Expr *expression;
};


class Unary : public Expr {
public: 
    Unary ( Token* this_operator, Expr* right);
    ~Unary();

    std::string acceptS(ExprVisitor<std::string> *visitor) override;
    Object *accpetO(ExprVisitor<Object *> *visitor) override;

    Token *this_operator;
    Expr *right;
};


class Logical  : public Expr {
public: 
    Logical (Expr *left, Token *this_operator, Expr *right);

    std::string acceptS(ExprVisitor<std::string> *visitor) override;
    Object *accpetO(ExprVisitor<Object *> *visitor) override;

    Expr *left;
    Token *this_operator;
    Expr *right;
};


class Literal : public Expr {
public:
    Literal(Object *value);
    ~Literal();

    std::string acceptS(ExprVisitor<std::string> *visitor) override;
    Object *accpetO(ExprVisitor<Object *> *visitor) override;

    Object *value;
};


class Variable : public Expr {
public: 
    Variable ( Token *name);
    
    std::string acceptS(ExprVisitor<std::string> *visitor) override;
    Object *accpetO(ExprVisitor<Object *> *visitor) override;

    Token *name;
};


#endif