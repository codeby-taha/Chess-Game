#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;
// dynamic string list
struct stringlist {
    string* data;
    int count;
    int capacity;
    stringlist();
    ~stringlist();
    void add(string s);
    void clear();
    string get(int i) const;
};
// single move record
struct moverecord {
    string from;
    string to;
    char piecesym;
    string piececol;
};
// dynamic move history list
struct movehistorylist {
    moverecord* data;
    int count;
    int capacity;
    movehistorylist();
    ~movehistorylist();
    void add(moverecord m);
    void clear();
};
// clears the console screen using ansi escape codes
void clearscreen();
#endif