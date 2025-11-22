export module Graphic;
import Board;
import GUI;

using namespace std;

export class Graphic : public GUI {
    public:
    virtual void ostream operator<<(*, Board &b, int player);
    virtual ~Graphic() = default;
};
