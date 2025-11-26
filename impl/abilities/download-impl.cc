module Gameplay;

import Coords;
import Link;
import <iostream>;

import <string>;

using namespace std;

Download::Download(): Ability{'D'} {}

string Download::usePower(Board & b, Coords & c, Link * link1, Link * link2, Player * p) {
    p->download(link1, b);

    // debug
    cerr << "in download";
    return "";
}
