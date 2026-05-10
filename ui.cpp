#include "ui.h"
void showhowtoplay() {
    clearscreen();
    cout << "=== Kaise Khelein ===" << endl << endl;
    cout << "  Move karne ka tarika: FROM TO" << endl;
    cout << "  Example: e2 e4" << endl << endl;
    cout << "  Columns: a se h (left to right)" << endl;
    cout << "  Rows:    1 se 8 (neeche se upar)" << endl << endl;
    cout << "  Special commands:" << endl;
    cout << "    menu  - game menu kholo" << endl;
    cout << "    exit  - game chodo" << endl << endl;
    cout << "  Castling: king ko 2 column move karo rook ki taraf" << endl;
    cout << "    Example: e1 g1 (white kingside castle)" << endl << endl;
    cout << "  Pawn Promotion: pawn last row tak jaye to piece choose karo" << endl << endl;
    cout << "  Uppercase letters = White pieces" << endl;
    cout << "  Lowercase letters = Black pieces" << endl;
    cout << "  [K] = King in check" << endl;
    cout << "  (.) = Legal move squares" << endl;
    cout << endl << "Enter dabao...";
    string tmp; cin.ignore(); getline(cin, tmp);
}
void showmainmenu() {
    clearscreen();
    cout << endl;
    cout << "  +================================+" << endl;
    cout << "  |                                |" << endl;
    cout << "  |     C H E S S   G A M E       |" << endl;
    cout << "  |       C++ Console Edition      |" << endl;
    cout << "  |                                |" << endl;
    cout << "  +================================+" << endl;
    cout << endl;
    cout << "  [1] Naya Game" << endl;
    cout << "  [2] Names Load Karo" << endl;
    cout << "  [3] Kaise Khelein" << endl;
    cout << "  [4] Leaderboard" << endl;
    cout << "  [5] Stats" << endl;
    cout << "  [6] Baahar Jao" << endl;
    cout << endl << "  Apna choice likhein: ";
}