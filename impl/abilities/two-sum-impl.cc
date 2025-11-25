module TwoSum;

import Board;
import Link;
import Coords;
import Player;

using namespace std;

string TwoSum::usePower(Board & b, Coords & b, Link * link1, Link * link2, Player * p) override {
    if (link1) {
        link1->frozen_on_turn = turn_number;
        return "";
    } else {
        return "link1 nullptr gg";
    }
}
