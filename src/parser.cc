#include "parser.h"

Parser::Parser(string l) {
    tks = get_tokens(l);
    it = tks.begin();
}

Parser::~Parser() {
}

token_t Parser::getNextToken() {
    return *(it++);
}

void Parser::generateTree() {
    root = getStatement();

    if (it != tks.end())
        throw runtime_error("could not reach end of statement - did not consume everything");
}

Statement* Parser::getStatement() {
    token_t stmnt_head = getNextToken();

    switch (stmnt_head.t) {
        case Token::PRINT:
        {
            // Consumes an expression/string and an expression/string list
            // Only shows expression because the string could be found from it
            PrntStatement* s = new PrntStatement();
            s->l = getExprList();
            return s;
        }
        case Token::IF:
        {
            IfStatement* s = new IfStatement();
            s->e1 = getExpression();
            s->relop = getRelop();
            s->e2 = getExpression();
            if (getNextToken().t != Token::THEN)
                throw runtime_error("expected THEN after second expression");
            s->stmnt = getStatement();
            return s;
        }
        case Token::GOTO:
        {
            GotoStatement* s = new GotoStatement();
            s->expr = getExpression();
            return s;
        }
        case Token::INPUT:
        {
            InpStatement* s = new InpStatement();
            s->vl = getVarList();
            return s;
        }
        case Token::LET:
        {
            LetStatement* s = new LetStatement();
            s->v = getVar();
            if (getNextToken().t != Token::EQ)
                throw runtime_error("expected '=' after variable");
            s->expr = getExpression();
            return s;
        }
        case Token::GOSUB:
        {
            GSubStatement* s = new GSubStatement();
            s->expr = getExpression();
            return s;
        }
        case Token::RETURN:
        case Token::CLEAR:
        case Token::LIST:
        case Token::RUN:
        case Token::END:
        {
            Statement* s = new Statement();
            s->t = stmnt_head.t;
            return s;
        }
        default:
            throw runtime_error("expected a statement");
    }
}

ExprList* Parser::getExprList() {
    ExprList* ret = new ExprList();

    if (it->t == Token::STRING) {
        String* s = new String();
        s->s = it->str;
        ret->exprs.push_back(s);

        getNextToken();
    }
    else {
        ret->exprs.push_back(getExpression());
    }

    while (it->t == Token::COMMA) {
        getNextToken();

        // Sanity checking - if the next token is the end of the line
        if (it == tks.end() || it->t == Token::COMMA)
            throw runtime_error("expected an expression/string after comma");

        if (it->t == Token::STRING) {
            String* s = new String();
            s->s = it->str;
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
    // Check if the first token is a binop or not, and add the correct token to
    // the first slot.
    if (it->t == Token::ADD || it->t == Token::SUB) {
        ret->tks.push_back(it->t);
        getNextToken();
    }
    else {
        ret->tks.push_back(Token::NONE);
    }

    // Check for the first term (must be present)
    ret->ts.push_back(getTerm());

    // The next n terms (and tokens) are all optional
    while (it->t == Token::ADD || it->t == Token::SUB) {
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
    while (it->t == Token::MUL || it->t == Token::DIV) {
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
    Factor* ret = new Factor();

    switch (it->t) {
    case Token::VARIABLE:
        ret->t = FType::Var;
        ret->v = getVar();
        break;
    case Token::NUMBER:
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

    while (it->t == Token::COMMA) {
        getNextToken();

        // Sanity checking
        if (it == tks.end() || it->t == Token::COMMA)
            throw runtime_error("expected a variable after the comma");

        ret->vars.push_back(getVar());
    }

    return ret;
}

Variable* Parser::getVar() {
    // Sanity checking
    if (it == tks.end())
        throw runtime_error("expected a variable");

    Variable* ret = new Variable();

    if (isalpha(it->str[0])) {
        ret->v = it->num;
        getNextToken();
    }
    else {
        throw runtime_error("expected a variable");
    }

    return ret;
}

Token Parser::getRelop() {
    // Sanity checking
    if (it == tks.end())
        throw runtime_error("expected a binary operator");

    Token ret;

    switch (it->t) {
        case Token::EQ:
        case Token::NEQ:
        case Token::LT:
        case Token::LTE:
        case Token::GT:
        case Token::GTE:
            ret = it->t;
            // Consume
            getNextToken();
            break;
        default:
            throw runtime_error("expected a binary operator");
    }

    return ret;
}
