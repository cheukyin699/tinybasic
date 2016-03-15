#include "parser.h"

Parser::Parser(string l) {
    tks = get_tokens(l);
    it = tks.begin();
    root = nullptr;
}

Parser::~Parser() {
    delete root;
    root = nullptr;
}

void Parser::getNextToken() {
    it++;
}

inline void Parser::assertSanity(string msg) {
    if (it == tks.end())
        throw runtime_error(msg);
}

void Parser::generateTree() {
    root = getStatement();

    if (it != tks.end())
        throw runtime_error("could not reach end of statement - did not consume everything");
}

Statement* Parser::getStatement() {
    token_t stmnt_head = *it;
    getNextToken();

    switch (stmnt_head.t) {
        case PRINT:
        {
            // Consumes an expression/string and an expression/string list
            // Only shows expression because the string could be found from it
            PrntStatement* s = new PrntStatement(getExprList());
            return s;
        }
        case IF:
        {
            IfStatement* s = new IfStatement();
            s->e1 = getExpression();
            s->relop = getRelop();
            s->e2 = getExpression();
            if ((it++)->t != THEN)
                throw runtime_error("expected THEN after second expression");
            s->stmnt = getStatement();
            return s;
        }
        case GOTO:
        {
            GotoStatement* s = new GotoStatement();
            s->expr = getExpression();
            return s;
        }
        case INPUT:
        {
            InpStatement* s = new InpStatement();
            s->vl = getVarList();
            return s;
        }
        case LET:
        {
            LetStatement* s = new LetStatement();
            s->v = getVar();
            if ((it++)->t != EQ)
                throw runtime_error("expected '=' after variable");
            s->expr = getExpression();
            return s;
        }
        case GOSUB:
        {
            GSubStatement* s = new GSubStatement();
            s->expr = getExpression();
            return s;
        }
        case RETURN:
        case CLEAR:
        case LIST:
        case RUN:
        case END:
        {
            Statement* s = new Statement(stmnt_head.t);
            return s;
        }
        default:
            throw runtime_error("expected a statement");
    }
}

ExprList* Parser::getExprList() {
    ExprList* ret = new ExprList();

    assertSanity("expected an expression/string");

    if (it->t == STRING) {
        String* s = new String(it->str);
        ret->exprs.push_back(s);

        getNextToken();
    }
    else {
        ret->exprs.push_back(getExpression());
    }

    while (it != tks.end() && it->t == COMMA) {
        getNextToken();

        // Sanity checking - if the next token is the end of the line
        if (it == tks.end() || it->t == COMMA)
            throw runtime_error("expected an expression/string after comma");

        if (it->t == STRING) {
            String* s = new String(it->str);
            ret->exprs.push_back(s);

            getNextToken();
        }
        else {
            ret->exprs.push_back(getExpression());
        }
    }

    return ret;
}

Expression* Parser::getExpression() {
    Expression* ret = new Expression();

    assertSanity("expected a term");

    // Check if the first token is a binop or not, and add the correct token to
    // the first slot.
    if (it->t == ADD || it->t == SUB) {
        ret->tks.push_back(it->t);
        getNextToken();
    }
    else {
        ret->tks.push_back(NONE);
    }

    // Check for the first term (must be present)
    ret->ts.push_back(getTerm());

    // The next n terms (and tokens) are all optional
    while (it != tks.end() && (it->t == ADD || it->t == SUB)) {
        // Insert
        ret->tks.push_back(it->t);
        // Consume
        getNextToken();
        // Find term (must be present)
        ret->ts.push_back(getTerm());
    }

    return ret;
}

Term* Parser::getTerm() {
    Term* ret = new Term();

    // Grabs the first factor available
    ret->fs.push_back(getFactor());

    // The next n factors (and tokens) are all optional
    while (it != tks.end() && (it->t == MUL || it->t == DIV)) {
        // Insert
        ret->tks.push_back(it->t);
        // Consume
        getNextToken();
        // Find factor (must be present)
        ret->fs.push_back(getFactor());
    }

    return ret;
}

Factor* Parser::getFactor() {
    assertSanity("expected a factor");

    Factor* ret = new Factor();

    switch (it->t) {
    case VARIABLE:
        ret->t = FType::Var;
        ret->v = getVar();
        break;
    case NUMBER:
        ret->t = FType::Num;
        ret->n = it->num;
        // Consume number
        getNextToken();
        break;
    default:
        // Let's say that this is an expression
        ret->t = FType::Exp;
        ret->expr = getExpression();
        break;
    }

    return ret;
}

VarList* Parser::getVarList() {
    VarList* ret = new VarList();

    ret->vars.push_back(getVar());

    while (it != tks.end() && it->t == COMMA) {
        getNextToken();

        // Sanity checking
        if (it == tks.end() || it->t == COMMA)
            throw runtime_error("expected a variable after the comma");

        ret->vars.push_back(getVar());
    }

    return ret;
}

Variable* Parser::getVar() {
    assertSanity("expected a variable");

    Variable* ret = new Variable();

    if (isalpha(it->str[0])) {
        ret->v = it->str[0];
        getNextToken();
    }
    else {
        throw runtime_error("expected a variable");
    }

    return ret;
}

Token Parser::getRelop() {
    assertSanity("expected a binary operator");

    Token ret;

    switch (it->t) {
        case EQ:
        case NEQ:
        case LT:
        case LTE:
        case GT:
        case GTE:
            ret = it->t;
            // Consume
            getNextToken();
            break;
        default:
            throw runtime_error("expected a binary operator");
    }

    return ret;
}
