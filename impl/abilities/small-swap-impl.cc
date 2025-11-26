module SmallSwap;

import Coords;
import Gameplay;
import Link;

using namespace std;

string SmallSwap::usePower(Board & b, Coords & b, Link * link1, Link * link2, Player * p) override {
    swap(link1, link2);
    return "";
}