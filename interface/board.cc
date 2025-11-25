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
    vector<IObserver*> observers;

    /** 
     * A matrix of coordinates storing the starting coords of links
     * The vector at index i is the positions for the i+1th player's links
     */ 
    const vector<vector<Coords>> link_starting_coords = {
        {{0, 0}, {0, 1}, {0, 2}, {1, 3}, {1, 4}, {0, 5}, {0, 6}, {0, 7}},
        {{7, 0}, {7, 1}, {7, 2}, {6, 3}, {6, 4}, {7, 5}, {7, 6}, {7, 7}}
    };

    /**
     * A matrix of coordinates storing the locations for server ports
     * The vector at index i is the positions for the i+1th player's server ports
     */
    const vector<vector<Coords>> server_port_coords = {
        {{0, 3}, {0, 4}}
        {{7, 3}, {7, 4}},
    }

    /**
     * A matrix of characters storing the symbol for each
     * player's links. The vector at index i is the symbols of the i+1th
     * player's links
     */
    const vector<vector<char>> symbols = {
        {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},
        {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'}
    }
    
    /**
     * Variable that indicates whether or not an ability
     * has been used
     */
    bool ability_used;

    public:
    /**
     * A simple struct for holding the information of a cell
         */
        struct Cell {
            int player; // Player number that the item in the cell belongs to: 0 if N/A
            char item; // 'S' for server port, 'V' for virus, 'D' for data, '\0' for empty
            int level; // level of the link in the cell, or 0 if there isn't a link in the cell
            bool firewall; // whether or not a player has set a firewall at that square
            
            /**
             * Overriding default constructor of cell to write specific values
             */
            Cell();

            /**
             * Remove items from cell, clearing fields
             */
            void clear();
        }
        
        // Constants related to board size, players, and board setup
        static inline const int NUM_ROWS = 8;
        static inline const int NUM_COLS = 8;
        static inline const int NUM_PLAYERS = 2;
        static inline const int NUM_SERVER_PORTS_PER_PLAYER = 2;
        static inline const int NUM_DATA_DOWNLOADED_TO_WIN = 4;
        static inline const int NUM_VIRUS_DOWNLOADED_TO_LOSE = 4;

        // Symbols for the Cell.item field; compare value with constant directly
        static inline const char DATA = 'D';
        static inline const char VIRUS = 'V';
        static inline const char EMPTY = '\0';
        static inline const char SERVER = 'S';

        /**
         * A 2D matrix of Cells representing the board; updated every turn
         * See "Cell" struct for more information
         */
        vector<vector<Cell>> board;

        /**
         * A PlayerHeader containing all players.
         * See "PlayerHeader" module for more information
         */
        PlayerHeader ph;

        /**
         * Variable to store the turn number; STARTS AT 0
         * if turn_number % NUM_PLAYERS == 0, it's player 1's turn, etc
         */
        int turn_number;

        /**
         * Variable to store the winner of the game, where the winner is
         * the winner-th player. When winner == -1, there is no winner
         */
        int winner;

        /**
         * Variable that indicates whether the double down ability is
         * in effect for the current turn
         */
        bool double_down;

        /**
         * Initializes a Board class with the passed parameters
         * @param link_orderings A vector of each player's link orderings, where
         * the vector at index i represents the i+1th player's link orderings.
         * @param ability_selections A vector of each player's 5 selected abilities,
         * where the vector at index i represents the i+1th player's abilities selected.
         * See the "Player" module for more information
         */
        Board(vector<string> link_orderings, vector<string> ability_selections);

        /**
         * Determines whether coords is a valid position on the board
         * @param coords A coordinate (r, c)
         */
        bool isValidPos(const Coords coords) const;

        /**
         * Moves link in the direction dir
         * 
         * @param link A character representing a link, from the character matrix
         * "symbol" above
         * @param dir A string representing a direction out of the four:
         * "up", "down", "left", "right"
         */
        string move(char link, string dir);

        /**
         * Use and remove the ability of the current player represented by the char
         * See the "Player" module for more information
         * @param ability
         * @param coords
         * @param link1
         * @param link2
         */
        string useAbility(char ability, Coords coords = {-1, -1}, char link1 = '\0', char link2 = '\0');
       
        /**
         * @param p
         */
        void win(Player* p);

        /**
         * 
         */
        void checkWinCondition();

        /**
         * 
         */
        int getCurrentPlayerID();

        /**
         * 
         */
        Player* getCurrentPlayer();

        /**
         * Adds an observer o
         */
        void subscribe(IObserver* o);

        /**
         * Removes an observer o
         */
        void unsubscribe(IObserver* o);

        /**
         * Calls notify to all observers
         */
        void notifyObservers();
};
