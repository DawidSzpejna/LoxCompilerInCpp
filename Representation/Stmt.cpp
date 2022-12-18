#include "Stmt.h"


// ------------------- Block --------------------------------------


Block::Block(std::vector<Stmt *> *statements) {
    this->statements = statements;
}


void Block::accpetV(StmtVisitor<void> *visitor) {
    visitor->visitBlockStmt(this);
}


// ------------------- If ----------------------------------------------


If::If (Expr *condition, Stmt *thenBranch, Stmt *elseBranch) {
    this->condition = condition;
    this->thenBranch = thenBranch;
    this->elseBranch = elseBranch;
}


void If::accpetV(StmtVisitor<void> *visitor) {
    visitor->visitIfStmt(this);
}


// ------------------- Expression --------------------------------------


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
