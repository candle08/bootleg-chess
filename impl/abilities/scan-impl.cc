module Scan;

import Gameplay;
import Coords;
import Link;

string Scan::usePower(Board & b, Coords & b, Link * link1, Link * link2, Player * p) override {
    // setting revealed to true, thereby revealing the type and strength on board
    if (link1) {
        link1->revealed = true;
        return "";
    } else {
        return "error, link1 is a nullptr";
    }


}