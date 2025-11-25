export module Download;

import Board;
import Coords;
import Ability;
import Player;

export class Download : public Ability {
    public:
        string usePower(Board &b, Coords &c, Link* link1, Link* link2, Player * p) override;
};
