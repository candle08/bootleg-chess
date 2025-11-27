module Gameplay;

import Coords;
import Link;

import <string>;
import <vector>;
import <iostream>;

using namespace std;

LinkBoost::LinkBoost(): Ability{'L'} {}

string LinkBoost::usePower(Board &b, vector<char> args, Player * p) {
    // debug
    cerr << "linkboost called\n";
    cerr << "in Linkbook, checking if the link has already used the linkboost\n";

    if (args.size() != 1) {
        return "Invalid input in LinkBoost: invalid number of args";
    }

    Link* link_ptr = p->getLinkPointerFromChar(args[0]);

    if (link_ptr->linkboost) {
        // debug
        return "already linkboosted pick another link";
    } else {
        link_ptr->linkboost = true;
    }
    return "";
}
