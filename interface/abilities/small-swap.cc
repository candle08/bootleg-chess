export module SmallSwap;
import Board;
import Coords;
import Ability;
import Player;

using namespace std;

export class SmallSwap : public Ability {
    public:
        SmallSwap();
        string usePower(Board &b, Coords &c, Link* link, Player * p) override;
};
