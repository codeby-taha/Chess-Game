#include "board.h"
#include <cstdlib>
board::board() {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            squares[i][j] = nullptr;
}
void board::placepiece(piece* p, int x, int y) {
    squares[x][y] = p;
}
piece* board::getpiece(int x, int y) const {
    if (x < 0 || x >= 8 || y < 0 || y >= 8) return nullptr;
    return squares[x][y];
}
bool board::ispathclear(int fromx, int fromy, int tox, int toy) const {
    int stepx = (tox > fromx) ? 1 : (tox < fromx ? -1 : 0);
    int stepy = (toy > fromy) ? 1 : (toy < fromy ? -1 : 0);
    int x = fromx + stepx;
    int y = fromy + stepy;
    while (x != tox || y != toy) {
        if (squares[x][y] != nullptr) {
            return false;
        }
        x += stepx;
        y += stepy;
    }
    return true;
}
bool board::isdiagonalclear(int fromx, int fromy, int tox, int toy) const {
    int stepx = (tox > fromx) ? 1 : -1;
    int stepy = (toy > fromy) ? 1 : -1;
    int x = fromx + stepx;
    int y = fromy + stepy;
    while (x != tox || y != toy) {
        if (squares[x][y] != nullptr) {
            return false;
        }
        x += stepx;
        y += stepy;
    }
    return true;
}
bool board::movepiece(int fromx, int fromy, int tox, int toy) {
    if (fromx < 0 || fromx >= 8 || fromy < 0 || fromy >= 8 ||
        tox < 0 || tox >= 8 || toy < 0 || toy >= 8) {
        return false;
    }
    piece* p = getpiece(fromx, fromy);
    if (!p) {
        return false;
    }
    piece* target = getpiece(tox, toy);
    if (target && target->getcolor() == p->getcolor()) {
        return false;
    }
    if (!p->isvalidmove(fromx, fromy, tox, toy)) {
        return false;
    }
    rook* rok = dynamic_cast<rook*>(p);
    if (rok && !ispathclear(fromx, fromy, tox, toy)) {
        return false;
    }
    bishop* bp = dynamic_cast<bishop*>(p);
    if (bp && !isdiagonalclear(fromx, fromy, tox, toy)) {
        return false;
    }
    queen* qn = dynamic_cast<queen*>(p);
    if (qn) {
        int dx = abs(tox - fromx);
        int dy = abs(toy - fromy);
        if (fromx == tox || fromy == toy) {
            if (!ispathclear(fromx, fromy, tox, toy)) return false;
        }
        else if (dx == dy) {
            if (!isdiagonalclear(fromx, fromy, tox, toy)) return false;
        }
    }
    pawn* pwn = dynamic_cast<pawn*>(p);
    if (pwn) {
        int dy = toy - fromy;
        if (dy == 0 && target != nullptr) {
            return false;
        }
        if ((dy == 1 || dy == -1) && target == nullptr) {
            return false;
        }
    }
    if (target) {
        delete target;
    }
    squares[tox][toy] = p;
    squares[fromx][fromy] = nullptr;
    p->hasmoved = true;
    return true;
}
void board::displayboard(int checkkingx, int checkkingy,
    int lastfromx, int lastfromy,
    int lasttox, int lasttoy,
    int highlightx[64], int highlighty[64],
    int highlightcount) const {
    cout << endl;
    cout << "     ";
    for (int j = 0; j < 8; j++)
        cout << (char)('a' + j) << "  ";
    cout << endl;
    cout << "   +";
    for (int j = 0; j < 8; j++) cout << "---+";
    cout << endl;
    for (int i = 0; i < 8; i++) {
        cout << (8 - i) << "  |";
        for (int j = 0; j < 8; j++) {
            bool islastmove = (i == lastfromx && j == lastfromy) ||
                (i == lasttox && j == lasttoy);
            bool islegal = false;
            if (highlightx != nullptr) {
                for (int h = 0; h < highlightcount; h++) {
                    if (highlightx[h] == i && highlighty[h] == j) {
                        islegal = true;
                        break;
                    }
                }
            }
            bool ischeckedking = (i == checkkingx && j == checkkingy);
            piece* p = squares[i][j];
            if (p) {
                if (ischeckedking)
                    cout << "[" << p->getunicode() << "]";
                else if (islastmove)
                    cout << "(" << p->getunicode() << ")";
                else
                    cout << " " << p->getunicode() << " ";
            }
            else {
                if (islegal)
                    cout << " . ";
                else if (islastmove)
                    cout << "( )";
                else
                    cout << "   ";
            }
            cout << "|";
        }
        cout << "  " << (8 - i) << endl;
        cout << "   +";
        for (int j = 0; j < 8; j++) cout << "---+";
        cout << endl;
    }
    cout << "     ";
    for (int j = 0; j < 8; j++)
        cout << (char)('a' + j) << "  ";
    cout << endl;
}
