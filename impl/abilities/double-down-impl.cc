module Scan;
import Board;
import Coords;
import Link;

import <algorithm>;
import <vector>;

string DoubleDown::usePower(Board & b, Coords & b, Link * link1, Link * link2, Player * p) override {
    // setting double_down to be true so that Board::move() knows to decrement turn_number by 1
    b.double_down = true;

    return "";
}