export module LinkBoost;

import Coords;
import Gameplay;
import Link;

using namespace std;

export class LinkBoost : public Ability {
    public:
        LinkBoost();
        string usePower(Board &b, Coords &c, Link* link1, Link* link2, Player * p) override;

};
