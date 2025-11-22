export module Download;

import Board;
import Coords;
import Ability;
import Player;

export class Download : public Ability {
    string name;
    public:
    use_power(Player & p1, Player &p2, Board & b, Coords c);

};
