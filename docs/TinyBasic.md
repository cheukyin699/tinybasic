## Tiny BASIC

### Tiny BASIC Grammar

Tiny BASIC is tiny, so it's grammar is also tiny. The grammar, if you were
wondering, is copied directly off of wikipedia. It is listed in Backus-Naur
form. Hopefully, you are familiar with it. `CR` stands for carriage return,
<kbd>Enter</kbd>.

```
   line ::= statement CR

   statement ::= PRINT expr-list
                 IF expression relop expression THEN statement
                 GOTO expression
                 INPUT var-list
                 LET var = expression
                 GOSUB expression
                 RETURN
                 CLEAR
                 LIST
                 RUN
                 END

   expr-list ::= (string|expression) (, (string|expression) )*

   var-list ::= var (, var)*

   expression ::= (+|-|ε) term ((+|-) term)*

   term ::= factor ((*|/) factor)*

   factor ::= var | number | (expression)

   var ::= A | B | C ... | Y | Z

   number ::= digit digit*

   digit ::= 0 | 1 | 2 | 3 | ... | 8 | 9

   relop ::= < (>|=|ε) | > (<|=|ε) | =
```
