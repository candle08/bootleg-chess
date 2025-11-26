module Gameplay;

import Coords;
import Link;

import <string>;

using namespace std;

Scan::Scan(): Ability{'S'} {}

string Scan::usePower(Board & b, Coords & c, Link * link1, Link * link2, Player * p) {
    // Setting revealed to true, thereby revealing the type and strength on board
    if (link1) {
        link1->revealed = true;
        return "";
    } else {
        return "error, link1 is a nullptr in SCAN";
    }


}
