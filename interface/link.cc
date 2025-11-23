export module Link;
import Coords;

export class Link {
    int level;
    Coords c;

    public:
        Link(int level, Coords c);
        Link(int level, int r, int c);
};
