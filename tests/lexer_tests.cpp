#include "../src/lexer.h"

int main(){
    std::string source = "";
    Lexer lexer;
    while(!std::cin.eof()){
        std::string line;
        std::getline(std::cin, line);
        source += line + "\n";
    }
    std::vector<Token> tokens = lexer.tokenize(source);
    for(auto x:tokens){
        printf("\033[033mToken\033[0m : \033[036m%10s\033[0m  \"%s\" at line: %d column %d\n", token_id_map[x.type].c_str(), x.value.c_str(), x.line, x.column);
    }
}