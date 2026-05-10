#include "utils.h"
// --- stringlist ---
stringlist::stringlist() {
    capacity = 32;
    count = 0;
    data = new string[capacity];
}
stringlist::~stringlist() {
    delete[] data;
}
void stringlist::add(string s) {
    if (count < capacity)
        data[count++] = s;
}
void stringlist::clear() {
    count = 0;
}
string stringlist::get(int i) const {
    return data[i];
}
// --- movehistorylist ---
movehistorylist::movehistorylist() {
    capacity = 300;
    count = 0;
    data = new moverecord[capacity];
}
movehistorylist::~movehistorylist() {
    delete[] data;
}
void movehistorylist::add(moverecord m) {
    if (count < capacity)
        data[count++] = m;
}
void movehistorylist::clear() {
    count = 0;
}
// --- clearscreen ---
void clearscreen() {
    cout << "\033[2J\033[1;1H";
}
