export module ISubject;
import IObserver;
import <vector>;

using namespace std;

export class ISubject {
    vector<IObserver *> observer;

    public:
        virtual ~ISubject() = 0;
};
