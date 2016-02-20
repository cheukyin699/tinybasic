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
        if (tmp.str.empty() && isspace(line[i]))
            continue;
        if (line[i] == '"' && tmp.t == NONE) {
            // Check for a string and put it into string mode
            tmp.t = STRING;
        }
        else if (line[i] == '"' && tmp.t == STRING) {
            // If you are done with the string, append and reset it
            tokens.push_back(tmp);
            tmp = create_token();
        }
        else if (!(isalpha(line[i]) || ispunct(line[i])) && tmp.t == NONE && !tmp.str.empty()) {
            // Use whitespace and commas to delimit keywords and variables
            if (tmp.str.size() == 1 && isalpha(tmp.str[0])) {
                // It's a variable
                tmp.t = VARIABLE;
                tmp.num = tmp.str[0] - 'A';
                tokens.push_back(tmp);
                tmp = create_token();
            }
            else {
                try {
                    // If it is an invalid keyword, throw an exception
                    tmp.t = token_map.at(tmp.str);
                    tokens.push_back(tmp);
                    tmp = create_token();
                    if (line[i] == ',') {
                        // If it is a comma, add it
                        tmp.t = COMMA;
                        tmp.str = ",";
                        tokens.push_back(tmp);
                        tmp = create_token();
                    }
                } catch (exception ex) {
                    throw runtime_error("invalid keyword '" + tmp.str + "'");
                }
            }
            if (isdigit(line[i]))
                i--;
        }
        else if (!isdigit(line[i]) && tmp.t == NUMBER) {
            // Convert into number
            tmp.num = stoi(tmp.str);
            tokens.push_back(tmp);
            tmp = create_token();
            if (line[i] == ',') {
                // If it is a comma, add it
                tmp.t = COMMA;
                tmp.str = ",";
                tokens.push_back(tmp);
                tmp = create_token();
            } else {
                // Put it back
                i--;
            }
        }
        else if (isdigit(line[i]) && tmp.t == NONE) {
            // Check for a digit and put it into digit mode
            tmp.t = NUMBER;
            tmp.str += line[i];
        }
        else {
            tmp.str += line[i];
        }
    }

    if (!tmp.str.empty()) {
        if (tmp.t == NUMBER) {
            // Handle the remaining number
            tmp.num = stoi(tmp.str);
            tokens.push_back(tmp);
            tmp = create_token();
        }
        else if (tmp.t == STRING) {
            // There's no end to this string!
            throw runtime_error("unexpected EOL; forgotten '\"'?");
        }
        else if (tmp.str.size() == 1 && isalpha(tmp.str[0])) {
            // It is a variable
            tmp.t = VARIABLE;
            tmp.num = tmp.str[0] - 'A';
            tokens.push_back(tmp);
            tmp = create_token();
        }
        else {
            // We have an issue if the string isn't empty because that means
            // something went wrong
            try {
                // If it is an invalid keyword, throw an exception
                tmp.t = token_map.at(tmp.str);
                tokens.push_back(tmp);
                tmp = create_token();
            } catch (exception ex) {
                throw runtime_error("invalid keyword '" + tmp.str + "'");
            }
        }
    }

    return tokens;
}

ostream& operator<<(ostream& os, token_t& t) {
    os << "Type: " << t.t << " Value: " << t.str;
    return os;
}
