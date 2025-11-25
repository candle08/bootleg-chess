export module Polarize;

import Board;
import Coords;
import Ability;
import Player;

using namespace std;

export class Polarize : public Ability {
    public:
        string usePower(Board &b, Coords &c, Link* link1, Link* link2, Player * p) override;
};
