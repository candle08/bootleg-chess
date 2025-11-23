export module Data;
import Coords;
import Link;

export struct Data : public Link {
    Data(int level, Coords coords);
    Data(int level, int r, int c);
};
