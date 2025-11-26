module LinkBoost;

import Coords;
import Gameplay;
import Link;

import <string>;

using namespace std;

string LinkBoost::usePower(Board &b, Coords &c, Link* link1, Link* link2, Player * p) {
    if (link1->linkboost) {
        return "already linkboosted pick another link";
    } else {
        link1->linkboost = true;
    }
    return "";
}
