#ifndef EDITOR_H
#define EDITOR_H
#define DEBUG

#include <string>
#include <vector>

using namespace std;

class Editor {
    private:
        vector<string> buffer;
        unsigned curr_line;
        string filename;
        bool running;

        void printLine(unsigned);

    public:
        Editor();

        void handleInput(string);

        bool isRunning() {return running;};

};

#endif
