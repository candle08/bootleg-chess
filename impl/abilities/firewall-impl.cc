module Gameplay;

import Coords;
import Link;

import <vector>;
import <string>;
import <iostream>;

using namespace std;

Firewall::Firewall(): Ability{'F'} {}

string Firewall::usePower(Board &b, vector<char> args, Player * p) {
    //debug
    cerr << "firewall called\n";
    // Check if cell is empty
    
    if (args.size() != 2) {
        return "Invalid input for Firewall: invalid number of args";
    }

    int r = args[0] - '0', c = args[1] - '1';

    cerr << "in firewall, checking if cell is empty\n";
    if (b.board[r][c].item != b.EMPTY) {
        return "Selected cell is not empty";
        //debut
    }
    cerr << "setting up a firewall on the coordinate";

    // Setting firewall on given coordinate
    b.board[r][c].firewall = true;
    b.board[r][c].player = p->id;
    return "";
}
