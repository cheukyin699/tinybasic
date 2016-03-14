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
                throw runtime_error("expected THEN");
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
                throw runtime_error("expected '='");
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
