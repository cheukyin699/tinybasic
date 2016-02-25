#include <algorithm>
#include <exception>
#include <stdexcept>

#include "tokenizer.h"

using namespace std;

token_t create_token(Token tt, int n, string s) {
    token_t t;
    t.t = tt;
    t.num = n;
    t.str = s;

    return t;
}

void reset_token(token_t& t) {
    t.t = NONE;
    t.num = 0;
    t.str = "";
}

v_tokens get_tokens(string line) {
    v_tokens tokens;

    // Initial indexing
    for (unsigned i = 0; i < line.size(); i++) {
        // Skip any and all spaces
        if (isspace(line[i])) continue;

        // Take the reverse
        token_t t;
        bool has_pushed = false;
        for (unsigned s = line.size()-i; s > 0; s--) {
            // To save space, it doesn't return anything
            is_token(line.substr(i, s), t);

            // If it didn't find anything, continue with a smaller size
            if (t.t == NONE)
                continue;
            else {
                tokens.push_back(t);
                i += s - 1;
                has_pushed = true;
                break;
            }
        }

        if (!has_pushed) {
            // If it didn't find anything at all, there must be a problem
            throw runtime_error(to_string(i) + " invalid token");
        }
    }

    return tokens;
}

void is_token(string line, token_t& token) {
    reset_token(token);
    // Checks to see if it is a variable (size 1)
    if (line.size() == 1 && isalpha(line[0])) {
        token.t = VARIABLE;
        token.str = line;
        token.num = line[0]-65;
    }

    // Checks if it is a string
    else if (line[0] == '"' && line.find('"', 1) == line.size()-1) {
        // If you can only find 1 other " in the string, and it's at the end
        token.t = STRING;
        token.str = line.substr(1, line.size()-2);
    }

    // Checks if it is a number
    // The lambda is to avoid the overloaded isdigit
    else if (all_of(line.begin(), line.end(), [] (char x) {return isdigit(x);})) {
        // If you can only find 1 other digit in the string, and it's at the end
        // OR if the string is of size 1
        token.t = NUMBER;
        token.str = line;
        token.num = stoi(line);
    }

    // Checks to see if it is a binary operator or keyword by looking up the
    // tokens
    else if (token_map.find(line) != token_map.end()) {
        token.t = token_map.at(line);
        token.str = line;
    }
}

ostream& operator<<(ostream& os, token_t& t) {
    os << "Type: " << t.t << " Value: " << t.str;
    return os;
}
