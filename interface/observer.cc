export module Observer;
import <vector>;

using namespace std;

export class IObserver;

export class ISubject {
    vector<IObserver *> observers;

    public:
        /**
         * Adds an observer
         */
        virtual void subscribe(IObserver* o) = 0;

        /**
         * Removes an observer
         */
        virtual void unsubscribe(IObserver* o) = 0;

        /**
         * Calls notify to all observers
         */
        virtual void notifyObservers() = 0;
        virtual ~ISubject() = default;
};

export class IObserver {
    public:
        virtual void notify(const ISubject &b) = 0;
        virtual ~IObserver() = default;
};
