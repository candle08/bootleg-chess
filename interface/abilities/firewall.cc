export module Firewall;

import Board;
import Coords;
import Ability;
import Player;

using namespace std;

export class Firewall : public Ability {
    public:
        Firewall();
        bool usePower(Player & p1, Player &p2, Board & b, Coords c) override;

};
