export module Board;
import ISubject;
import IObserver;
import Link;
import PlayerHeader;
import Coords;
import <vector>;
import <string>;

using namespace std;

export class Board : public ISubject {
    /** 
     * A matrix of coordinates storing the starting coords of links
     * The vector at index i is the positions for the i+1th player's links
     */ 
    const vector<vector<Coords>> link_starting_coords = {
        {{7, 0}, {7, 1}, {7, 2}, {6, 3}, {6, 4}, {7, 5}, {7, 6}, {7, 7}},
        {{0, 0}, {0, 1}, {0, 2}, {1, 3}, {1, 4}, {0, 5}, {0, 6}, {0, 7}}
    };

    /**
     * A matrix of coordinates storing the locations for server ports
     * The vector at index i is the positions for the i+1th player's server ports
     */
    const vector<vector<Coords>> server_port_coords = {
        {{7, 3}, {7, 4}},
        {{0, 3}, {0, 4}}
    }

   
    
    bool ability_used;

    bool validPos(const Coords c);
    void initializePlayer(Player* p);

    public:
    /**
     * A simple struct for holding the information of a cell
         */
        struct Cell {
            int player; // Player number that the item in the cell belongs to: 0 if N/A
            char item; // 'S' for server port, 'V' for virus, 'D' for data, '\0' for empty
            int level; // level of the link in the cell, or 0 if there isn't a link in the cell
            
            /**
             * Remove items from cell, clearing fields
             */
            void clear();
        }
        
        static inline const int NUM_ROWS = 8;
        static inline const int NUM_COLS = 8;
        static inline const int NUM_PLAYERS = 2;
        static inline const int NUM_SERVER_PORTS_PER_PLAYER = 2;

        // Symbols for the Cell.item field; compare value with constant directly
        static inline const char DATA = 'D';
        static inline const char VIRUS = 'V';
        static inline const char EMPTY = '\0';
        static inline const char SERVER = 'S';

        /**
         * A 2D matrix of strings representing the board; updated every turn
         * The strings are to be interpreted as follows:
         * "": Empty square
         * "1S": server port for Player 1 (similar for Player 2)
         * "1V2": level 2 virus
         */
        vector<vector<Cell>> board;
        PlayerHeader ph;

        /**
         * Variable to store the turn number
         * if turn_number % NUM_PLAYERS == 0, it's player 1's turn, etc
         */
        int turn_number;

        Board(vector<string> link_orderings, vector<string> ability_selections);
        bool isValidPos(const Coords coords) const;
        string move(string link, string dir);
        string useAbility(char ability, Coords coords = {-1, -1}, string link = "");
        int getCurrPlayer();


};
