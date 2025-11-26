export module GUI;
import Observer;
import Gameplay;

using namespace std;

export class GUI : public IObserver {
    public:
        virtual ~GUI() = 0;
        void virtual notify(const ISubject& b) override = 0;
};
