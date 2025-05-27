#include "lexer.h"

Token::Token(TokenType type, std::string value, int val, int line, int column){
    this->type = type;
    this->value = value;
    this->val = val;
    this->line = line;
    this->column = column;
}

void Lexer::skip_whitespace(){ // skips positions until a non white space character is found;
    while(peek_char() && peek_char() == ' ' || peek_char() == '\n' || peek_char() == '\t'){
        if(peek_char() == '\n'){
            line++;
            column = 0;
        }
        column++;
        position++;
    }
}

char Lexer::peek_char(){ // returns the present scanning character of source
    if(position < source_code->size()){
        return source_code->at(position);
    }
    else{
        return '\0';
    }
}

bool Lexer::is_num(char c){ // returns true if character is a digit
    return ('0' <= c && c <= '9');
}

bool Lexer::is_alpha(char c){ // returns true if the character is alphabet
    return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') );
}

int Lexer::read_number(){ // reads in an integer
    int num = 0;
    while(peek_char() && peek_char() <= '9' && peek_char() >= '0'){
        num *= 10;
        num += peek_char() - '0';
        position++;
        column++;
    }
    return num;
}

std::string Lexer::read_identifier(){ // reads in name of variable
    std::string identifier = "";
    while (peek_char() && (is_num(peek_char()) || is_alpha(peek_char())) || peek_char() == '_')
    {
        identifier += peek_char();
        position++;
        column++;
    }
    return identifier;
}

void Lexer::add_token(TokenType type){
    tokens.push_back(Token(type, "", 0, line, column));
}

void Lexer::next_token(){
    skip_whitespace();
    std::string s;
    switch (peek_char())
    {
    case '<':
        position++;
        column++;
        if(peek_char() == '='){
            position++;
            column++;
            add_token(LE);
        }
        else{
            add_token(LT);
        }
        break;

    case '>':
        position++;
        column++;
        if(peek_char() == '='){
            position++;
            column++;
            add_token(GE);
        }
        else{
            add_token(GT);
        }
        break;

    case '=':
        position++;
        column++;
        if(peek_char() == '='){
            position++;
            column++;
            add_token(EQ);
        }
        else{
            add_token(EQUAL);
        }
        break;
        
    case '+':
        position++;
        column++;
        add_token(PLUS);
        break;
    
    case '-':
        position++;
        column++;
        add_token(MINUS);
        break;
    
    case '*':
        position++;
        column++;
        add_token(STAR);
        break;
        
    case '/':
        position++;
        column++;
        if(peek_char() == '/'){
            position++;
            column++;
            handle_comments();
        }
        else{
            add_token(SLASH);
        }
        break;
        
    case '{':
        position++;
        column++;
        add_token(LCURL);
        break;
        
    case '}':
        position++;
        column++;
        add_token(RCURL);
        break;
    
    case '(':
        position++;
        column++;
        add_token(LPAREN);
        break;
    
    case ')':
        position++;
        column++;
        add_token(RPAREN);
        break;
    
    case '[':
        position++;
        column++;
        add_token(LSQUARE);
        break;
    
    case ']':
        position++;
        column++;
        add_token(RSQUARE);
        break;
    
    case ';':
        position++;
        column++;
        add_token(SEMICOLON);
        break;
    
    case ',':
        position++;
        column++;
        add_token(COMMA);
        break;
    
    // lowercase letter
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
    case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
    case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
    case 'v': case 'w': case 'x': case 'y': case 'z':
    // uppercase letter
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
    case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
    case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
    case 'V': case 'W': case 'X': case 'Y': case 'Z':
    // under_score
    case '_':
        s = read_identifier();
        if(s == "int"){
            add_token(INT);
        }
        else if(s == "void"){
            add_token(VOID);
        }
        else if(s == "if"){
            add_token(IF);
        }
        else if(s == "else"){
            add_token(ELSE);
        }
        else if(s == "while"){
            add_token(WHILE);
        }
        else if(s == "return"){
            add_token(RETURN);
        }
        else if(s == "input"){
            add_token(INPUT);
        }
        else if(s == "output"){
            add_token(OUTPUT);
        }
        else{
            if(peek_char() == '('){
                tokens.push_back(Token(FUNC_ID, s, 0, line, column));
            }
            else{
                tokens.push_back(Token(VAR_ID, s, 0, line, column));
            }
        }
        break;
        
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        int val = read_number();
        tokens.push_back(Token(INT_ID, "", val, line, column));
        break;

    default:
        break;
    }
}