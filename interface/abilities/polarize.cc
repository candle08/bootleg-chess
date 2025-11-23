export module Polarize;

import Board;
import Coords;
import Ability;
import Player;

using namespace std;

export class Polarize : public Ability {
    string name;
    public:
    usePower(Player & p1, Player &p2, Board & b, Coords c);

};
