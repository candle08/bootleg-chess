module Gameplay;

import Coords;
import Link;

import <string>;
import <iostream>;

using namespace std;

SmallSwap::SmallSwap(): Ability{'W'} {}

string SmallSwap::usePower(Board & b, Coords & c, Link * link1, Link * link2, Player * p) {
    //debug
    cerr << "Scan called";
    swap(link1, link2);
    return "";
}
