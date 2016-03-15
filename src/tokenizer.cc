#include <algorithm>
#include <exception>
#include <stdexcept>

#include "tokenizer.h"

using namespace std;

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
            unsigned size = is_token(line.substr(i, s), t);

            // If it didn't find anything, continue with a smaller size
            if (t.t == NONE) {
                // If you have already checked once, change size
                if (s > Longest_KW) s = Longest_KW;
            }
            else {
                tokens.push_back(t);
                i += (size? size : s) - 1;
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

unsigned is_token(string line, token_t& token) {
    unsigned ret = 0;
    reset_token(token);
    // Checks to see if it is a variable (size 1)
    if (line.size() == 1 && isalpha(line[0])) {
        token.t = VARIABLE;
        token.str = line;
        token.num = line[0]-65;
    }

    // Checks if it is a string
    else if (line[0] == '"') {
        unsigned quote = line.find('"', 1);
        if (quote == line.size()-1) {
            // If you can only find 1 other " in the string, and it's at the end
            token.t = STRING;
            token.str = line.substr(1, line.size()-2);
        } else {
            // If you have found other " in the string, change the stuff up...
            token.t = STRING;
            token.str = line.substr(1, quote-1);
            ret = quote+1;
        }
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

    // Checks if it is a number
    else if (isdigit(line[0])) {
        unsigned i;
        for (i = 0; i < line.length() - 1; i++) {
            if (!isdigit(line[i+1])) break;
        }
        ret = i + 1;
        token.t = NUMBER;
        token.str = line.substr(0, i + 1);
        token.num = stoi(token.str);
    }

    // Checks to see if it is a binary operator or keyword by looking up the
    // tokens
    else if (token_map.find(line) != token_map.end()) {
        token.t = token_map.at(line);
        token.str = line;
    }

    return ret;
}

ostream& operator<<(ostream& os, token_t& t) {
    os << "Type: " << t.t << " Value: " << t.str;
    return os;
}
