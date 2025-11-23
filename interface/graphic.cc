export module Graphic;
import Board;
import GUI;

using namespace std;

export class Graphic : public GUI {
    public:
        void ostream operator<<(*, Board &b, int player);
        void notify(Board & b) override;
};
