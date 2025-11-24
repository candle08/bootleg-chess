export module LinkBoost;

import Ability;
import Board;
import Coords;
import Player;

using namespace std;

export class LinkBoost : public Ability {
    public:
        LinkBoost();
        string usePower(Board &b, Coords &c, Link* link) override;

};
