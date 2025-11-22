export module Virus;
import Coords;

export class Virus : public Link {
    int level;
    Coords c;

    public:
    Virus(int level, Coords c);
    ~Virus() = default;
};
