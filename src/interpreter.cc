#include <cassert>

#include "grammar.h"
#include "interpreter.h"
#include "utilities.h"

Interpreter::Interpreter() {
}

Interpreter::~Interpreter() {
    vector_destructor(stmnts);
}

void Interpreter::set(vector<Statement*> ss) {
    stmnts = ss;
}

void Interpreter::run() {
    curr_line = 0;
    xStatement(stmnts.at(0));
}



void Interpreter::xStatement(Statement* s) {
    switch (s->t) {
        case PRINT:
            xPrnt(static_cast<PrntStatement*>(s));
            break;
        case IF:
            xIf(static_cast<IfStatement*>(s));
            break;
        case GOTO:
            xGoto(static_cast<GotoStatement*>(s));
            break;
        case INPUT:
            xInp(static_cast<InpStatement*>(s));
            break;
        case LET:
            xLet(static_cast<LetStatement*>(s));
            break;
        case GOSUB:
            xGSub(static_cast<GSubStatement*>(s));
            break;
        case RETURN:
            if (calls.empty())
                throw runtime_error("cannot return: 0 size call stack");
            curr_line = calls.top();
            calls.pop();
            break;
        case END:
            // Halts execution
            return;
        default:
            throw runtime_error("invalid statement");
    }

    // Next line, if any
    if ((unsigned long) curr_line >= stmnts.size()-1)
        return;
    else
        xStatement(stmnts.at(++curr_line));
}

void Interpreter::xPrnt(PrntStatement* s) {
    for (auto e: s->l->exprs) {
        if (e->str) {
            cout << evalString(static_cast<String*>(e));
        }
        else {
            cout << evalExp(static_cast<Expression*>(e));
        }
    }

    cout << endl;
}

void Interpreter::xIf(IfStatement* s) {
    int e1 = evalExp(s->e1),
        e2 = evalExp(s->e2);
    bool exec_stmnt = false;

    switch (s->relop) {
    case LT:
        exec_stmnt = e1 < e2;
        break;
    case LTE:
        exec_stmnt = e1 <= e2;
        break;
    case GT:
        exec_stmnt = e1 > e2;
        break;
    case GTE:
        exec_stmnt = e1 >= e2;
        break;
    case EQ:
        exec_stmnt = e1 == e2;
        break;
    case NEQ:
        exec_stmnt = e1 != e2;
        break;
    default:
        throw runtime_error("invalid binary operation");
    }

    if (exec_stmnt)
        xStatement(s->stmnt);
}

void Interpreter::xGoto(GotoStatement* s) {
    curr_line = evalExp(s->expr);
    xStatement(stmnts.at(curr_line));
}

void Interpreter::xInp(InpStatement* s) {
    int tmp = 0;
    for (auto v: s->vl->vars) {
        cin >> tmp;
        vars[v->v] = tmp;
    }
}

void Interpreter::xLet(LetStatement* s) {
    int val = evalExp(s->expr);
    vars[s->v->v] = val;
}

void Interpreter::xGSub(GSubStatement* s) {
    int line = evalExp(s->expr);
    calls.push(curr_line);

    curr_line = line;
    xStatement(stmnts.at(line));
}

int Interpreter::evalExp(Expression* e) {
    // Use accumulator and loop
    int acc = 0;

    for (unsigned long i = 0; i < e->ts.size(); i++) {
        if (e->tks.at(i) == ADD) {
            acc += evalTerm(e->ts.at(i));
        }
        else if (e->tks.at(i) == SUB) {
            acc -= evalTerm(e->ts.at(i));
        }
    }

    return acc;
}

int Interpreter::evalTerm(Term* t) {
    // Use accumulator and loop
    int acc = evalFactor(t->fs.at(0));

    for (unsigned long i = 0; i < t->tks.size(); i++) {
        if (t->tks.at(i) == MUL) {
            acc *= evalFactor(t->fs.at(i+1));
        }
        else if (t->tks.at(i) == DIV) {
            acc /= evalFactor(t->fs.at(i+1));
        }
    }

    return acc;
}

int Interpreter::evalFactor(Factor* f) {
    switch (f->t) {
    case Var:
        return vars.at(f->v->v);
    case Num:
        return f->n;
    case Exp:
        return evalExp(f->expr);
    default:
        throw runtime_error("invalid factor");
    }
}

string Interpreter::evalString(String* s) {
    return s->s;
}
