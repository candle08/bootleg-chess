export module LinkBoost;

import Ability;

export class LinkBoost : public Ability {
    string name;
    public:
    use_power(Player & p1, Player &p2, Board & b, int x, int y);

};
