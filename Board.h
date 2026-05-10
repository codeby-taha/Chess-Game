#ifndef BOARD_H
#define BOARD_H
#include "piece.h"
#include <iostream>
using namespace std;
// the 8x8 chess board
class board {
public:
    piece* squares[8][8];
    board();
    void placepiece(piece* p, int x, int y);
    piece* getpiece(int x, int y) const;
    bool ispathclear(int fromx, int fromy, int tox, int toy) const;
    bool isdiagonalclear(int fromx, int fromy, int tox, int toy) const;
    bool movepiece(int fromx, int fromy, int tox, int toy);
    void displayboard(int checkkingx = -1, int checkkingy = -1,
        int lastfromx = -1, int lastfromy = -1,
        int lasttox = -1, int lasttoy = -1,
        int highlightx[64] = nullptr, int highlighty[64] = nullptr,
        int highlightcount = 0) const;
};
#endif