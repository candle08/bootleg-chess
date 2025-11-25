export module Ability;

import Coords;

using namespace std;

export class Ability {
    string name;

    public:
        virtual Ability(string name);

        /**
         * Use the corresponding ability's power
         * Returns either the empty string on success, or an error message on failure
         * @param board A reference to the playing board
         * @param coords A reference to the coordinates of the ability, or {-1, -1} if not applicable
         * @param link1 A pointer to the first link targeted in the ability, or nullptr if not applicable
         * @param link2 A pointer to the second link targeted in the ability, or nullptr if not applciable
         * @param p A pointer to the player using the ability
         */
        virtual string usePower(Board &b, Coords &c, Link* link1, Link* link2, Player * p);
        virtual ~Ability() = 0;
};
