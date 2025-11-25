export module DoubleDown;
import Board;
import Coords;
import Ability;
import Player;

using namespace std;

export class DoubleDown : public Ability {
    public:
        DoubleDown();
        string usePower(Board &b, Coords &c, Link* link, Player * p) override;
};
