export module Link;
import Coords;

export struct Link {
    int level;
    Coords coords;
    string type;

    Link(int level, Coords coords);

    /**
     * Update the coords of the link, but with a Coords parameter
     * @param new_coords The new coords of the link
     */
    void move(Coords new_coords);
}; 
