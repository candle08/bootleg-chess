module Gameplay;

import Coords;
import Link;

import <iostream>;
import <vector>;
import <string>;
using namespace std;
DoubleDown::DoubleDown(): Ability{'B'} {}

string DoubleDown::usePower(Board &b, vector<char> args, Player * p) {
    //debug
    if (Board::DEBUG) cerr << "double down called\n";

    if (args.size() != 0) {
        return "Invalid input for Firewall: invalid number of args";
    }

    b.double_down = true;

    return "";
}
