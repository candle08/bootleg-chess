export module Scan;

import Board;
import Coords;
import Ability;
import Player;

using namespace std;

export class Scan : public Ability {
    public:
        Scan();
        string usePower(Board &b, Coords &c, Link* link) override;

};
