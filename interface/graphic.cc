export module Graphic;
import Gameplay;
import IObserver;
import GUI;

import <iostream>;

using namespace std;

export class Graphic : public GUI {
    public:
        void printOutput(ostream& o, Board &b);
        void notify(const IObserver & b) override;
};
