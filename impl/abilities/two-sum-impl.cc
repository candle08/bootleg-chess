module Gameplay;

import Coords;
import Link;

import <string>;
import <iostream>;
import <vector>;

using namespace std;

TwoSum::TwoSum(): Ability{'T'} {}

string TwoSum::usePower(Board &b, vector<char> args, Player * p) {
    //debug
    
    cerr << "two sum called\n";
    if (args.size() != 1) {
        return "Invalid input for TwoSum: invalid number of args";
    }

    char symbol = args[0];
    Link* link_ptr = b.getLinkPointerFromChar(symbol);
    if (link_ptr != nullptr) {
        link_ptr->frozen_on_turn = b.turn_number;
        return "";
    }

    return "Error in TwoSum: link not found for symbol";
}
