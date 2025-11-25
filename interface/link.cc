export module Link;
import Coords;

export struct Link {
    int level; // level on a scale of 1 to 4
    Coords coords;
    string type; // virus or data
    bool download_status; // whether or not the link has been downloaded
    char symbol; // its symbol on the board
    bool revealed; // whether or not a link has been revealed
    bool linkboost; // whether or not a link has been boosted
    int frozen_on_turn; // number of frozen turns from double-down ability; when double-down is called, we set freeze = level, and after every turn we decrement freeze by 1

    Link(int level, Coords coords, string type, char symbol, bool revealed, bool linkboost);

    /**
     * Update the coords of the link, but with a Coords parameter
     * @param new_coords The new coords of the link
     */
    void move(Coords new_coords);
}; 
