export module GUI;
import IObserver;
import Gameplay;

using namespace std;

export class GUI : public IObserver {
    public:
        virtual ~GUI() = 0;
        void virtual notify(const IObserver& b) override = 0;
};
