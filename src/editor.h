#ifndef EDITOR_H
#define EDITOR_H
#define DEBUG

#include <string>
#include <vector>

#include "tokenizer.h"

using namespace std;

class Editor {
    private:
        vector<string> buffer;          // Buffer of characters
        unsigned curr_line;
        string filename;
        bool running;

        void printLine(unsigned);
        void navLine(int);
        void insertLine(string);
        void editLine(string);
        void removeLine(unsigned);
        void fileStats();

    public:
        Editor();

        void handleInput(string);
        void write(string);
        void load(string);
        void execute();
        void help();

        bool isRunning() {return running;};

};

#endif
