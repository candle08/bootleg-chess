export module GUI;
import IObserver;
import Board;

using namespace std;

export class GUI : public IObserver {
    public:
    virtual void notify(Board & b);
    ~GUI() = default;
};
