
#ifndef _CPPLOX_PARSER_
#define _CPPLOX_PARSER_


#include "../Representation/Token.h"
#include "../Representation/Expressions.h"
#include "../Representation/Stmt.h"
#include "../Errors/CppLoxError.h"
#include <vector>
#include <iostream>


class Parser {
public:
    class ParseError : public std::exception {
        public:

        const char *what() const throw() {
            return "What the fuck!!!!";
        }
    };

public:
    std::vector<Token *> *tokens;
    int current;

    Parser(std::vector<Token *> *tokens);
    ~Parser();
    std::vector<Stmt *> *parse();
    Expr *expresion();
    Expr *BinaryExpr(std::vector<TokenType> types, Expr *(Parser::*production)(void), Parser* parser);
    Stmt *declaration();
    Stmt *varDeclaration();
    Stmt *whileStatement();
    Stmt *statement();
    Stmt *forStatement();
    Stmt *ifStatement();
    Stmt *printStatement();
    Stmt *expressionStatement();
    std::vector<Stmt *> *block();
    Expr *primary();
    Expr *unary();
    Expr *factor();
    Expr *term();
    Expr *comparison();
    Expr *equality();
    Expr *assignment();
    Expr *myOr();
    Expr *myAnd();
    bool match(std::vector<TokenType> types);
    Token *consume(TokenType type, std::string message);
    bool check(TokenType type);
    Token *advance();
    bool isAtEnd();
    Token *peek();
    Token *previous();
    ParseError error(Token* token, std::string message);
    void synchronize();
};


#endif