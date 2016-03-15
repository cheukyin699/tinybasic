#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <map>
#include <string>
#include <stack>

#include "grammar.h"
#include "parser.h"

using namespace std;

class Interpreter {
private:
    int curr_line;
    vector<Statement*> stmnts;
    map<char, int> vars;
    stack<int> calls;

    void xStatement(Statement*);
    void xPrnt(PrntStatement*);
    void xIf(IfStatement*);
    void xGoto(GotoStatement*);
    void xInp(InpStatement*);
    void xLet(LetStatement*);
    void xGSub(GSubStatement*);

    int evalExp(Expression*);
    int evalTerm(Term*);
    int evalFactor(Factor*);
    string evalString(String*);

public:
    Interpreter();
    ~Interpreter();

    void set(vector<Statement*>);

    void run();
};

#endif
