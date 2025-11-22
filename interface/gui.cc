export module GUI;
import IObserver;
import Board;

export class GUI : public IObserver {
    public:
    void virtual notify(Board & b);
    ~GUI() = default;
};
