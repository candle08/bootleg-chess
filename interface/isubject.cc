export module ISubject;
import IObserver;

export ISubject {
    
    vector<Observer *> observer;
    public:
    ~ISubject();
};
