export module GUI;
import Observer;
import Gameplay;

using namespace std;

// Abstract class that all displays inherit
export class GUI : public IObserver {
    public:
        void virtual notify(const ISubject& b) override = 0;
};
