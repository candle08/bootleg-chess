module Gameplay;

import Coords;
import Link;

import <vector>;
import <string>;
import <iostream>;

using namespace std;

Scan::Scan(): Ability{'S'} {}

string Scan::usePower(Board &b, vector<char> args, Player * p) {
    //debug
    // cerr << "Scan called\n";
    // // Setting revealed to true, thereby revealing the type and strength on board
    // if (link1) {
    //     link1->revealed = true;
    //     return "";
    // } else {
    //     return "error, link1 is a nullptr in SCAN";
    // }

    return "";
}
