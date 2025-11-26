module Download;

import Coords;
import Gameplay;
import Link;

import <string>;

using namespace std;

string Download::usePower(Board & b, Coords & c, Link * link1, Link * link2, Player * p) {
    p->download(link1, b);
    return "";
}