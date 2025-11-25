module Firewall;

import Board;
import Coords;
import Ability;
import Player;

using namespace std;

string Firewall::usePower(Board &b, Coords &c, Link* link1, Link* link2, Player * p) override {
    // setting firewall on given coordinate
    b[c.r][c.c]->firewall = true;
    b[c.r][c.c]->player = p->id;

    return "";
}
