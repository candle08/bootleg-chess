export module GUI;
import Observer;
import Gameplay;

using namespace std;

export class GUI : public IObserver {
    public:
        virtual ~GUI() = default;
        void virtual notify(const ISubject& b) override = 0;
};
