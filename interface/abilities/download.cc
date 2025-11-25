export module Download;

import Board;
import Coords;
import Ability;
import Player;

export class Download : public Ability {
    public:
        Download();
        string usePower(Board &b, Coords &c, Link* link, Player * p) override;
};
