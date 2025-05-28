#include <iostream>
#include <vector>
#include <string>
#include <map>


enum TokenType : unsigned char
{
    // Keywords
    INT, VOID, IF, ELSE, WHILE, RETURN, INPUT, OUTPUT,
    
    // Operators  
    PLUS, MINUS, STAR, SLASH, EQUAL, EQ, NE, LT, LE, GT, GE,
    
    // Delimiters
    LCURL, RCURL, LPAREN, RPAREN, LSQUARE, RSQUARE, SEMICOLON, COMMA,
    
    // Literals & Identifiers
    IDENTIFIER, INT_ID, VAR_ID, FUNC_ID,
    
    // Errors tokens
    ERROR
};

extern std::map<TokenType, std::string> token_id_map;

struct Token{

    std::string value;
    TokenType type;
    int line;
    int column;

    Token(TokenType type, std::string value, int line, int column);

};

class Lexer{

    std::string source_code;
    std::vector<Token> tokens;
    int position;
    int line;
    int column;

    void next_token();
    void skip_whitespace();
    void handle_comments();
    void add_token(TokenType, std::string);
    char peek_char();
    std::string read_number();
    std::string read_identifier();
    bool is_num(char);
    bool is_alpha(char);
public:
    std::vector<Token> tokenize(const std::string& source);
};