module Gameplay;

import Coords;
import Link;

import <vector>;
import <string>;
import <iostream>;

using namespace std;

SmallSwap::SmallSwap(): Ability{'W'} {}

string SmallSwap::usePower(Board &b, vector<char> args, Player * p) {
    //debug
    cerr << "small swap called\n";

    if (args.size() != 2) {
        return "Invalid input for SmallSwap: invalid number of arguments";
    }

    char symbol1 = args[0];
    char symbol2 = args[1];
    Link* link1 = b.getLinkPointerFromChar(symbol1);
    Link* link2 = b.getLinkPointerFromChar(symbol2);


    if (link1 == nullptr || link2 == nullptr) {
        return "Error in SmallSwap: link not found";
    }

    swap(*link1, *link2);
    return "";
}
