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

    map<char, Link *> positions; // A hashmap of the position association of each Link for a player


    /**
     * An array of links that the player has downloaded
    */
    vector<Link *> downloaded;
    int num_virus_downloaded;
    int num_data_downloaded;

    public:
        /**
         * Initialize a player class with the passed parameters
         * @param links The order of links, represented as a length-16 string (e.g. "D1D2V1V2...")
         * @param abilities_selected The abilities selected, represented as a length-5 string
         * @param positions A size-8 vector of the corodinates of the links
         */
        Player(string link_orderings, string abilities_selected, vector<Coords> positions)
        
        

        /**
         * Returns a pointer to the corresponding virus or data that the string represents
         * It is assumed that the string is of valid format
         */
        Link* getLinkPointerFromSymbol(char link);

        /**
         * Use and remove the ability represented by the char
         * Returns the empty string on success, or an error message on failure
         * It is assumed that ability is valid (a capitalized letter representing the ability)
         */
        string useAbility(char ability, Board& b, Coords& c, string link);
        ~Player();
};
