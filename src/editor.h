#ifndef EDITOR_H
#define EDITOR_H
#define DEBUG

#include <string>
#include <vector>

#include "tokenizer.h"
#include "grammar.h"
#include "interpreter.h"

using namespace std;

class Editor {
    private:
        Interpreter inter;
        vector<string> buffer;          // Buffer of characters
        vector<Statement*> stmnts;      // Buffer of statements (lines)
        unsigned curr_line;
        string filename;
        bool running, changed;

        void printLine(unsigned);
        void navLine(int);
        void insertLine(string);
        void editLine(string);
        void removeLine(unsigned);
        void fileStats();

    public:
        Editor();
        ~Editor();

        void handleInput(string);
        void write(string);
        void load(string);
        void execute();
        void help();

        bool isRunning() {return running;};

};

#endif
