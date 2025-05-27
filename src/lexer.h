#include <iostream>
#include <vector>
#include <string>

enum TokenType : unsigned char
{
    // Keywords
    INT, VOID, IF, ELSE, WHILE, RETURN, INPUT, OUTPUT,

    // Operators  
    PLUS, MINUS, STAR, SLASH, EQUAL, EQ, NE, LT, LE, GT, GE,

    // Delimiters
    LCURL, RCURL, LPAREN, RPAREN, LSQUARE, RSQUARE, SEMICOLON, COMMA,

    // Literals & Identifiers
    INT_ID, VAR_ID, FUNC_ID
};

class Token{

    std::string value;
    int val;
    TokenType type;
    int line;
    int column;

public:
    Token(TokenType type, std::string value, int val, int line, int column);

};

class Lexer{

    std::string *source_code;
    int position;
    std::vector<Token> tokens;
    int line;
    int column;

    void next_token();
    void skip_whitespace();
    void handle_comments();
    void add_token(TokenType);
    char peek_char();
    int read_number();
    std::string read_identifier();
    bool is_num(char);
    bool is_alpha(char);
public:
    std::vector<Token> *tokenize(const std::string& source);
};