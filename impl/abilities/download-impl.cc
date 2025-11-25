module Download;

import Board;
import Coords;
import Link;

import <vector>;

string Download::usePower(Board & b, Coords & b, Link * link1, Link * link2, Player * p) override {
    p->download(link1);
    return "";
}