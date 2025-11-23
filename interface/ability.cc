export module Ability;

import Player;
import Board;
import Coords;

using namespace std;

export class Ability {
    string name;

    public:
        virtual Ability(string name);
        virtual boolean usePower(Player &p1, Player &p2, Board &b, Coords &c);
        virtual ~Ability() = 0;
};
