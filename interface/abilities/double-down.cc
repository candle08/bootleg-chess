export module DoubleDown;
import Board;
import Coords;
import Ability;
import Player;

using namespace std;

export class DoubleDown : public Ability {
    public:
        DoubleDown();
        bool usePower(Player & p1, Player &p2, Board & b, Coords c) override;
};
