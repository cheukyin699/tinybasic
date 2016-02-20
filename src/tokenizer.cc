#include <exception>

#include "tokenizer.h"

token_t create_token(Token tt, int n, string s) {
    token_t t;
    t.t = tt;
    t.num = n;
    t.str = s;

    return t;
}

vector<token_t> get_tokens(string line) {
    vector<token_t> tokens;
    token_t tmp = create_token();

    for (unsigned i = 0; i < line.size(); i++) {
        if (line[i] == '"' && tmp.t == NONE) {
            // Check for a string and put it into string mode
            tmp.t = STRING;
        }
        else if (line[i] == '"' && tmp.t == STRING) {
            // If you are done with the string, append and reset it
            tokens.push_back(tmp);
            tmp = create_token();
        }
        else if (line[i] == ' ' && tmp.t == NONE) {
            // Use whitespace to delimit keywords
            try {
                // If it is an invalid keyword, throw an exception
                tmp.t = token_map.at(tmp.str);
                tokens.push_back(tmp);
                tmp = create_token();
            } catch (exception ex) {
                throw runtime_error("invalid keyword");
            }
        }
        else {
            tmp.str += line[i];
        }
    }

    if (!tmp.str.empty()) {
        // We have an issue if the string isn't empty because that means
        // something went wrong
        throw runtime_error("unexpected EOL");
    }

    return tokens;
}

ostream& operator<<(ostream& os, token_t& t) {
    os << "Type: " << t.t << "\tValue: " << t.str;
    return os;
}
