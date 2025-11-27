module;
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h> // For usleep
module Graphic;

import Gameplay; 
import Link; // Import Link to access Link properties (type, level, revealed)
import Observer;
import <iostream>;
import <string>;
import <vector>;
import <algorithm>; // Required for std::sort
import <cstdlib>; // For exit

using namespace std;

// ==========================================
// Constructor: Sets up X11 Window
// ==========================================
Graphic::Graphic(const ISubject & b) {
    int width = 500;
    int height = 650; // Increased to 650 to comfortably fit text at bottom

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
    for(int i=0; i < 5; ++i) { 
        XParseColor(d,cmap,color_vals[i],&xcolour);
        XAllocColor(d,cmap,&xcolour);
        colours[i]=xcolour.pixel;
    }
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
    cerr << "graphic dtor" << endl;
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
    // cerr << "notify called of graphic notify\n";
    Board& boardRef = (Board&)b;    
    printOutput(cout, boardRef);
}

void Graphic::printOutput(ostream& o, Board &b) {
    PlayerHeader& ph = b.ph;
    int currentPlayer = b.getCurrentPlayerID();

    int cellSize = 50;
    int offset_x = 25;
    int offset_y = 100; // Shifted down to make room for P1 text

    // 1. Clear view area 
    fillRectangle(0, 0, 500, 650, White);

    // =========================================================
    // Helper Lambda to Draw Player Info (Replaces print_player_info)
    // =========================================================
    auto drawPlayerInfo = [&](int playerID, int startX, int startY, bool isOwner) {
        Player* p = ph.players[playerID];
        
        // 1. Stats Line
        string header = "Player " + to_string(playerID) + ":";
        string stats = "Downloaded: " + to_string(p->num_data_downloaded) + "D, " 
                       + to_string(p->num_virus_downloaded) + "V";
        string abilities = "Abilities: " + to_string(p->abilities.size());

        drawString(startX, startY, header);
        drawString(startX + 80, startY, stats);
        drawString(startX + 300, startY, abilities);

        // 2. Build Symbol List
        vector<char> symbols;
        for (size_t i = 0; i < p->all_data.size(); i++) {
            symbols.push_back(p->all_data[i]->symbol);
        }
        for (size_t i = 0; i < p->all_virus.size(); i++) {
            symbols.push_back(p->all_virus[i]->symbol);
        }
        sort(symbols.begin(), symbols.end());

        // 3. Draw Links
        int linkX = startX;
        int linkY = startY + 15; // Start drawing links on next line
        int count = 0;

        for (size_t i = 0; i < symbols.size(); i++) {
            char reference = symbols[i];
            Link* link_ptr = p->getLinkPointerFromChar(reference);
            
            string infoString = "";
            infoString += reference;
            infoString += ": ";

            if (link_ptr == nullptr) {
               // Should not happen
            } else if (isOwner || link_ptr->revealed) {
                infoString += link_ptr->type;
                infoString += to_string(link_ptr->level);
            } else {
                infoString += "?";
            }

            drawString(linkX, linkY, infoString);

            // Spacing for next link
            linkX += 50; 
            count++;

            // Break line logic (similar to i == Board::NUM_COLS/2 - 1 in terminal)
            if (count == 4) {
                linkX = startX;
                linkY += 15;
            }
        }
    };

    // =========================================================
    // Draw Components
    // =========================================================

    // 1. Draw Player 1 (Top) - mimics print_player_info(..., 0, true)
    drawPlayerInfo(0, 10, 20, true);

    // 2. Draw Grid and Cells
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
                // Logic for Links on Board
                if (cell.player == currentPlayer) {
                    if (cell.item == b.DATA) {
                        color = Green;
                        label = "D" + to_string(cell.level);
                    } else if (cell.item == b.VIRUS) {
                        color = Red;
                        label = "V" + to_string(cell.level);
                    }
                } else {
                    color = Black;
                    label = "?"; // Opponent hidden
                }
            }

            // Draw Cell Background
            fillRectangle(x, y, cellSize, cellSize, color);
            
            // Draw Firewall Indicator
            if (cell.firewall) {
                fillRectangle(x+2, y+2, cellSize-4, cellSize-4, Orange);
                if (cell.item == b.EMPTY) label = "M"; 
            }            
            
            // Draw Text Label inside cell
            if (!label.empty()) {
                // Contrast adjustment: if background is Black/Red/Blue, use White text? 
                // X11 simple drawString is usually just foreground color. 
                // Currently simple Black text. might be hard to see on Black/Blue.
                // Assuming XSetForeground handles the drawString color, 
                // we reset to Black at start of fillRectangle helper, so text is Black.
                drawString(x + 20, y + 30, label); 
            }
        }
    }
    
    // 3. Draw Player 2 (Bottom) - mimics print_player_info(..., 1, false)
    // Calculate Y position: Offset + (Rows * Size) + Padding
    int p2_y = offset_y + (8 * cellSize) + 30;
    drawPlayerInfo(1, 10, p2_y, false);
}
