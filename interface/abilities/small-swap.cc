export module SmallSwap;
import Board;
import Coords;
import Ability;
import Player;

using namespace std;

export class SmallSwap : public Ability {
    public:
        SmallSwap();
        bool usePower(Player & p1, Player &p2, Board & b, Coords c) override;
};
