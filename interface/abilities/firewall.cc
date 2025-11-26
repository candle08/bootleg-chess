export module Firewall;

import Coords;
import Gameplay;
import Link;

import <string>;

using namespace std;

export class Firewall : public Ability {
    public:
        string usePower(Board &b, Coords &c, Link* link1, Link* link2, Player * p) override;

};
