#include "Parser.h"
#include <iostream>

Parser::Parser(std::vector<Token*>* tokens) {
    this->current = 0;
    this->tokens = tokens;
}

Parser::~Parser() { }

std::vector<Stmt *> *Parser::parse() {
    std::vector<Stmt *>* statements = new std::vector<Stmt *>();

    while(!isAtEnd()) {
        statements->push_back(declaration());
    }

    return statements;
}


Expr *Parser::expresion() {
    return assignment();
}


Expr *Parser::BinaryExpr(std::vector<TokenType> types, Expr *(Parser::*production)(void), Parser* parser) {
    Expr *expr = (parser->*production)();

    while (match(types)) {
        Token *oprt = previous();
        Expr *right = (parser->*production)();
        expr = new Binary(expr, oprt, right);
    }

    return expr;
}


Stmt *Parser::declaration() {
    try {
        if (match({TokenType::VAR})) return varDeclaration();

        return statement();
    }
    catch (ParseError exp) {
        synchronize();
        return nullptr;
    }
}


Stmt *Parser::varDeclaration() {
    Token *name = consume({TokenType::IDENTIFIER}, "Expect variable name.")->clone();

    Expr *initializer = nullptr;
    if (match({TokenType::EQUAL})) {
        initializer = expresion();
    }

    consume(TokenType::SEMICOLON, "Expect ';' after variable declaration.");
    return new Var(name, initializer);
}


Stmt *Parser::whileStatement() {
    consume(TokenType::LEFT_PAREN, "Expect '(' after 'while'.");
    Expr *condition = expresion();
    consume(TokenType::RIGHT_PAREN, "Expect ')' after condition.");
    Stmt *body = statement();

    return new While(condition, body);
}


Stmt *Parser::statement() {
    if (match({TokenType::FOR})) return forStatement();
    if (match({TokenType::IF})) return ifStatement();
    if (match({TokenType::PRINT})) return printStatement();
    if (match({TokenType::WHILE})) return whileStatement();
    if (match({TokenType::LEFT_BRACE})) return new Block(block());

    return expressionStatement();
}


Stmt *Parser::forStatement() {
    consume(TokenType::LEFT_PAREN, "Expect '(' after 'for'.");

    Stmt *initializer;
    if (match({TokenType::SEMICOLON})) {
      initializer = nullptr;
    } else if (match({TokenType::VAR})) {
      initializer = varDeclaration();
    } else {
      initializer = expressionStatement();
    }

    Expr *condition = nullptr;
    if (!check({TokenType::SEMICOLON})) {
      condition = expresion();
    }
    consume(TokenType::SEMICOLON, "Expect ';' after loop condition.");

    Expr *increment = nullptr;
    if (!check({TokenType::RIGHT_PAREN})) {
      increment = expresion();
    }
    consume(TokenType::RIGHT_PAREN, "Expect ')' after for clauses.");
    Stmt *body = statement();

    if (increment != nullptr) {
        std::vector<Stmt *> *innerStatements = new std::vector<Stmt *>();
        innerStatements->push_back(body);
        innerStatements->push_back(new Expression(increment));

        body = new Block(innerStatements);
    }

    if (condition == nullptr) condition = new Literal(new Object(true));
    body = new While(condition, body);

    if (initializer != nullptr) {
        std::vector<Stmt *> *innerStatements = new std::vector<Stmt *>();
        innerStatements->push_back(initializer);
        innerStatements->push_back(body);

        body = new Block(innerStatements);
    }

    return body;
}


Stmt *Parser::ifStatement() {
    consume(TokenType::LEFT_PAREN, "Expect '(' after 'if'.");
    Expr *condition = expresion();
    consume(TokenType::RIGHT_PAREN, "Expect ')' after if condition."); 

    Stmt *thenBranch = statement();
    Stmt *elseBranch = nullptr;
    if (match({TokenType::ELSE})) {
      elseBranch = statement();
    }

    return new If(condition, thenBranch, elseBranch);
}


Stmt *Parser::printStatement() {
    Expr *value = expresion();
    consume(TokenType::SEMICOLON, "Expect ';' after value.");

    return new Print(value);
}


Stmt *Parser::expressionStatement() {
    Expr *value = expresion();
    consume(TokenType::SEMICOLON, "Expect ';' after value.");

    return new Expression(value);
}


