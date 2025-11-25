export module TwoSum;
import Board;
import Coords;
import Ability;
import Player;

using namespace std;

export class TwoSum : public Ability {
    public:
        TwoSum();
        string usePower(Board &b, Coords &c, Link* link1, Link* link2, Player * p) override;
};
