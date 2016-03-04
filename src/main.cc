#include <string>
#include <iostream>

#include "editor.h"

#define VERSION         "v0.0.0"

const string Prompt = ">> ";

int main(/*int argc, char* argv[]*/) {
    Editor ed;
    string line;

    cout << "tbasic line editor " VERSION "\n";
    do {
        // Command prompt
        cout << Prompt;
        getline(cin, line);
        ed.handleInput(line);
    } while (ed.isRunning());

    return 0;
}
