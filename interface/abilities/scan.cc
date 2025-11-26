export module Scan;

import Coords;
import Gameplay;
import Link;

import <string>;

using namespace std;

export class Scan : public Ability {
    public:
        string usePower(Board &b, Coords &c, Link* link1, Link* link2, Player * p) override;
};
