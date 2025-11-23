export module TwoSum;
import Board;
import Coords;
import Ability;
import Player;

using namespace std;

export class TwoSum : public Ability {
    public:
        TwoSum();
        bool usePower(Player & p1, Player &p2, Board & b, Coords c) override;
};
