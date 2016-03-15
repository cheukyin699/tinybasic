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

// The longest keyword length
const unsigned Longest_KW = 6;

/* A representation of the token type, in which contains the type of the token,
 * as well as the value(s)
 */
struct token_t {
    Token t;
    int num;        // The type of variable is stored here [0,25]
    string str;
    token_t(Token t=NONE, int num=0, string str=""): t(t), num(num), str(str) {}
};

typedef vector<token_t> v_tokens;

/* Creates a new token with the defaults from one that has just been initialized
 */
void reset_token(token_t&);

/* Get's a list of tokens from the line and returns them as a vector
 */
v_tokens get_tokens(string line);

/* Checks to see if the given string is a token. If it is, it returns that
 * token. If it isn't, it gives a token with NONE as the type. It returns a
 * the length of the token, or 0 if the whole length is used.
 */
unsigned is_token(string, token_t&);

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
