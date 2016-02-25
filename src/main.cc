#include <string>
#include <iostream>

#include "editor.h"

#define VERSION         "v0.0.0"

const string Prompt = ">> ";

int main(/*int argc, char* argv[]*/) {
    Editor ed;
    string line;

    cout << "tbasic line editor " VERSION "\n";
    while (ed.isRunning()) {
        // Command prompt
        cout << Prompt;
        getline(cin, line);
        ed.handleInput(line);
    }

    return 0;
}
