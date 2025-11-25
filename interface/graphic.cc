export module Graphic;
import Board;
import IObserver;
import GUI;

using namespace std;

export class Graphic : public GUI {
    public:
        ostream& operator<<(*, Board &b, int player);
        void notify(const IObserver & b) override;
};
