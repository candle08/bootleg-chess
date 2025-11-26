export module IObserver;

export class IObserver {
    public:
        virtual void notify(const ISubject &b) = 0;
};
