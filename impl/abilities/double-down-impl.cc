module Gameplay;

import Coords;
import Link;
import <iostream>;

import <string>;
using namespace std;
DoubleDown::DoubleDown(): Ability{'B'} {}

string DoubleDown::usePower(Board & b, Coords & c, Link * link1, Link * link2, Player * p) {
    //debug
    cerr << "double down called";
    // setting double_down to be true so that Board::move() knows to decrement turn_number by 1
    b.double_down = true;
    

    return "";
}