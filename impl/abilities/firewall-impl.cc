module Firewall;

import Coords;
import Gameplay;
import Link;

import vector;

using namespace std;

string Firewall::usePower(Board &b, Coords &c, Link* link1, Link* link2, Player * p) override {
    // check if cell is empty
    if (b.board[c.r][c.c].item != b.EMPTY) {
        return "Selected cell is not empty";
    }
    // setting firewall on given coordinate
    b[c.r][c.c]->firewall = true;
    b[c.r][c.c]->player = p->id;
    return "";
}
