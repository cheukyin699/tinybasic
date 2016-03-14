#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <vector>

#include "tokenizer.h"

using namespace std;

class Statement {
public:
    Token t;
};

class StrExpr {
};

class Expression: public StrExpr {
};

class String: public StrExpr {
public:
    string s;
};

class ExprList {
public:
    vector<StrExpr> exprs;
};

class Term {
};

class Variable {
public:
    char v;
};

class Factor {
public:
    Variable* v;
    int n;
    Expression* expr;
};

class VarList {
public:
    vector<Variable> vars;
};

class PrntStatement: public Statement {
public:
    ExprList* l;
};

class IfStatement: public Statement {
public:
    Expression* e1;
    Token relop;
    Expression* e2;
    Statement* stmnt;
};

class GotoStatement: public Statement {
public:
    Expression* expr;
};

class InpStatement: public Statement {
public:
    VarList* vl;
};

class LetStatement: public Statement {
public:
    Variable* v;
    Expression* expr;
};

class GSubStatement: public GotoStatement {
};

#endif
