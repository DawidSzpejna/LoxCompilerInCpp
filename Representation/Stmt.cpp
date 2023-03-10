#include "Stmt.h"


#include "Expressions.h"


// ------------------- Block --------------------------------------


Block::Block(std::vector<Stmt *> *statements) {
    this->statements = statements;
}


void Block::accpetV(StmtVisitor<void> *visitor) {
    visitor->visitBlockStmt(this);
}


// ------------------- Class ---------------------------------------


Class::Class (Token *name, Variable *superclass, std::vector<Function *> *methods) {
    this->name = name;
    this->methods = methods;
    this->superclass = superclass;
}

void Class::accpetV(StmtVisitor<void> *visitor) {
    visitor->visitClassStmt(this);
}


// ------------------- If ------------------------------------------


If::If (Expr *condition, Stmt *thenBranch, Stmt *elseBranch) {
    this->condition = condition;
    this->thenBranch = thenBranch;
    this->elseBranch = elseBranch;
}


void If::accpetV(StmtVisitor<void> *visitor) {
    visitor->visitIfStmt(this);
}


// ------------------- Function -------------------------------------


Function::Function (Token *name, std::vector<Token *> *params, std::vector<Stmt *> *body) {
    this->name = name;
    this->params = params;
    this->body = body;
}

void Function::accpetV(StmtVisitor<void> *visitor) {
    visitor->visitFunctionStmt(this);
}


// ------------------- Expression ------------------------------------


Expression::Expression (Expr *expression) {
    this->expression = expression;
}


void Expression::accpetV(StmtVisitor<void> *visitor) {
    visitor->visitExpressionStmt(this);
}


// ------------------- Print --------------------------------------


Print::Print (Expr *expression) {
    this->expression = expression;
}


void Print::accpetV(StmtVisitor<void> *visitor) {
    visitor->visitPrintStmt(this);
}


// ------------------- Return -----------------------------------


Return::Return (Token *keyword, Expr *value) {
    this->keyword = keyword;
    this->value = value;
}

void Return::accpetV(StmtVisitor<void> *visitor) {
    visitor->visitReturnStmt(this);
}


// ------------------- Var --------------------------------------


Var::Var( Token *name, Expr *initializer) {
    this->name = name;
    this->initializer = initializer;
}

void Var::accpetV(StmtVisitor<void> *visitor) {
    visitor->visitVarStmt(this);
}


// -------------------- While -------------------------------------


While::While (Expr *condition, Stmt *body) {
    this->condition = condition;
    this->body = body;
}

void While::accpetV(StmtVisitor<void> *visitor) {
    visitor->visitWhileStmt(this);
}
