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
    if (Board::DEBUG) cerr << "Scan called\n";

    if (args.size() != 1) {
        return "Invalid input for Scan: invalid number of arguments";
    }
    
    // find link with symbol
    char symbol = args[0];
    Link* link_ptr = b.getLinkPointerFromChar(symbol);

    if (link_ptr != nullptr) {
        link_ptr->revealed = true;
        return "";
    }
    return "Invalid input in scan: link not found";
}
