#include "iostream"
#include "Lexer.h"

int main(){
    std::cout << "Start work" << std::endl;
    std::string code = "((a))()";
    Lexer l = Lexer(code);
    while(1){
        Token t = l.nextToken();

        std::cout << char(t.tag) << " " << char(t.value) << std::endl;
        if (t.tag == END_OF_CODE){
            break;
        }
    }

    std::cout << "Finish work" << std::endl;
    return 0;
}