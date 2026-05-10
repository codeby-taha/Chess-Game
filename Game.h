#ifndef GAME_H
#define GAME_H
#include "board.h"
#include "utils.h"
#include <string>
using namespace std;
// main game logic class
class game {
protected:
    board chessboard;
    bool whiteturn;
public:
    string whitename;
    string blackname;
    int lastfromx, lastfromy, lasttox, lasttoy;
    bool haslastmove;
    stringlist whitecaptured;
    stringlist blackcaptured;
    movehistorylist movehistory;
    int legalhx[30];
    int legalhy[30];
    int legalcount;
    bool gameover;
    bool paused;
    int whitewins, whitelosses, whitedraws;
    int blackwins, blacklosses, blackdraws;
    // backup struct for move simulation
    struct movebackup {
        piece* movedpiece;
        piece* capturedpiece;
    };
    game();
    void startgame();
    bool findking(const string& col, int& kx, int& ky) const;
    bool iskingcheck(const string& col);
    movebackup simulatemove(int fromx, int fromy, int tox, int toy);
    void undomove(int fromx, int fromy, int tox, int toy, movebackup b);
    bool islegalmove(int fromx, int fromy, int tox, int toy);
    void getlegalmoves(int fromx, int fromy);
    bool hasanylegal(const string& col);
    bool ischeckmate(const string& col);
    bool isstalemate(const string& col);
    void promotepawn(int row, int col, const string& color);
    bool trycastling(int fromx, int fromy, int tox, int toy);
    int colfromchar(char c);
    int rowfromchar(char c);
    void displaycaptured();
    void displayhistory();
    void savenames(const string& filename);
    bool loadnames(const string& filename);
    void displaystats();
    void displayleaderboard();
    void playturn(const string& from, const string& to);
    void showingamemenu();
    void gameloop();
};
#endif