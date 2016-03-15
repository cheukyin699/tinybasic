#ifndef PARSER_H
#define PARSER_H

#include <string>

#include "tokenizer.h"
#include "grammar.h"

class Parser {
private:
    v_tokens tks;
    v_tokens::iterator it;
    Statement* root;

    void getNextToken();
    inline void assertSanity(string);

    Statement*      getStatement();
    Expression*     getExpression();
    ExprList*       getExprList();
    Term*           getTerm();
    Factor*         getFactor();
    VarList*        getVarList();
    Variable*       getVar();
    Token           getRelop();

public:
    Parser(string);
    ~Parser();

    void generateTree();
};

#endif
