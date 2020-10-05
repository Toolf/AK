#include "Lexer.h"
#include <iostream>

Lexer::Lexer(std::string code)
{  
    this->code = code;
    this->last_index = -1;
};
Token Lexer::lookahead()
{
    int last_index = this->last_index;
    Token res = this->nextToken();
    this->last_index = last_index;
    return res;
};
Token Lexer::nextToken()
{
    last_index+=1;
    if (code.length() == last_index){
        return Token(END_OF_CODE);
    }
    if (code[last_index] == LPAR){
        return Token(LPAR);
    } else if (code[last_index] == RPAR){
        return Token(RPAR);
    } else {
        return Token(UNKNOWN, code[last_index]);
    }
};