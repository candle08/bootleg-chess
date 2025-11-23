export module Data;
import Coords;
import Link;

export class Data : public Link {
    int level;
    Coords c;

    public:
        Data(int level, Coords c);
        virtual ~Data() = 0;
};
