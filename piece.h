#pragma once
#           ifndef PIECE_H
#define PIECE_H
#include <string>
using namespace std;
// base class for all chess pieces
class piece {
protected:
    string color;
    char symbol;
public:
    bool hasmoved;
    piece(string c, char s);
    virtual ~piece();
    virtual char getsymbol() const;
    virtual string getunicode() const;
    virtual bool isvalidmove(int fromx, int fromy, int tox, int toy) const = 0;
    string getcolor() const;
};
// pawn piece
class pawn : public piece {
public:
    pawn(const string& c, char s);
    string getunicode() const override;
    bool isvalidmove(int fromx, int fromy, int tox, int toy) const override;
};
// rook piece
class rook : public piece {
public:
    rook(const string& col, char sym);
    string getunicode() const override;
    bool isvalidmove(int fromx, int fromy, int tox, int toy) const override;
};
// bishop piece
class bishop : public piece {
public:
    bishop(const string& col, char sym);
    string getunicode() const override;
    bool isvalidmove(int fromx, int fromy, int tox, int toy) const override;
};
// knight piece
class knight : public piece {
public:
    knight(const string& col, char sym);
    string getunicode() const override;
    bool isvalidmove(int fromx, int fromy, int tox, int toy) const override;
};
// queen piece
class queen : public piece {
public:
    queen(const string& col, char sym);
    string getunicode() const override;
    bool isvalidmove(int fromx, int fromy, int tox, int toy) const override;
};
// king piece
class king : public piece {
public:
    king(const string& col, char sym);
    string getunicode() const override;
    bool isvalidmove(int fromx, int fromy, int tox, int toy) const override;
};
#endif