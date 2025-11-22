export module Ability;

import Player;
import Board;
import Coords;

export class Ability {
    string name;
    public:
    void virtual usePower(Player & p1, Player & p2, Board & b, Coords & c);
    virtual ~Ability() = default;
};
