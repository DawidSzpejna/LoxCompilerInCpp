#include "Token.h"


Token::Token(TokenType type, std::string lexem, Object* literal, int line) {
    this->type = type;
    this->lexem = lexem;
    this->literal = literal;
    this->line = line;
}


Token::~Token()
{
    //delete literal;
}


Token *Token::clone() {
    Token *tmp = new Token( this->type,
                            this->lexem, 
                            this->literal == nullptr ? nullptr :  this->literal->Clone(), 
                            this->line
                           );

    return tmp;
}


std::ostream& operator<<(std::ostream& out, Token &toke) {
    std::string type = "UNKNOWN";

    switch (toke.type)
    {
    case TokenType::LEFT_PAREN: type = "LEFT_PAREN"; break;
    case TokenType::RIGHT_PAREN: type = "RIGHT_PAREN"; break;
    case TokenType::LEFT_BRACE: type = "LEFT_BRACE"; break;
    case TokenType::RIGHT_BRACE: type = "RIGHT_BRACE"; break;
    case TokenType::COMMA: type = "COMMA"; break;
    case TokenType::DOT: type = "DOT"; break;
    case TokenType::MINUS: type = "MINUS"; break;
    case TokenType::PLUS: type = "PLUS"; break;
    case TokenType::SEMICOLON: type = "SEMICOLON"; break;
    case TokenType::SLASH: type = "SLASH"; break;
    case TokenType::STAR: type = "STAR"; break;
    case TokenType::BANG: type = "BANG"; break;
    case TokenType::BANG_EQUAL: type = "BANG_EQUAL"; break;
    case TokenType::EQUAL: type = "EQUAL"; break;
    case TokenType::EQUAL_EQUAL: type = "EQUAL_EQUAL"; break;
    case TokenType::GREATER: type = "GREATER"; break;
    case TokenType::GREATER_EQUAL: type = "GREATER_EQUAL"; break;
    case TokenType::LESS: type = "LESS"; break;
    case TokenType::LESS_EQUAL: type = "LESS_EQUAL"; break;
    case TokenType::IDENTIFIER: type = "IDENTIFIER"; break;
    case TokenType::STRING: type = "STRING"; break;
    case TokenType::NUMBER: type = "NUMBER"; break;
    case TokenType::AND: type = "AND"; break;
    case TokenType::CLASS: type = "CLASS"; break;
    case TokenType::ELSE: type = "ELSE"; break;
    case TokenType::FALSE: type = "FALSE"; break;
    case TokenType::FUN: type = "FUN"; break;
    case TokenType::FOR: type = "FOR"; break;
    case TokenType::IF: type = "IF"; break;
    case TokenType::NIL: type = "NIL"; break;
    case TokenType::OR: type = "OR"; break;
    case TokenType::PRINT: type = "PRINT"; break;
    case TokenType::RETURN: type = "RETURN"; break;
    case TokenType::SUPER: type = "SUPER"; break;
    case TokenType::THIS: type = "THIS"; break;
    case TokenType::TRUE: type = "TRUE"; break;
    case TokenType::VAR: type = "VAR"; break;
    case TokenType::WHILE: type = "WHILE"; break;
    case TokenType::EOFF: type = "EOFF"; break;
    }

    return out << type << " " << toke.lexem << " : " << (toke.literal == nullptr ? "" : toke.literal->toString());
}
