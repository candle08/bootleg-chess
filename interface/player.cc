export module Player;
import Virus;
import Data;
import Ability;
import Coords;
import <vector>;

using namespace std;

export class Player {
    vector<Virus *> all_virus;
    vector<Data *> all_data;
    vector<Ability *> abilities;

    public:
        /**
         * Initialize a player class with the passed parameters
         * @param links The order of links, represented as a length-16 string (e.g. "D1D2V1V2...")
         * @param abilities_selected The abilities selected, represented as a length-5 string
         * @param positions A size-8 vector of the corodinates of the links
         */
        Player(string link_orderings, string abilities_selected, vector<Coords> positions)
        ~Player();
};
