export module SmallSwap;

import Coords;
import Gameplay;
import Link;

using namespace std;

export class SmallSwap : public Ability {
    public:
        SmallSwap();
        string usePower(Board &b, Coords &c, Link* link1, Link* link2, Player * p) override;
};
