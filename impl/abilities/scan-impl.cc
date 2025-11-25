module Scan;
import Board;
import Coords;
import Link;

string Scan::userPower(Board & b, Coords & b, Link * link) override {
    link->revealed = true;
}