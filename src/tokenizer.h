#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

/* A representation of all the tokens
 */
enum Token {
    // Nothing
    NONE,
    // Constants
    NUMBER, STRING,
    // Variable(s)
    VARIABLE,
    // Binary operators
    ADD, SUB, MUL, DIV, EQ, NEQ, LT, GT, LTE, GTE, COMMA,
    // Reserved Keywords
    PRINT, IF, THEN, GOTO, INPUT, LET, GOSUB, RETURN, CLEAR, LIST, RUN, END
};

/* A representation of the token type, in which contains the type of the token,
 * as well as the value(s)
 */
struct token_t {
    Token t;
    int num;        // The type of variable is stored here [0,25]
    string str;
};

token_t create_token(Token tt=NONE, int n=0, string s="");

/* Get's a list of tokens from the line and returns them as a vector
 */
vector<token_t> get_tokens(string line);

/* Overrides << operator for token_t
 */
ostream& operator<<(ostream& os, token_t& t);



/* This maps the corresponding strings to the corresponding Tokens
 */
const map<string, Token> token_map {
    {"+", ADD}, {"-", SUB},  {"*", MUL}, {"/", DIV},
    {"=", EQ}, {"<>", NEQ}, {"<", LT}, {">", GT}, {"<=", LTE}, {">=", GTE},
    {"PRINT", PRINT}, {"IF", IF}, {"THEN", THEN}, {"GOTO", GOTO}, {"INPUT", INPUT},
    {"LET", LET}, {"GOSUB", GOSUB}, {"RETURN", RETURN}, {"CLEAR", CLEAR},
    {"LIST", LIST}, {"RUN", RUN}, {"END", END}, {",", COMMA}
};

#endif
