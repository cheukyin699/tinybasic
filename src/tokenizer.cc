#include "tokenizer.h"

vector<token_t> get_tokens(string line) {
    vector<token_t> tokens;
    token_t tmp;

    for (unsigned i = 0; i < line.size(); i++) {
        if (line[i] == '"' && tmp.t == NONE) {
            // Check for a string and put it into string mode
            tmp.t = STRING;
        }
        else if (line[i] == '"' && tmp.t == STRING) {
            // If you are done with the string, append and reset it
            tokens.append(tmp);
        }
        else {
            tmp.str += line[i];
        }
    }

    return tokens;
}

