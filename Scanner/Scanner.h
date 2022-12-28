#ifndef _CPPLOX_SCANNER_
#define _CPPLOX_SCANNER_


#include <iostream>
#include <vector>
#include <map>


class Token;
class Object;
enum class TokenType;


class Scanner {
public:
    static std::map<std::string, TokenType> keywords;

    std::vector<Token *> *tokens;
    std::string source;
    
    int start = 0;
    int current = 0;
    int line = 1;
public:
    Scanner(std::string source, std::vector<Token *> *tokens);
    ~Scanner();

    std::vector<Token *> *scanTokens();
    void scanToken();
    void identifier();
    void number();
    void haveString();
    bool match(char expected);
    char peek();
    char peekNext();
    bool isAlpha(char c);
    bool isAlphaNumeric(char c);
    bool isDigit(char c);

    bool isAtEnd();
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, Object *literal);
};

#endif // _CPPLOX_SCANNER_
