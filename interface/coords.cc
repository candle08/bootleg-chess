export module Coords;

export struct Coords {
    int r;
    int c;

    bool operator==(const Coords other);
};