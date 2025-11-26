module Gameplay;

import Coords;
import Link;

import <string>;

using namespace std;

Download::Download(): Ability{'D'} {}

string Download::usePower(Board & b, Coords & c, Link * link1, Link * link2, Player * p) {
    p->download(link1, b);
    return "";
}
