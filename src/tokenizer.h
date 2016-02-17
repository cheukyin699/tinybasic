#ifndef TOKENIZER_H
#define TOKENIZER_H
/*
 * All these things that are binary operators would be converted from char to
 * int. This includes the following:
 *
 * +*-/<>=
 */
enum Token {
    NUMBER, STRING,
    // Doubled binary operators
    LTE, GTE,
    // Reserved Keywords
    PRINT, IF, THEN, GOTO, INPUT, LET, GOSUB, RETURN, CLEAR, LIST, RUN, END
};

#endif
