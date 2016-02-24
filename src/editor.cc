#include <algorithm>
#include <cctype>
#include <cstdio>
#include <fstream>
#include <iostream>

#include "editor.h"
#include "tokenizer.h"
#include "utilities.h"

Editor::Editor() {
    curr_line = 0;
    running = true;
    filename = "";
}

void Editor::handleInput(string line) {
    unsigned line_len = line.length();
    char cmd_char = isalpha(line[0])? line[0]&0xdf: line[0];// Conversion to uppercase
    int cmd_num = 1;                        // Number of times to repeat
    string str_num = "";                    // Number of times to repeat (as string)

    // Zero length sanity check
    if (line_len == 0) return;

    // Find the number of times the user specified to repeat the command.
    // Defaults to 1. The command must immediately be followed by the number, or
    // else it doesn't count it entirely. Notice the elaborate method of
    // appending characters to string, then converting the whole string into an
    // integer.
    for (unsigned i = 1; i < line_len; i++) {
        if (!isdigit(line[i]))  break;
        else                    str_num += line[i];
    }

    if (!str_num.empty())
        cmd_num = stoi(str_num);

    switch (cmd_char) {
        case 'Q': running = false; return;  // Q for quit
        case 'U':                           // Navigate up 1 line
            navLine(-cmd_num);
            return;
        case 'D':                           // Navigate down 1 line
            navLine(cmd_num);
            return;
        case 'I':                           // Insert this line
            insertLine(line);
            return;
        case 'R':                           // Remove (some) lines
            removeLine(cmd_num);
            return;
        case 'S':                           // Show all lines
            for (unsigned i = 0; i < buffer.size(); i++)
                printLine(i);
            return;
        case 'C':                           // Show current line
            printLine(curr_line);
            return;
        case 'T':                           // Move to very top
            curr_line = 0;
            return;
        case 'B':                           // Move to very bottom
            curr_line = buffer.size() - 1;
            return;
        case 'W':                           // Write to file
            write(line);
            return;
        case 'L':                           // Load from file
            load(line);
            return;
        case 'X':                           // Execute the program
            execute();
            return;
        case 'H':                           // Output help screen
            help();
            return;
        case '?':                           // Output file statistics
            fileStats();
            return;
        default:                            // Report an error
            printf("Couldn't recognize command '%c'\n", cmd_char);
            return;
    }
}

void Editor::printLine(unsigned i) {
    printf("%04u %s\n", i, buffer[i].c_str());
}

void Editor::navLine(int lines) {
    if (lines < 0 && curr_line <= 0) {
        // Specific to navigating upwards
        cout << "At top of file already" << endl;
        return;
    } else if (lines > 0 && curr_line >= buffer.size() - 1) {
        // Specific to navigating downwards
        cout << "At bottom of file already" << endl;
        return;
    }
    curr_line = clamp<unsigned>(0, buffer.size(), curr_line + lines);
    printLine(curr_line);
}

void Editor::insertLine(string line) {
    // Skip all the spaces
    unsigned ind = nextToken(line, 1);
    // Automagically converts to ALL CAPS
    transform(line.begin(), line.end(), line.begin(), ::toupper);
    // Insert the line into buffer, AFTER the current line
    // It also increments the line counter
    // If the buffer is empty, it merely pushes it back
    if (buffer.size() == 0 || curr_line == buffer.size()) {
        buffer.push_back(line.substr(ind));
        curr_line++;
    }
    else
        buffer.insert(buffer.begin() + ++curr_line, line.substr(ind));
}

void Editor::removeLine(unsigned times) {
    unsigned erase_count = clamp<unsigned>(0, buffer.size(), curr_line + times);
    buffer.erase(buffer.begin() + curr_line, buffer.begin() + erase_count);
}

void Editor::write(string line) {
    // Get filename, if any
    unsigned ind = nextToken(line, 1);
    string fn = line.substr(ind);
    if (fn.empty()) {
        if (filename.empty()) {
            cout << "error: must specify filename" << endl;
            return;
        }
        fn = filename;
    }
    ofstream f(fn, ios::out);

    if (f.good()) {
        unsigned lines = 0;
        for (auto l: buffer) {
            f << l << endl;
            lines++;
        }
        cout << lines << " lines written successfully to '" << fn << "'" << endl;
    } else {
        cout << "Couldn't open file '" << fn << "' for writing" << endl;
    }

    f.close();

    return;
}

void Editor::load(string line) {
    // Get filename, if any
    unsigned ind = nextToken(line, 1);
    string fn = line.substr(ind);
    if (fn.empty()) {
        if (filename.empty()) {
            cout << "error: must specify filename" << endl;
            return;
        }
        fn = filename;
    }
    ifstream f(fn, ios::in);

    if (f.good()) {
        // Clear the buffer first
        buffer.clear();
        filename = fn;
        string l = "";
        unsigned lines = 0;
        while(getline(f, l)) {
            buffer.push_back(l);
            lines++;
        }

        cout << lines << " lines read successfully from '" << fn << "'" << endl;
    } else {
        cout << "Couldn't open file '" << fn << "' for reading" << endl;
    }

    f.close();
}

void Editor::execute() {
    // TODO fill this in once done testing

    // Tokenizer
    unsigned errs = 0, i = 0;
    for (auto l: buffer) {
        i++;
        try {
            auto tokens = get_tokens(l);
            #ifdef DEBUG
            for (auto t: tokens)
                cout << t << endl;
            #endif
        } catch (runtime_error ex) {
            cerr << "Line " << i << ":" << ex.what() << endl;
            errs++;
        }
    }
    cout << "Total of " << errs << " error(s) reported.\n";
}

void Editor::fileStats() {
    cout << "Filename: " << (filename.empty()? "<untitled>": filename) << endl
        << "Current line: " << curr_line << endl
        << "Total lines: " << buffer.size() << endl;
}

void Editor::help() {
    // TODO
}
