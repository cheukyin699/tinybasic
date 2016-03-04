#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>

#include "tokenizer.h"

using namespace std;

const vector<string> Test_Strings = {
    "IF A<B THEN GOTO 1",
    "PRINT 123+246 * 300",
    "PRINT \"Hello, world\", \"Are you feeling it yet?\"",
};

int main() {
    for (auto line: Test_Strings) {
        try {
            auto tokens = get_tokens(line);

            cout << "Line '" << line << "':\n";
            for (auto t: tokens)
                cout << t << endl;
            cout << '\n';
        } catch (runtime_error e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}
