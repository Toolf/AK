#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>

enum TokenType
{
    LPAR = '(',
    RPAR = ')',
    END_OF_CODE = '\0',
    UNKNOWN = -1,
};

struct Token
{
    TokenType tag;
    char value;
    Token(TokenType tag, char value = 0){
        this->tag = tag;
        this->value = value;
    }
};

class Lexer
{
    public:
        Lexer(std::string code);
        Token lookahead();
        Token nextToken();
    private:
        int last_index;
        std::string code;

};

#endif //LEXER_HPP
