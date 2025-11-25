module Scan;
import Board;
import Coords;
import Link;

import <algorithm>;
import <vector>;

string DoubleDown::usePower(Board & b, Coords & b, Link * link1, Link * link2, Player * p) override {
    // setting revealed to true, thereby revealing the type and strength on board
    b.double_down = true;

    return "";
}