std::vector<Stmt *> *Parser::block() {
    std::vector<Stmt *> *statements = new std::vector<Stmt *>();

    while(!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        statements->push_back(declaration());
    }

    consume(TokenType::RIGHT_BRACE, "Expect '}' after block.");
    return statements;
}


Expr *Parser::primary() {
    if (match({TokenType::FALSE})) return new Literal(new Object(false));
    if (match({TokenType::TRUE})) return new Literal(new Object(true));
    if (match({TokenType::NIL})) return new Literal(new Object(nullptr));

    if (match({TokenType::NUMBER, TokenType::STRING})) {
        return new Literal(previous()->literal->Clone());
    }

    if (match({TokenType::IDENTIFIER})) {
        return new Variable(previous()->clone());
    }

    if (match({TokenType::LEFT_PAREN})) {
        Expr *expr = expresion();
        consume({TokenType::RIGHT_PAREN}, "Expect ')' after expression.");
        return new Grouping(expr);
    }

    throw error(peek(), "Expect expression.");
}


Expr *Parser::unary() {
    if (match({TokenType::BANG, TokenType::MINUS})) {
        Token *oprt = previous();
        Expr *right = unary();
        return new Unary(oprt, right);
    }

    return primary();
}


Expr *Parser::factor() {
    return BinaryExpr({ TokenType::SLASH, 
                        TokenType::STAR},
                        &Parser::unary, this);
}


Expr *Parser::term() {
    return BinaryExpr({ TokenType::MINUS,
                        TokenType::PLUS},
                        &Parser::factor, this);
}


Expr *Parser::comparison() {
    return BinaryExpr({ TokenType::GREATER, 
                        TokenType::GREATER_EQUAL, 
                        TokenType::LESS, 
                        TokenType::LESS_EQUAL},
                        &Parser::term, this);
}


Expr *Parser::equality() {
    return BinaryExpr({ TokenType::BANG_EQUAL, 
                        TokenType::EQUAL_EQUAL}, 
                        &Parser::comparison, this);
}


Expr *Parser::assignment() {
    //bool isVar = check(TokenType::VAR);
    Expr *expr = myOr();

    if (match({TokenType::EQUAL})) {
        Token *equals = previous();
        Expr *value = assignment();

        if (expr != nullptr && dynamic_cast<Variable *>(expr) != nullptr) { 
            Token *name = ((Variable *)expr)->name->clone();
            return new Assign(name, value);
        }

        error(equals, "Invalid assignment target.");
    }

    return expr;
}


Expr *Parser::myOr() {
    Expr *expr = myAnd();

    while (match({TokenType::OR})) {
        Token *oprt = previous();
        Expr *right = myAnd();
        expr = new Logical(expr, oprt, right);
    }

    return expr;
}


Expr *Parser::myAnd() {
    Expr *expr = equality();

    while (match({TokenType::AND})) {
        Token *oprt = previous();
        Expr *right = equality();
        expr = new Logical(expr, oprt, right);
    }

    return expr;
}


bool Parser::match(std::vector<TokenType> types) {
    for (auto it = types.begin(); it != types.end(); ++it) {
        if (check(*it)) {
            advance();
            return true;
        }
    }

    return false;
}


Token *Parser::consume(TokenType type, std::string message) {
    if (check(type)) return advance();

    throw error(peek(), message);
}


bool Parser::check(TokenType type) {
    if (isAtEnd()) return false;
    return peek()->type == type;
}


Token *Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}


bool Parser::isAtEnd() {
    return peek()->type == TokenType::EOFF;
}


Token *Parser::peek() {
    return (*tokens)[current];
}


Token *Parser::previous() {
    return (*tokens)[current - 1];
}


Parser::ParseError Parser::error(Token* token, std::string message) {
    CppLoxError::error(token, message);
    return ParseError();
}


void Parser::synchronize() {
    advance();

    while(!isAtEnd()) {
        if (previous()->type == TokenType::SEMICOLON) return;

        switch (peek()->type)
        {
        case TokenType::CLASS:
        case TokenType::FUN:
        case TokenType::VAR:
        case TokenType::FOR:
        case TokenType::IF:
        case TokenType::WHILE:
        case TokenType::PRINT:
        case TokenType::RETURN:
            return;
        }

        advance();
    }
}


