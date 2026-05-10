#include "piece.h"
#include <cstdlib>
// --- base piece ---
piece::piece(string c, char s) : color(c), symbol(s), hasmoved(false) {}
piece::~piece() {}
char piece::getsymbol() const {
    return symbol;
}
string piece::getunicode() const {
    return "?";
}
string piece::getcolor() const {
    return color;
}
// --- pawn ---
pawn::pawn(const string& c, char s) : piece(c, s) {}
string pawn::getunicode() const {
    return (color == "white") ? "P" : "p";
}
bool pawn::isvalidmove(int fromx, int fromy, int tox, int toy) const {
    int dir = (color == "white") ? -1 : 1;
    int dx = tox - fromx;
    int dy = toy - fromy;
    if (dx == dir && dy == 0) return true;
    if (dx == 2 * dir && dy == 0) {
        if ((color == "white" && fromx == 6) || (color == "black" && fromx == 1)) {
            return true;
        }
    }
    if (dx == dir && (dy == 1 || dy == -1)) return true;
    return false;
}
// --- rook ---
rook::rook(const string& col, char sym) : piece(col, sym) {}
string rook::getunicode() const {
    return (color == "white") ? "R" : "r";
}
bool rook::isvalidmove(int fromx, int fromy, int tox, int toy) const {
    if (fromx == tox || fromy == toy) {
        return true;
    }
    return false;
}
// --- bishop ---
bishop::bishop(const string& col, char sym) : piece(col, sym) {}
string bishop::getunicode() const {
    return (color == "white") ? "B" : "b";
}
bool bishop::isvalidmove(int fromx, int fromy, int tox, int toy) const {
    int dx = abs(tox - fromx);
    int dy = abs(toy - fromy);
    return (dx == dy && dx != 0);
}
// --- knight ---
knight::knight(const string& col, char sym) : piece(col, sym) {}
string knight::getunicode() const {
    return (color == "white") ? "N" : "n";
}
bool knight::isvalidmove(int fromx, int fromy, int tox, int toy) const {
    int dx = abs(tox - fromx);
    int dy = abs(toy - fromy);
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}
// --- queen ---
queen::queen(const string& col, char sym) : piece(col, sym) {}
string queen::getunicode() const {
    return (color == "white") ? "Q" : "q";
}
bool queen::isvalidmove(int fromx, int fromy, int tox, int toy) const {
    int dx = abs(tox - fromx);
    int dy = abs(toy - fromy);
    return (dx == dy && dx != 0) || (fromx == tox || fromy == toy);
}
// --- king ---
king::king(const string& col, char sym) : piece(col, sym) {}
string king::getunicode() const {
    return (color == "white") ? "K" : "k";
}
bool king::isvalidmove(int fromx, int fromy, int tox, int toy) const {
    int dx = abs(tox - fromx);
    int dy = abs(toy - fromy);
    return (dx <= 1 && dy <= 1 && (dx + dy > 0));
}
