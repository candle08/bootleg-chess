export module LinkBoost;

import Ability;
import Board;
import Coords;
import Player;

using namespace std;

export class LinkBoost : public Ability {
    string name;
    public:
    use_power(Player & p1, Player &p2, Board & b, Coords c);

};
