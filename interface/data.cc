export module Data;
import Coords;
import Link;

export struct Data : public Link {
    Data(int level, Coords coords, char symbol);
};
