export module TwoSum;
import <Board>;
import Coords;
import Ability;
import Player;

using namespace std;

export class TwoSum : public Ability {
    string name;

    public:
    use_power(Player & p1, Player &p2, Board & b, Coords c);
};
