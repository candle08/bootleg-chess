export module Firewall;

import Board;
import Coords;
import Ability;
import Player;

export class Firewall : public Ability {
    string name;
    public:
    use_power(Player & p1, Player &p2, Board & b, Coords c);

};
