module Firewall;

import Coords;
import Gameplay;
import Link;

import <vector>;
import <string>;

using namespace std;

string Firewall::usePower(Board &b, Coords &c, Link* link1, Link* link2, Player * p) {
    // check if cell is empty
    if (b.board[c.r][c.c].item != b.EMPTY) {
        return "Selected cell is not empty";
    }
    // setting firewall on given coordinate
    b.board[c.r][c.c].firewall = true;
    b.board[c.r][c.c].player = p->id;
    return "";
}
