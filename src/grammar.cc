#include <algorithm>

#include "grammar.h"


template <typename T>
static void vector_destructor(vector<T>& v) {
    for (auto&& i: v) {
        delete i;
        i = nullptr;
    }
    v.clear();
}


Term::~Term() {
    vector_destructor(fs);
}

Expression::~Expression() {
    vector_destructor(ts);
}

ExprList::~ExprList() {
    vector_destructor(exprs);
}

Factor::~Factor() {
    delete v;
    v = nullptr;
    delete expr;
    expr = nullptr;
}

VarList::~VarList() {
    vector_destructor(vars);
}

PrntStatement::~PrntStatement() {
    delete l;
    l = nullptr;
}

IfStatement::~IfStatement() {
    delete e1;
    e1 = nullptr;
    delete e2;
    e2 = nullptr;
    delete stmnt;
    stmnt = nullptr;
}

GotoStatement::~GotoStatement() {
    delete expr;
    expr = nullptr;
}

InpStatement::~InpStatement() {
    delete vl;
    vl = nullptr;
}

LetStatement::~LetStatement() {
    delete v;
    v = nullptr;
    delete expr;
    expr = nullptr;
}
