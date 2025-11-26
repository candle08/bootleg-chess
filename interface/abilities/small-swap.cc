export module SmallSwap;

import Coords;
import Gameplay;
import Link;

import <string>;

using namespace std;

export class SmallSwap : public Ability {
    public:
        string usePower(Board &b, Coords &c, Link* link1, Link* link2, Player * p) override;
};
