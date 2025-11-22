export module ISubject;
import IObserver;
import <vector>;

export class ISubject {
    vector<IObserver *> observer;

    public:
    virtual ~ISubject() = 0;
};
