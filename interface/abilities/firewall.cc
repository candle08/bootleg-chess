export module Firewall;

import Board;
import Coords;
import Ability;
import Player;

using namespace std;

export class Firewall : public Ability {
    public:
        Firewall();
        string usePower(Board &b, Coords &c, Link* link) override;

};
