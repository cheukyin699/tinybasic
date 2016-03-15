#include <algorithm>

#include "grammar.h"
#include "utilities.h"


Term::~Term() {
    vector_destructor(fs);
}

Expression::~Expression() {
    vector_destructor(ts);
}

ExprList::~ExprList() {
    // Cannot use default destructor because of different classes
    for (auto&& i: exprs) {
        if (i->str)
            delete static_cast<String*>(i);
        else
            delete static_cast<Expression*>(i);

        i = nullptr;
    }
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
