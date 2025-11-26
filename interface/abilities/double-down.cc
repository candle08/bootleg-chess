export module DoubleDown;

import Coords;
import Gameplay;
import Link;

using namespace std;

export class DoubleDown : public Ability {
    public:
        DoubleDown();
        string usePower(Board &b, Coords &c, Link* link1, Link* link2, Player * p) override;
};
