export module ISubject;
import IObserver;

export class ISubject {
    
    vector<IObserver *> observer;
    public:
    ~ISubject();
};
