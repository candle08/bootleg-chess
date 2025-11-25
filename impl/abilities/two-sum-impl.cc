module TwoSum;

import Board;
import Link;
import Coords;
import Player;

using namespace std;

string SmallSum::usePower(Board & b, Coords & b, Link * link1, Link * link2, Player * p) override {
    if (link1) {
        link1->freeze += link1->level; // since we don't know if this is their first or second time using two-sum
        return "";
    } else {
        return "link1 nullptr gg";
    }
}
