module Gameplay;

import Coords;
import Link;

import <string>;

using namespace std;

LinkBoost::LinkBoost(): Ability{'L'} {}

string LinkBoost::usePower(Board &b, Coords &c, Link* link1, Link* link2, Player * p) {
    if (link1->linkboost) {
        cerr << "failed in Linkbook, checking if the link has already used the linkboost";
        return "already linkboosted pick another link";
    } else {
        link1->linkboost = true;
    }
    return "";
}
