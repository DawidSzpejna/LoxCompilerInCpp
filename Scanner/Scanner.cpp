#include "Scanner.h"
#include "../Errors/CppLoxError.h"


std::map<std::string, TokenType> Scanner::keywords = {
    {"and",    TokenType::AND},
    {"class",  TokenType::CLASS},
    {"else",   TokenType::ELSE},
    {"false",  TokenType::FALSE},
    {"for",    TokenType::FOR},
    {"fun",    TokenType::FUN},
    {"if",     TokenType::IF},
    {"nil",    TokenType::NIL},
    {"or",     TokenType::OR},
    {"print",  TokenType::PRINT},
    {"return", TokenType::RETURN},
    {"super",  TokenType::SUPER},
    {"this",   TokenType::THIS},
    {"true",   TokenType::TRUE},
    {"var",    TokenType::VAR},
    {"while",  TokenType::WHILE}
};



Scanner::Scanner(std::string source, std::vector<Token *> *tokens)
{
    this->tokens = tokens;
    this->source = source;
}


Scanner::~Scanner() { }


std::vector<Token *> *Scanner::scanTokens()
{
    while(!isAtEnd()) {
        start = current;
        scanToken();
    }

    tokens->push_back(new Token(TokenType::EOFF, "", nullptr, line));
    return tokens;
}


void Scanner::scanToken()
{
    char c = advance();
    switch (c)
    {
    case '(': addToken(TokenType::LEFT_PAREN); break;
    case ')': addToken(TokenType::RIGHT_PAREN); break;
    case '{': addToken(TokenType::LEFT_BRACE); break;
    case '}': addToken(TokenType::RIGHT_BRACE); break;
    case ',': addToken(TokenType::COMMA); break;
    case '.': addToken(TokenType::DOT); break;
    case '-': addToken(TokenType::MINUS); break;
    case '+': addToken(TokenType::PLUS); break;
    case ';': addToken(TokenType::SEMICOLON); break;
    case '*': addToken(TokenType::STAR); break; 

    case '!':
        addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
        break;
    case '=':
        addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
        break;
    case '<':
        addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
        break;
    case '>':
        addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        break;

    case '/':
        if (match('/')) {
            while (peek() != '\n' && !isAtEnd()) advance();
        }
        else {
            addToken(TokenType::SLASH);
        }
        break;
    
    case ' ':
    case '\r':
    case '\t':
        // Ignore whitespace.
        break;
    
    case '\n':
        line++;
        break;

    case '"':
        haveString();
        break;

    default:
        if (isDigit(c)) {
            number();
        }
        else if (isAlpha(c)) {
            identifier();
        }
        else {
            CppLoxError::error(line, "Unexpected character.");
        }
        break;
    }
}


void Scanner::identifier() {
    while (isAlphaNumeric(peek())) advance();

    std::string text = source.substr(start, current - start);
    
    TokenType type = TokenType::IDENTIFIER;
    if (Scanner::keywords.count(text)) {
        type = Scanner::keywords[text];
    }

    addToken(type);
}


void Scanner::number() {
    while (isdigit(peek())) advance();

    // Look for a fractional part.
    if (peek() == '.' && isDigit(peekNext())) {
        // Consume the "."
        advance();

        while (isDigit(peek())) advance();
    }

    char* nptr = nullptr;
    float number = strtof(source.substr(start, current - start).c_str(), &nptr);


    if (*nptr != '\0') {
        CppLoxError::error(line, "There is not a number.");
    }

    addToken(TokenType::NUMBER, new Object(number));
}


void Scanner::haveString()
{
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }

    if (isAtEnd()) {
        CppLoxError::error(line, "Unterminated string.");
        return;
    }

    // The closing ".
    advance();

    std::string value = source.substr(start + 1, current - start - 2);
    addToken(TokenType::STRING, new Object(value));
}


bool Scanner::match(char expected)
{
    if (isAtEnd()) return false;
    if (source[current] != expected) return false;

    current++;
    return true;
}


char Scanner::peek()
{
    if (isAtEnd()) return '\0';
    return source[current];
}


char Scanner::peekNext()
{
    if (current + 1 >= source.length()) return '\0';
    return source[current + 1];
}


bool Scanner::isAlpha(char c)
{
    return  (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c == '_');
}


bool Scanner::isAlphaNumeric(char c)
{
    return isAlpha(c) || isDigit(c);
}


bool Scanner::isDigit(char c)
{
    return c >= '0' && c <= '9';
}


bool Scanner::isAtEnd()
{
    return current >= source.length();
}


char Scanner::advance()
{
    return source[current++];
}


void Scanner::addToken(TokenType type)
{
    addToken(type, nullptr);
}


void Scanner::addToken(TokenType type, Object *literal)
{
    std::string text = source.substr(start, current - start);

    tokens->push_back(new Token(type, text, literal, line));
}
