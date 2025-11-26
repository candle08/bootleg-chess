module Gameplay;

import Coords;
import Link;

import <vector>;
import <string>;
import <iostream>;

using namespace std;

Firewall::Firewall(): Ability{'F'} {}

string Firewall::usePower(Board &b, Coords &c, Link* link1, Link* link2, Player * p) {
    //debug
    cerr << "firewall called\n";
    // Check if cell is empty
    
    cerr << "in firewall, checking if cell is empty\n";
    if (b.board[c.r][c.c].item != b.EMPTY) {
        return "Selected cell is not empty";
        //debut
    }
    cerr << "setting up a firewall on the coordinate";

    // Setting firewall on given coordinate
    b.board[c.r][c.c].firewall = true;
    b.board[c.r][c.c].player = p->id;
    return "";
}
