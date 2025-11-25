module Scan;
import Board;
import Coords;
import Link;

import <algorithm>;
import <vector>;

string Scan::usePower(Board & b, Coords & b, Link * link1, Link * link2, Player * p) override {
    // setting revealed to true, thereby revealing the type and strength on board
    link1->revealed = true;

    // iterates through abilities and deletes that ability
    p->abilities.erase(find(p->abilities.begin(), p->abilities.end(), this));
}