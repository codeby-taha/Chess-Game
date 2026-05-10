#include "ui.h"
int main() {
    game g;
    while (true) {
        showmainmenu();
        char ch;
        cin >> ch;
        if (ch == '1') {
            clearscreen();
            cout << endl << "  White player ka naam: ";
            cin >> g.whitename;
            cout << "  Black player ka naam: ";
            cin >> g.blackname;
            g.startgame();
            g.gameloop();
        }
        else if (ch == '2') {
            cout << endl << "  File ka naam: ";
            string fn; cin >> fn;
            if (g.loadnames(fn)) {
                cout << "  Load ho gaya! Enter dabao..." << endl;
                string tmp; cin.ignore(); getline(cin, tmp);
            }
            else {
                cout << "  Load nahi hua." << endl;
                string tmp; cin.ignore(); getline(cin, tmp);
            }
        }
        else if (ch == '3') {
            showhowtoplay();
        }
        else if (ch == '4') {
            clearscreen();
            g.displayleaderboard();
            cout << endl << "Enter dabao...";
            string tmp; cin.ignore(); getline(cin, tmp);
        }
        else if (ch == '5') {
            clearscreen();
            g.displaystats();
            cout << endl << "Enter dabao...";
            string tmp; cin.ignore(); getline(cin, tmp);
        }
        else if (ch == '6') {
            cout << endl << "  Allah Hafiz!" << endl << endl;
            break;
        }
    }
    return 0;
}
