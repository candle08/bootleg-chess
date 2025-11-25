export module ISubject;
import IObserver;
import <vector>;

using namespace std;

export class ISubject {
    vector<IObserver *> observers;

    public:
        /**
         * Adds an observer
         */
        void subscribe(IObserver* o);

        /**
         * Removes an observer
         */
        void unsubscribe(IObserver* o);

        /**
         * Calls notify to all observers
         */
        void notifyObservers();
        virtual ~ISubject() = 0;
};
