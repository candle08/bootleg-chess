export module Graphic;
import Board;
import GUI;

export class Graphic : public GUI {
    public:
    void virtual ostream operator<<(*, Board &b, int player);
    virtual ~Graphic() = default;
};
