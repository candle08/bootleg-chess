export module Link;
import Coords;

export struct Link {
    int level;
    Coords coords;
    string type;
    bool download_status;
    char symbol;
    bool revealed;

    Link(int level, Coords coords, string type, char symbol);

    /**
     * Update the coords of the link, but with a Coords parameter
     * @param new_coords The new coords of the link
     */
    void move(Coords new_coords);
}; 
