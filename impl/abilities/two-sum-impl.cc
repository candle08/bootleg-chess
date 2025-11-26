module Gameplay;

import Coords;
import Link;

import <string>;

using namespace std;

TwoSum::TwoSum(): Ability{'T'} {}

string TwoSum::usePower(Board & b, Coords & c, Link * link1, Link * link2, Player * p) {
    if (link1) {
        link1->frozen_on_turn = b.turn_number;
        return "";
    } else {
        return "link1 nullptr gg";
    }
}
