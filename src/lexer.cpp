#include "lexer.h"

std::map<TokenType , std::string> token_id_map = {
    {TokenType::INT    , "INT"},
    {TokenType::VOID   , "VOID"},
    {TokenType::IF     , "IF"},
    {TokenType::ELSE   , "ELSE"},
    {TokenType::WHILE  , "WHILE"},
    {TokenType::RETURN , "RETURN"},
    {TokenType::INPUT  , "INPUT"},
    {TokenType::OUTPUT , "OUTPUT"},
    {TokenType::PLUS   , "PLUS"},
    {TokenType::MINUS  , "MINUS"},
    {TokenType::STAR   , "STAR"},
    {TokenType::SLASH  , "SLASH"},
    {TokenType::EQUAL  , "EQUAL"},
    {TokenType::EQ     , "EQ"},
    {TokenType::NE     , "NE"},
    {TokenType::LT     , "LT"},
    {TokenType::LE     , "LE"},
    {TokenType::GT     , "GT"},
    {TokenType::GE     , "GE"},
    {TokenType::LPAREN , "LPAREN"},
    {TokenType::RPAREN , "RPAREN"},
    {TokenType::LCURL  , "LCURL"},
    {TokenType::RCURL  , "RCURL"},
    {TokenType::LSQUARE, "LSQUARE"},
    {TokenType::RSQUARE, "RSQUARE"},
    {TokenType::SEMICOLON, "SEMICOLON"},
    {TokenType::COMMA  , "COMMA"},
    {TokenType::IDENTIFIER, "IDNETIFIER"},
    {TokenType::INT_ID , "INT_ID"},
    {TokenType::VAR_ID , "VAR_ID"},
    {TokenType::FUNC_ID, "FUNC_ID"},
    {TokenType::ERROR , "ERROR"},
};

Token::Token(TokenType type, std::string value, int line, int column){
    this->type = type;
    this->value = value;
    this->line = line;
    this->column = column;
}

char Lexer::peek_char(){ // returns the present scanning character of source
    if(position < source_code.size()){
        return source_code.at(position);
    }
    else{
        return '\0';
    }
}

void Lexer::skip_whitespace(){ // skips positions until a non white space character is found;
    char c = peek_char();
    while(c && (c == ' ' || c == '\n' || c == '\t' || c == '\r')){
        if(c == '\n'){
            line++;
            column = 0;
        }
        column++;
        position++;
        c = peek_char();
    }
}

bool Lexer::is_num(char c){ // returns true if character is a digit
    return ('0' <= c && c <= '9');
}

bool Lexer::is_alpha(char c){ // returns true if the character is alphabet
    return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') );
}

std::string Lexer::read_number(){ // reads in an integer
    std::string number = "";
    char c = peek_char();
    while(c && is_num(c)){
        number += c;
        position++;
        column++;
        c = peek_char();
    }
    return number;
}

std::string Lexer::read_identifier(){ // reads in name of variable
    std::string identifier = "";
    char c = peek_char();
    while (c && (is_num(c) || is_alpha(c) || c == '_')){
        identifier += c;
        position++;
        column++;
        c = peek_char();
    }
    return identifier;
}

void Lexer::add_token(TokenType type, std::string value){
    tokens.push_back(Token(type, value, line, column - (type == ERROR ? 0 : value.length())));
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
            add_token(LE, "<=");
        }
        else{
            add_token(LT, "<");
        }
        break;

    case '>':
        position++;
        column++;
        if(peek_char() == '='){
            position++;
            column++;
            add_token(GE, ">=");
        }
        else{
            add_token(GT, ">");
        }
        break;

    case '=':
        position++;
        column++;
        if(peek_char() == '='){
            position++;
            column++;
            add_token(EQ, "==");
        }
        else{
            add_token(EQUAL, "=");
        }
        break;
        
    case '!':
        position++;
        column++;
        if(peek_char() == '='){
            position++;
            column++;
            add_token(NE, "!=");
        }
        else{
            add_token(ERROR, "Unexpected character: !");
        }
        break;
    
        
    case '+':
        position++;
        column++;
        add_token(PLUS, "+");
        break;
    
    case '-':
        position++;
        column++;
        add_token(MINUS, "-");
        break;
    
    case '*':
        position++;
        column++;
        add_token(STAR, "*");
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
            add_token(SLASH, "/");
        }
        break;
        
    case '{':
        position++;
        column++;
        add_token(LCURL, "{");
        break;
        
    case '}':
        position++;
        column++;
        add_token(RCURL, "}");
        break;
    
    case '(':
        position++;
        column++;
        add_token(LPAREN, "(");
        break;

    case ')':
        position++;
        column++;
        add_token(RPAREN, ")");
        break;
    
    case '[':
        position++;
        column++;
        add_token(LSQUARE, "[");
        break;
    
    case ']':
        position++;
        column++;
        add_token(RSQUARE, "]");
        break;
    
    case ';':
        position++;
        column++;
        add_token(SEMICOLON, ";");
        break;
    
    case ',':
        position++;
        column++;
        add_token(COMMA, ",");
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
            add_token(INT, s);
        }
        else if(s == "void"){
            add_token(VOID, s);
        }
        else if(s == "if"){
            add_token(IF, s);
        }
        else if(s == "else"){
            add_token(ELSE, s);
        }
        else if(s == "while"){
            add_token(WHILE, s);
        }
        else if(s == "return"){
            add_token(RETURN, s);
        }
        else if(s == "input"){
            add_token(INPUT, s);
        }
        else if(s == "output"){
            add_token(OUTPUT, s);
        }
        else{// in other case tokenize the string as identifier which will be segredated to var or func by parser
            add_token(IDENTIFIER, s);
        }
        break;
        
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        s = read_number();
        add_token(INT_ID, s);
        break;

    case '\0':
        return;
        break;

    default:
        add_token(ERROR, "Unexpected character");
        column++;
        position++;
        break;
    }
}

void Lexer::handle_comments(){
    char c;
    while(c = peek_char() && c != '\n'){
        position++;
        column++;
    }
    if(peek_char()){
        line++;
        column = 1;
        position++;
    }
}

std::vector<Token> Lexer::tokenize(const std::string & source){
    source_code = source;
    line = 1;
    column = 1;
    position = 0;
    tokens.clear();
    
    while(peek_char()){
        next_token();
    }
    return tokens;
}