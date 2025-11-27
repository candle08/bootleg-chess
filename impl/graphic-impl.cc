module;
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h> // For usleep
module Graphic;

import Gameplay; 
import Observer;
import <iostream>;
import <string>;
import <vector>;
import <cstdlib>; // For exit

using namespace std;

// ==========================================
// Constructor: Sets up X11 Window
// ==========================================
Graphic::Graphic(const ISubject & b) {
    int width = 500;
    int height = 600; // Increased to 600 to fit the board logic (offset + rows)

    d = XOpenDisplay(NULL);
    if (d == NULL) {
        cerr << "Cannot open display" << endl;
        exit(1);
    }
    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapRaised(d, w);

    Pixmap pix = XCreatePixmap(d,w,width,
            height,DefaultDepth(d,DefaultScreen(d)));
    gc = XCreateGC(d, pix, 0,(XGCValues *)0);

    XFlush(d);
    XFlush(d);

    // Set up colours
    XColor xcolour;
    Colormap cmap;
    char color_vals[10][10]={"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

    cmap=DefaultColormap(d,DefaultScreen(d));
    for(int i=0; i < 5; ++i) { // Note: Original loop only went to 5, might want to increase to 10
        XParseColor(d,cmap,color_vals[i],&xcolour);
        XAllocColor(d,cmap,&xcolour);
        colours[i]=xcolour.pixel;
    }
    // Attempt to load the rest of the colors if the loop above was intentional
    for(int i=5; i < 10; ++i) {
        XParseColor(d,cmap,color_vals[i],&xcolour);
        XAllocColor(d,cmap,&xcolour);
        colours[i]=xcolour.pixel;
    }

    XSetForeground(d,gc,colours[Black]);

    // Make window non-resizeable
    XSizeHints hints;
    hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
    hints.height = hints.base_height = hints.min_height = hints.max_height = height;
    hints.width = hints.base_width = hints.min_width = hints.max_width = width;
    XSetNormalHints(d, w, &hints);

    XSynchronize(d,True);

    usleep(1000);

    notify(b);
}

// ==========================================
// Destructor: Cleans up X11
// ==========================================
Graphic::~Graphic() {
    XFreeGC(d, gc);
    XCloseDisplay(d);
}

// ==========================================
// Helper Drawing Functions
// ==========================================
void Graphic::fillRectangle(int x, int y, int width, int height, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, w, gc, x, y, width, height);
    XSetForeground(d, gc, colours[Black]);
}

void Graphic::drawString(int x, int y, string msg) {
    XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}

// ==========================================
// Game Logic
// ==========================================

void Graphic::notify(const ISubject & b) {
    // debug
    cerr << "notify called of graphic notify";
    Board& boardRef = (Board&)b;    
    printOutput(cout, boardRef);
}

void Graphic::printOutput(ostream& o, Board &b) {
    PlayerHeader& ph = b.ph;
    int player = b.getCurrentPlayerID();

    // No need to check "if (this->xw)" anymore, we are the window.
    
    int cellSize = 50;
    int offset_x = 25;
    int offset_y = 75; 

    // Clear view area 
    fillRectangle(0, 0, 500, 600, White);

    // Draw Player 1 Stats at Top
    string p1Str = "P1: " + to_string(ph.players[0]->num_data_downloaded) + "D, " 
                    + to_string(ph.players[0]->num_virus_downloaded) + "V | Abilities: " 
                    + to_string(ph.players[0]->abilities.size());
    drawString(10, 20, p1Str);

    // Draw Grid and Cells
    for (int r = 0; r < b.NUM_ROWS; ++r) {
        for (int c = 0; c < b.NUM_COLS; ++c) {
            Cell &cell = b.board[r][c];
            
            int x = offset_x + c * cellSize;
            int y = offset_y + r * cellSize;
            
            int color = White; 
            string label = "";

            if (cell.item == b.SERVER) {
                color = Blue; 
                label = "S";
            } else if (cell.item != b.EMPTY) {
                // Logic for Links
                if (cell.player == player) {
                    if (cell.item == b.DATA) {
                        color = Green;
                        label = "D" + to_string(cell.level);
                    } else if (cell.item == b.VIRUS) {
                        color = Red;
                        label = "V" + to_string(cell.level);
                    }
                } else {
                    color = Black;
                    label = "?"; 
                }
            }

            // Draw Cell Background
            fillRectangle(x, y, cellSize, cellSize, color);
            
            // Draw Firewall Indicator
            if (cell.firewall) {
                fillRectangle(x+2, y+2, cellSize-4, cellSize-4, Orange);
                if (cell.item == b.EMPTY) label = "M"; 
            }            
            
            // Draw Text
            if (!label.empty()) {
                drawString(x + 20, y + 30, label); 
            }
        }
    }
    
    // Draw Player 2 Stats at Bottom
    string p2Str = "P2: " + to_string(ph.players[1]->num_data_downloaded) + "D, " 
                    + to_string(ph.players[1]->num_virus_downloaded) + "V | Abilities: " 
                    + to_string(ph.players[1]->abilities.size());
    drawString(10, offset_y + (8 * cellSize) + 20, p2Str);
}
