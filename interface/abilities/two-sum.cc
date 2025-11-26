export module TwoSum;

import Coords;
import Gameplay;
import Link;

using namespace std;

export class TwoSum : public Ability {
    public:
        TwoSum();
        string usePower(Board &b, Coords &c, Link* link1, Link* link2, Player * p) override;
};
