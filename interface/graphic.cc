export module Graphic;
import Board;
import GUI;

using namespace std;

export class Graphic : public GUI {
    public:
        ostream& operator<<(*, Board &b, int player);
        void notify(const Board & b) override;
};
