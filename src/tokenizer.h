#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

/* A representation of all the tokens
 */
enum Token {
    // Nothing
    NONE,
    // Constants
    NUMBER, STRING,
    // Binary operators
    ADD, SUB, MUL, DIV, EQ, NEQ, LT, GT, LTE, GTE,
    // Reserved Keywords
    PRINT, IF, THEN, GOTO, INPUT, LET, GOSUB, RETURN, CLEAR, LIST, RUN, END
};

/* A representation of the token type, in which contains the type of the token,
 * as well as the value(s)
 */
struct token_t {
    Token t;
    int num;
    string str;
};

// TODO
token_t::token_t(Token tt=NONE, int n=0, string s="");

/* Get's a list of tokens from the line and returns them as a vector
 */
vector<token_t> get_tokens(string line);

#endif
