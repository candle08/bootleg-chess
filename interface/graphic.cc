module;
#include <X11/Xlib.h>
export module Graphic;

import Gameplay;
import Observer;
import GUI;
import <iostream>;
import <string>;

using namespace std;

export class Graphic : public GUI {
    // X11 Display Variables
    Display *d;
    Window w;
    int s;
    GC gc;
    unsigned long colours[10];

    // Helper functions (formerly in Xwindow)
    void fillRectangle(int x, int y, int width, int height, int colour);
    void drawString(int x, int y, string msg);

    public:
        // Color Enum (formerly in Xwindow)
        enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown};

        Graphic(const ISubject & b);
        ~Graphic();

        void printOutput(ostream& o, Board &b);
        void notify(const ISubject & b) override;
};
