#include "Expressions.h"
#include <sstream>


// ------------------- Assign --------------------------------------


Assign::Assign ( Token *name, Expr *value) {
    this->name = name;
    this->value = value;
}


std::string Assign::acceptS(ExprVisitor<std::string> *visitor) {
    return visitor->visitAssignExpr(this);
}


Object *Assign::accpetO(ExprVisitor<Object *> *visitor) {
    return visitor->visitAssignExpr(this);
}


// ------------------- Binary --------------------------------------


Binary::Binary ( Expr *left, Token *this_operator, Expr *right) {
    this->left = left;
    this->this_operator = this_operator;
    this->right = right;
}


std::string Binary::acceptS(ExprVisitor<std::string> *visitor) { 
    return visitor->visitBinaryExpr(this);
}

Object *Binary::accpetO(ExprVisitor<Object *> *visitor) {
    return visitor->visitBinaryExpr(this);
}


Binary::~Binary() {
    delete left;
    delete this_operator;
    delete right;
}


// ------------------- Grouping --------------------------------------


Grouping::Grouping ( Expr *expression) {
    this->expression = expression;
}


std::string Grouping::acceptS(ExprVisitor<std::string> *visitor) { 
    return visitor->visitGroupingExpr(this);
}


Object *Grouping::accpetO(ExprVisitor<Object *> *visitor) {
    return visitor->visitGroupingExpr(this);
}


Grouping::~Grouping() {
    delete expression;
}


// ------------------- Unary --------------------------------------


Unary::Unary ( Token *this_operator, Expr *right) {
    this->this_operator = this_operator;
    this->right = right;
}


std::string Unary::acceptS(ExprVisitor<std::string> *visitor) { 
    return visitor->visitUnaryExpr(this);
}


Object *Unary::accpetO(ExprVisitor<Object *> *visitor) {
    return visitor->visitUnaryExpr(this);
}


Unary::~Unary() {
    delete this_operator;
    delete right;
}


// ------------------- Logical --------------------------------------


Logical::Logical (Expr *left, Token *this_operator, Expr *right) {
    this->left = left;
    this->this_operator = this_operator;
    this->right = right;
}


std::string Logical::acceptS(ExprVisitor<std::string> *visitor) {
    return visitor->visitLogicalExpr(this);
}


Object *Logical::accpetO(ExprVisitor<Object *> *visitor) {
    return visitor->visitLogicalExpr(this);
}


// ------------------- Literal --------------------------------------


Literal::Literal(Object *value) {
    this->value = value;
}


std::string Literal::acceptS(ExprVisitor<std::string> *visitor) { 
    return visitor->visitLiteralExpr(this);
}


Object *Literal::accpetO(ExprVisitor<Object *> *visitor) {
    return visitor->visitLiteralExpr(this);
}


Literal::~Literal() {
    delete value;
}


// ------------------- Literal --------------------------------------


Variable::Variable(Token *name) {
    this->name = name;
}


std::string Variable::acceptS(ExprVisitor<std::string> *visitor) {
    return visitor->visitVariableExpr(this);
}

Object *Variable::accpetO(ExprVisitor<Object *> *visitor) {
    return visitor->visitVariableExpr(this);
}

// Test program
// int main(int argc, char** argv) {
//     Expr* expression = new Binary(
//         new Unary(
//             new Token(TokenType::MINUS, "-", nullptr, 1),
//             new Literal(new Object(123))),
//         new Token(TokenType::STAR, "*", nullptr, 1),
//         new Grouping(
//             new Literal(new Object(45.67))));

//     //System.out.println(new AstPrinter().print(expression));
//     AstPrinter* ttmp = new AstPrinter();
//     std::cout << ttmp->printf(expression) << "\n";

//     delete ttmp;
//     delete expression;
//     return 0;
// }