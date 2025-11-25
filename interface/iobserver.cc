export module IObserver;

export class IObserver {
    public:
        virtual void notify(const IObserver &b) = 0;
};
