#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <string>
#include <vector>

#include "tokenizer.h"

using namespace std;


/* The type that a factor contains. Makes it slightly easier to check what the
 * factor contains.
 */
enum FType {None, Var, Num, Exp};

class Factor;

/* The Statement class.
 *
 * The base class of all statements. Most statements that aren't able to be
 * represented by a single token are derived from this class.
 */
class Statement {
public:
    Statement(Token tk): t(tk) {}

    Token t;
};

/* The StrExpr class.
 *
 * Represents both the possibilities of a string AND an expression; both classes
 * consequentially derived from this one.
 */
class StrExpr {
protected:
    StrExpr(bool s): str(s) {}
public:
    bool str;
};

/* The Term class.
 *
 * Unlike the expression class, it is impossible to have any binary operations
 * in front of a factor, so we won't consider that case.
 *
 * Valid token (binops) are: (*|/).
 */
class Term {
public:
    Term() {}
    ~Term();

    vector<Factor*> fs;
    vector<Token> tks;
};

/* The Expression class.
 *
 * The first binop (+/-/e) is the first element in ts. If there is no first,
 * Token::NONE is used.
 *
 * Valid token (binops) are: (+|-|NONE).
 */
class Expression: public StrExpr {
public:
    Expression(): StrExpr(false) {}
    ~Expression();

    vector<Term*> ts;
    vector<Token> tks;
};

/* The String class.
 *
 * Represents a string. Simple as that.
 */
class String: public StrExpr {
public:
    String(): StrExpr(true), s("") {}
    String(string str): StrExpr(true), s(str) {}

    string s;
};

/* The ExprList class.
 *
 * Contains a vector holding StrExpr objects. Commas aren't counted for obvious
 * reasons.
 */
class ExprList {
public:
    ExprList() {}
    ~ExprList();

    vector<StrExpr*> exprs;
};

/* The Variable class.
 *
 * Holds the variable name [A-Z].
 */
class Variable {
public:
    Variable(): v(0) {}
    Variable(char c): v(c) {}

    char v;
};

/* The Factor class.
 *
 * Could be one of 3 different types (represented by FType):
 * - Variable
 * - Integer
 * - Expression
 */
class Factor {
public:
    Factor(): t(None), v(0), n(0), expr(0) {}
    ~Factor();

    FType t;
    Variable* v;
    int n;
    Expression* expr;
};

/* The VarList class.
 *
 * Represents the list of variables for Input Statement.
 */
class VarList {
public:
    VarList() {}
    ~VarList();

    vector<Variable*> vars;
};

/* The PrntStatement class.
 *
 * Represents the Print Statement. Holds a list of Expressions, either strings
 * or expressions.
 */
class PrntStatement: public Statement {
public:
    PrntStatement(ExprList* l): Statement(PRINT), l(l) {}
    ~PrntStatement();

    ExprList* l;
};

/* The IfStatement class.
 *
 * Represents the If Statement. In the form of:
 *      IF e1 relop e2 THEN stmnt
 * For obvious reasons, the THEN token is omitted from the class, and will be
 * checked in the Parser::getStatement() function.
 */
class IfStatement: public Statement {
public:
    IfStatement(): Statement(IF), e1(0), relop(NONE), e2(0), stmnt(0) {}
    ~IfStatement();

    Expression* e1;
    Token relop;
    Expression* e2;
    Statement* stmnt;
};

/* The GotoStatement class.
 *
 * Represents the Goto Statement.
 */
class GotoStatement: public Statement {
public:
    GotoStatement(): Statement(GOTO), expr(0) {}
    // For child only
    GotoStatement(bool): Statement(GOSUB), expr(0) {}
    ~GotoStatement();

    Expression* expr;
};

/* The InpStatement class.
 *
 * Represents an Input Statement. Contains a list of variables all from which to
 * store input in.
 */
class InpStatement: public Statement {
public:
    InpStatement(): Statement(INPUT), vl(0) {}
    ~InpStatement();

    VarList* vl;
};

/* The LetStatement class.
 *
 * Represents the humble Let Statement. In the form of:
 *      LET v = expr
 * For obvious reasons, the equal sign token is not present in the class, and
 * will be checked in the Parser::getStatement() function.
 */
class LetStatement: public Statement {
public:
    LetStatement(): Statement(LET), v(0), expr(0) {}
    ~LetStatement();

    Variable* v;
    Expression* expr;
};

/* The GSubStatement class
 *
 * Represents a GoSub Statement. It is so similar to the Goto statement that I
 * thought it would be fitting to make it derived from the GotoStatement class.
 */
class GSubStatement: public GotoStatement {
public:
    GSubStatement(): GotoStatement(true) {}
};

#endif
