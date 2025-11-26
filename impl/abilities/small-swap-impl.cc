module SmallSwap;

import Coords;
import Gameplay;
import Link;

import <string>;

using namespace std;

string SmallSwap::usePower(Board & b, Coords & c, Link * link1, Link * link2, Player * p) {
    swap(link1, link2);
    return "";
}