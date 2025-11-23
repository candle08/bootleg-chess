export module Virus;
import Link;
import Coords;

export struct Virus : public Link {
    Virus(int level, Coords coords);
    Virus(int level, int r, int c);
};
