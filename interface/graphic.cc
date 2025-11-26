export module Graphic;
import Gameplay;
import Observer;
import GUI;
import xwindow;

import <iostream>;

using namespace std;

export class Graphic : public GUI {
    Xwindow *xw;
    public:
        Graphic();
        void printOutput(ostream& o, Board &b);
        void notify(const ISubject & b) override;
        ~Graphic();
};
