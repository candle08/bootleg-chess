export module Ability;

import Player;
import Board;
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
         * @param link A pointer to the link targeted in the ability, or nullptr if not applicable
         */
        virtual string usePower(Board &b, Coords &c, Link* link);
        virtual ~Ability() = 0;
};
// hi