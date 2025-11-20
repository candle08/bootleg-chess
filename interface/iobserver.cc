export module IObserver;
import Board;

export class IObserver {
    public:
    virtual void notify(const Board &b) = 0;
    virtual ~IObserver();
}
