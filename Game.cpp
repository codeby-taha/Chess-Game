#include "game.h"
#include <cstdlib>
game::game() {
    whitename = "White";
    blackname = "Black";
    lastfromx = lastfromy = lasttox = lasttoy = -1;
    haslastmove = false;
    legalcount = 0;
    gameover = false;
    paused = false;
    whitewins = whitelosses = whitedraws = 0;
    blackwins = blacklosses = blackdraws = 0;
    whiteturn = true;
}
void game::startgame() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            if (chessboard.squares[i][j]) {
                delete chessboard.squares[i][j];
                chessboard.squares[i][j] = nullptr;
            }
        }
    chessboard.placepiece(new rook("black", 'r'), 0, 0);
    chessboard.placepiece(new knight("black", 'n'), 0, 1);
    chessboard.placepiece(new bishop("black", 'b'), 0, 2);
    chessboard.placepiece(new queen("black", 'q'), 0, 3);
    chessboard.placepiece(new king("black", 'k'), 0, 4);
    chessboard.placepiece(new bishop("black", 'b'), 0, 5);
    chessboard.placepiece(new knight("black", 'n'), 0, 6);
    chessboard.placepiece(new rook("black", 'r'), 0, 7);
    for (int j = 0; j < 8; j++)
        chessboard.placepiece(new pawn("black", 'p'), 1, j);
    for (int j = 0; j < 8; j++)
        chessboard.placepiece(new pawn("white", 'P'), 6, j);
    chessboard.placepiece(new rook("white", 'R'), 7, 0);
    chessboard.placepiece(new knight("white", 'N'), 7, 1);
    chessboard.placepiece(new bishop("white", 'B'), 7, 2);
    chessboard.placepiece(new queen("white", 'Q'), 7, 3);
    chessboard.placepiece(new king("white", 'K'), 7, 4);
    chessboard.placepiece(new bishop("white", 'B'), 7, 5);
    chessboard.placepiece(new knight("white", 'N'), 7, 6);
    chessboard.placepiece(new rook("white", 'R'), 7, 7);
    whiteturn = true;
    haslastmove = false;
    legalcount = 0;
    gameover = false;
    paused = false;
    movehistory.clear();
    whitecaptured.clear();
    blackcaptured.clear();
}
bool game::findking(const string& col, int& kx, int& ky) const {
    char sym = (col == "white") ? 'K' : 'k';
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            piece* p = chessboard.getpiece(i, j);
            if (p && p->getsymbol() == sym) {
                kx = i; ky = j;
                return true;
            }
        }
    return false;
}
bool game::iskingcheck(const string& col) {
    int kx, ky;
    if (!findking(col, kx, ky)) return false;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            piece* p = chessboard.getpiece(i, j);
            if (p && p->getcolor() != col) {
                if (p->isvalidmove(i, j, kx, ky)) {
                    rook* rok = dynamic_cast<rook*>(p);
                    bishop* bp = dynamic_cast<bishop*>(p);
                    queen* qn = dynamic_cast<queen*>(p);
                    if (rok) {
                        if (!chessboard.ispathclear(i, j, kx, ky)) continue;
                    }
                    if (bp) {
                        if (!chessboard.isdiagonalclear(i, j, kx, ky)) continue;
                    }
                    if (qn) {
                        int dx = abs(kx - i);
                        int dy = abs(ky - j);
                        if (i == kx || j == ky) {
                            if (!chessboard.ispathclear(i, j, kx, ky)) continue;
                        }
                        else if (dx == dy) {
                            if (!chessboard.isdiagonalclear(i, j, kx, ky)) continue;
                        }
                    }
                    return true;
                }
            }
        }
    return false;
}
game::movebackup game::simulatemove(int fromx, int fromy, int tox, int toy) {
    movebackup b;
    b.movedpiece = chessboard.squares[fromx][fromy];
    b.capturedpiece = chessboard.squares[tox][toy];
    chessboard.squares[tox][toy] = chessboard.squares[fromx][fromy];
    chessboard.squares[fromx][fromy] = nullptr;
    return b;
}
void game::undomove(int fromx, int fromy, int tox, int toy, movebackup b) {
    chessboard.squares[fromx][fromy] = b.movedpiece;
    chessboard.squares[tox][toy] = b.capturedpiece;
}
bool game::islegalmove(int fromx, int fromy, int tox, int toy) {
    piece* p = chessboard.getpiece(fromx, fromy);
    if (!p) return false;
    piece* target = chessboard.getpiece(tox, toy);
    if (target && target->getcolor() == p->getcolor()) return false;
    if (!p->isvalidmove(fromx, fromy, tox, toy)) return false;
    movebackup b = simulatemove(fromx, fromy, tox, toy);
    bool incheck = iskingcheck(p->getcolor());
    undomove(fromx, fromy, tox, toy, b);
    return !incheck;
}
void game::getlegalmoves(int fromx, int fromy) {
    legalcount = 0;
    piece* p = chessboard.getpiece(fromx, fromy);
    if (!p) return;
    for (int tx = 0; tx < 8; tx++)
        for (int ty = 0; ty < 8; ty++) {
            if (tx == fromx && ty == fromy) continue;
            if (islegalmove(fromx, fromy, tx, ty)) {
                if (legalcount < 30) {
                    legalhx[legalcount] = tx;
                    legalhy[legalcount] = ty;
                    legalcount++;
                }
            }
        }
}
bool game::hasanylegal(const string& col) {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            piece* p = chessboard.getpiece(i, j);
            if (p && p->getcolor() == col) {
                int saved_lhx[30], saved_lhy[30], saved_lc = legalcount;
                for (int x = 0; x < legalcount; x++) { saved_lhx[x] = legalhx[x]; saved_lhy[x] = legalhy[x]; }
                getlegalmoves(i, j);
                int found = legalcount;
                legalcount = saved_lc;
                for (int x = 0; x < legalcount; x++) { legalhx[x] = saved_lhx[x]; legalhy[x] = saved_lhy[x]; }
                if (found > 0) return true;
            }
        }
    return false;
}
bool game::ischeckmate(const string& col) {
    if (!iskingcheck(col)) return false;
    return !hasanylegal(col);
}
bool game::isstalemate(const string& col) {
    if (iskingcheck(col)) return false;
    return !hasanylegal(col);
}
void game::promotepawn(int row, int col, const string& color) {
    cout << endl << "  *** Pawn Promotion! Choose piece ***" << endl;
    cout << "  [Q] Queen   [R] Rook" << endl;
    cout << "  [B] Bishop  [N] Knight" << endl;
    cout << "  Your choice: ";
    char ch;
    cin >> ch;
    ch = toupper(ch);
    piece* newpiece = nullptr;
    if (ch == 'Q')
        newpiece = new queen(color, color == "white" ? 'Q' : 'q');
    else if (ch == 'R')
        newpiece = new rook(color, color == "white" ? 'R' : 'r');
    else if (ch == 'B')
        newpiece = new bishop(color, color == "white" ? 'B' : 'b');
    else
        newpiece = new knight(color, color == "white" ? 'N' : 'n');
    delete chessboard.squares[row][col];
    chessboard.squares[row][col] = newpiece;
}
bool game::trycastling(int fromx, int fromy, int tox, int toy) {
    piece* k = chessboard.getpiece(fromx, fromy);
    if (!k) return false;
    king* kg = dynamic_cast<king*>(k);
    if (!kg) return false;
    if (kg->hasmoved) return false;
    if (fromx != tox || abs(toy - fromy) != 2) return false;
    int rookcol = (toy > fromy) ? 7 : 0;
    piece* r = chessboard.getpiece(fromx, rookcol);
    rook* rk = dynamic_cast<rook*>(r);
    if (!rk || rk->hasmoved) return false;
    if (!chessboard.ispathclear(fromx, fromy, fromx, rookcol)) return false;
    if (iskingcheck(k->getcolor())) return false;
    int newkingcol = toy;
    int newrookcol = (toy > fromy) ? toy - 1 : toy + 1;
    chessboard.squares[fromx][newkingcol] = k;
    chessboard.squares[fromx][fromy] = nullptr;
    chessboard.squares[fromx][newrookcol] = r;
    chessboard.squares[fromx][rookcol] = nullptr;
    k->hasmoved = true;
    r->hasmoved = true;
    return true;
}
int game::colfromchar(char c) {
    return c - 'a';
}
int game::rowfromchar(char c) {
    return 8 - (c - '0');
}
void game::displaycaptured() {
    cout << endl;
    cout << whitename << " captured: ";
    for (int i = 0; i < whitecaptured.count; i++)
        cout << whitecaptured.get(i) << " ";
    cout << endl;
    cout << blackname << " captured: ";
    for (int i = 0; i < blackcaptured.count; i++)
        cout << blackcaptured.get(i) << " ";
    cout << endl;
}
void game::displayhistory() {
    cout << endl << "=== Move History ===" << endl;
    for (int i = 0; i < movehistory.count; i++) {
        if (i % 2 == 0)
            cout << (i / 2 + 1) << ". ";
        cout << movehistory.data[i].from << movehistory.data[i].to << " ";
        if (i % 2 == 1)
            cout << endl;
    }
    cout << endl;
}
void game::savenames(const string& filename) {
    ofstream f(filename.c_str());
    if (!f) { cout << "File open nahi ho sakti!" << endl; return; }
    f << whitename << endl << blackname << endl;
    f.close();
    cout << "Names save ho gaye: " << filename << endl;
}
bool game::loadnames(const string& filename) {
    ifstream f(filename.c_str());
    if (!f) { cout << "File nahi mili!" << endl; return false; }
    getline(f, whitename);
    getline(f, blackname);
    f.close();
    cout << "Names load ho gaye: " << filename << endl;
    return true;
}
void game::displaystats() {
    cout << endl << "=== Player Stats ===" << endl;
    cout << whitename << ": Wins=" << whitewins << " Losses=" << whitelosses << " Draws=" << whitedraws << endl;
    cout << blackname << ": Wins=" << blackwins << " Losses=" << blacklosses << " Draws=" << blackdraws << endl;
}
void game::displayleaderboard() {
    cout << endl << "=== Leaderboard ===" << endl;
    int wscore = whitewins * 3 + whitedraws;
    int bscore = blackwins * 3 + blackdraws;
    if (wscore >= bscore) {
        cout << "1. " << whitename << " - Score: " << wscore << endl;
        cout << "2. " << blackname << " - Score: " << bscore << endl;
    }
    else {
        cout << "1. " << blackname << " - Score: " << bscore << endl;
        cout << "2. " << whitename << " - Score: " << wscore << endl;
    }
}
void game::playturn(const string& from, const string& to) {
    if (from.size() < 2 || to.size() < 2) {
        cout << "Input galat hai! Example: e2 e4" << endl;
        return;
    }
    int fromcol = colfromchar(from[0]);
    int fromrow = rowfromchar(from[1]);
    int tocol = colfromchar(to[0]);
    int torow = rowfromchar(to[1]);
    if (fromcol < 0 || fromcol >= 8 || fromrow < 0 || fromrow >= 8 ||
        tocol < 0 || tocol >= 8 || torow < 0 || torow >= 8) {
        cout << "Board ke bahar hai!" << endl;
        return;
    }
    piece* p = chessboard.getpiece(fromrow, fromcol);
    if (!p) {
        cout << from << " par koi piece nahi hai!" << endl;
        return;
    }
    if ((whiteturn && p->getcolor() != "white") ||
        (!whiteturn && p->getcolor() != "black")) {
        cout << "Abhi aap ki baari nahi hai!" << endl;
        return;
    }
    getlegalmoves(fromrow, fromcol);
    bool castled = false;
    if (dynamic_cast<king*>(p) && abs(tocol - fromcol) == 2 && torow == fromrow) {
        castled = trycastling(fromrow, fromcol, torow, tocol);
        if (!castled) {
            cout << "Castling nahi ho sakti!" << endl;
            legalcount = 0;
            return;
        }
    }
    if (!castled) {
        if (!islegalmove(fromrow, fromcol, torow, tocol)) {
            cout << "Illegal move - king check mein aa jayega!" << endl;
            legalcount = 0;
            return;
        }
        piece* target = chessboard.getpiece(torow, tocol);
        if (target) {
            if (p->getcolor() == "white")
                whitecaptured.add(target->getunicode());
            else
                blackcaptured.add(target->getunicode());
        }
        if (!chessboard.movepiece(fromrow, fromcol, torow, tocol)) {
            cout << "Move nahi ho saka!" << endl;
            legalcount = 0;
            return;
        }
    }
    moverecord mr;
    mr.from = from;
    mr.to = to;
    mr.piecesym = p->getsymbol();
    mr.piececol = p->getcolor();
    movehistory.add(mr);
    piece* np = chessboard.getpiece(torow, tocol);
    if (np) {
        pawn* pw = dynamic_cast<pawn*>(np);
        if (pw) {
            if ((pw->getcolor() == "white" && torow == 0) ||
                (pw->getcolor() == "black" && torow == 7)) {
                promotepawn(torow, tocol, pw->getcolor());
            }
        }
    }
    lastfromx = fromrow; lastfromy = fromcol;
    lasttox = torow;     lasttoy = tocol;
    haslastmove = true;
    legalcount = 0;
    cout << "Move ho gaya!" << endl;
    whiteturn = !whiteturn;
}
void game::showingamemenu() {
    cout << endl << "=== Game Menu ===" << endl;
    cout << "[1] Resume" << endl;
    cout << "[2] Save Names" << endl;
    cout << "[3] Move History" << endl;
    cout << "[4] Stats" << endl;
    cout << "[5] Resign" << endl;
    cout << "[6] Offer Draw" << endl;
    cout << "[7] Main Menu par jao" << endl;
    cout << "Choice: ";
    char ch;
    cin >> ch;
    if (ch == '1') {
        paused = false;
    }
    else if (ch == '2') {
        cout << "Filename: ";
        string fn; cin >> fn;
        savenames(fn);
    }
    else if (ch == '3') {
        displayhistory();
        cout << "Enter dabao...";
        string tmp; cin.ignore(); getline(cin, tmp);
    }
    else if (ch == '4') {
        displaystats();
        cout << "Enter dabao...";
        string tmp; cin.ignore(); getline(cin, tmp);
    }
    else if (ch == '5') {
        string resigned = whiteturn ? whitename : blackname;
        cout << endl << resigned << " ne resign kar diya!" << endl;
        if (whiteturn) { blackwins++; whitelosses++; }
        else { whitewins++; blacklosses++; }
        gameover = true;
    }
    else if (ch == '6') {
        string other = !whiteturn ? whitename : blackname;
        cout << endl << "Draw offer " << other << " ko gaya. Accept? (y/n): ";
        char ans; cin >> ans;
        if (ans == 'y' || ans == 'Y') {
            cout << "Draw accept ho gaya!" << endl;
            whitedraws++; blackdraws++;
            gameover = true;
        }
        else {
            cout << "Draw decline ho gaya." << endl;
        }
    }
    else if (ch == '7') {
        gameover = true;
    }
}
void game::gameloop() {
    while (!gameover) {
        string curcolor = whiteturn ? "white" : "black";
        string curname = whiteturn ? whitename : blackname;
        if (ischeckmate(curcolor)) {
            clearscreen();
            string winner = whiteturn ? blackname : whitename;
            chessboard.displayboard();
            cout << endl << "*** CHECKMATE! " << winner << " jeet gaya! ***" << endl;
            if (whiteturn) { blackwins++; whitelosses++; }
            else { whitewins++; blacklosses++; }
            break;
        }
        if (isstalemate(curcolor)) {
            clearscreen();
            chessboard.displayboard();
            cout << endl << "*** STALEMATE! Draw! ***" << endl;
            whitedraws++; blackdraws++;
            break;
        }
        clearscreen();
        int checkkingx = -1, checkkingy = -1;
        if (iskingcheck(curcolor)) {
            findking(curcolor, checkkingx, checkkingy);
            cout << endl << "*** CHECK! ***" << endl;
        }
        int lhx[30], lhy[30];
        for (int x = 0; x < legalcount; x++) { lhx[x] = legalhx[x]; lhy[x] = legalhy[x]; }
        chessboard.displayboard(
            checkkingx, checkkingy,
            haslastmove ? lastfromx : -1,
            haslastmove ? lastfromy : -1,
            haslastmove ? lasttox : -1,
            haslastmove ? lasttoy : -1,
            lhx, lhy, legalcount
        );
        displaycaptured();
        cout << endl << "  " << curname << " ki baari (" << curcolor << ")" << endl;
        cout << "  Move likhein (e.g. e2 e4) ya 'menu' ya 'exit': ";
        string from, to;
        cin >> from;
        if (from == "menu") {
            showingamemenu();
            continue;
        }
        if (from == "exit") {
            break;
        }
        cin >> to;
        playturn(from, to);
    }
    displaystats();
    displayleaderboard();
    cout << endl << "Enter dabao...";
    string tmp; cin.ignore(); getline(cin, tmp);
}