module Download;

import Coords;
import Gameplay;
import Link;

string Download::usePower(Board & b, Coords & b, Link * link1, Link * link2, Player * p) override {
    p->download(link1);
    return "";
}