export module GUI;
import IObserver;
import Board;

using namespace std;

export class GUI : public IObserver {
    public:
        virtual ~GUI() = 0;
        virtual notify(const Board& b) override = 0;
};
