#ifndef _CPPLOX_TOKEN_
#define _CPPLOX_TOKEN_


#include <iostream>


class Object;


enum class TokenType {
    // Single-character tokens.
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // One or two character tokens.
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literals.
    IDENTIFIER, STRING, NUMBER,

    // Keywords.
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    EOFF   
};


class Token {
public:
    TokenType type;
    std::string lexem;
    Object* literal;
    int line;

public:
    Token() {}
    Token(TokenType type, std::string lexem, Object* literal, int line);
    // ~Token();

    Token *clone();

    friend std::ostream& operator<<(std::ostream& out, Token &toke);
};


#endif // _CPPLOX_TOKEN_
