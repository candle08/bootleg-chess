module TwoSum;

import Coords;
import Gameplay;
import Link;


string TwoSum::usePower(Board & b, Coords & b, Link * link1, Link * link2, Player * p) override {
    if (link1) {
        link1->frozen_on_turn = turn_number;
        return "";
    } else {
        return "link1 nullptr gg";
    }
}
