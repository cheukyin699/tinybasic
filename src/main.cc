#include <string>
#include <iostream>

#include "editor.h"

#define VERSION         "v0.0.0"

int main(/*int argc, char* argv[]*/) {
    Editor ed;
    string line;

    cout << "tbasic line editor " VERSION << endl;
    while (ed.isRunning()) {
        // Command prompt
        cout << ">> ";
        getline(cin, line);
        ed.handleInput(line);
    }

    return 0;
}