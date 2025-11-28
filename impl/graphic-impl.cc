module;
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h> 
module Graphic;

import Gameplay; 
import Link; 
import Observer;
import <iostream>;
import <string>;
import <vector>;
import <algorithm>; 
import <cstdlib>; 

using namespace std;

// ==========================================
// Constructor
// ==========================================
Graphic::Graphic(const ISubject & b) {
    // Increased height to accommodate the "Sandwich" layout (P1 -> Board -> P2)
    int width = 500;
    int height = 750; 

    d = XOpenDisplay(NULL);
    if (d == NULL) {
        if (Board::DEBUG) cerr << "Cannot open display" << endl;
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
    // Added LightGray/DarkGray logic if needed, but sticking to basics for now
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

    XSizeHints hints;
    hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
    hints.height = hints.base_height = hints.min_height = hints.max_height = height;
    hints.width = hints.base_width = hints.min_width = hints.max_width = width;
    XSetNormalHints(d, w, &hints);

    XSynchronize(d,True);

    usleep(1000);

    notify(b);
}

Graphic::~Graphic() {
    XFreeGC(d, gc);
    XCloseDisplay(d);
}

// ==========================================
// Drawing Helpers
// ==========================================
void Graphic::fillRectangle(int x, int y, int width, int height, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, w, gc, x, y, width, height);
    XSetForeground(d, gc, colours[Black]); // Reset to black for text/lines
}

void Graphic::drawString(int x, int y, string msg) {
    XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}

// ==========================================
// Core Logic
// ==========================================

void Graphic::notify(const ISubject & b) {
    Board& boardRef = (Board&)b;    
    printOutput(cout, boardRef);
}

void Graphic::printOutput(ostream& o, Board &b) {
    PlayerHeader& ph = b.ph;
    int currentPlayer = b.getCurrentPlayerID();

    // Layout Constants
    const int CELL_SIZE = 50;
    const int BOARD_X_OFFSET = 50; 
    const int P1_Y_START = 20;
    const int BOARD_Y_START = 160; // Pushed down to make room for P1 stats
    const int P2_Y_START = BOARD_Y_START + (8 * CELL_SIZE) + 40;

    // Clear Screen
    fillRectangle(0, 0, 500, 750, White);

    // ========================================================================
    // LAMBDA: Draw Player Info (Replicates Terminal::print_player_info logic)
    // ========================================================================
    auto drawPlayerInfo = [&](int playerID, int startY, bool isOwner) {
        Player* p = ph.players[playerID];
        int x = 10;
        int y = startY;
        int lineHeight = 15;

        // 1. Player Header
        drawString(x, y, "Player " + to_string(playerID + 1) + ":");
        y += lineHeight;

        // 2. Downloaded Stats
        string stats = "Downloaded: " + to_string(p->num_data_downloaded) + "D, " 
                     + to_string(p->num_virus_downloaded) + "V";
        drawString(x, y, stats);
        y += lineHeight;

        // 3. Abilities Left
        int abilities_left = 0;
        for (auto a : p->abilities) {
            if (!a->used) ++abilities_left;
        }
        string abStr = "Abilities: " + to_string(abilities_left);
        drawString(x, y, abStr);
        y += lineHeight + 5; // Extra gap before links

        // 4. Link Legend
        vector<char> symbols;
        for (size_t i = 0; i < p->all_data.size(); i++) symbols.push_back(p->all_data[i]->symbol);
        for (size_t i = 0; i < p->all_virus.size(); i++) symbols.push_back(p->all_virus[i]->symbol);
        sort(symbols.begin(), symbols.end());

        int count = 0;
        int linkX = x;
        
        for (size_t i = 0; i < symbols.size(); i++) {
            char ref = symbols[i];
            Link* link_ptr = p->getLinkPointerFromChar(ref);
            string info = string(1, ref) + ": ";

            if (link_ptr) {
                if (isOwner || link_ptr->revealed) {
                    info += link_ptr->type + to_string(link_ptr->level);
                } else {
                    info += "?";
                }
            }

            drawString(linkX, y, info);
            
            // Advance position
            linkX += 60; // Width of one link entry
            count++;

            // Break line logic: (i == Board::NUM_COLS/2 - 1) in Terminal
            // This usually breaks after 4 items
            if (count % 4 == 0) {
                linkX = x;
                y += lineHeight;
            }
        }
    };

    // ========================================================================
    // EXECUTION
    // ========================================================================

    // 1. Draw Player 1 Info (Owner if currentPlayer == 0)
    drawPlayerInfo(0, P1_Y_START, (currentPlayer == 0));

    // 2. Draw Top Border (Visual representation of =======)
    // Drawing a thick black line above the board
    fillRectangle(BOARD_X_OFFSET, BOARD_Y_START - 5, (8*CELL_SIZE), 3, Black);

    // 3. Draw The Board Grid
    for (int r = 0; r < b.NUM_ROWS; ++r) {
        for (int c = 0; c < b.NUM_COLS; ++c) {
            Cell &cell = b.board[r][c];
            
            int x = BOARD_X_OFFSET + c * CELL_SIZE;
            int y = BOARD_Y_START + r * CELL_SIZE;

            int bgColour = White;
            string text = "";

            // Determine Background & Text
            if (cell.item == b.SERVER) {
                bgColour = Blue; // Server Port
                text = "S";
            } 
            else if (cell.item == b.VIRUS || cell.item == b.DATA) {
                // It's a link
                if (cell.player == 0) bgColour = Green; // P1 is Green-ish
                else bgColour = Red; // P2 is Red-ish
                
                // Logic for what text to show inside the square
                // The terminal shows the 'symbol' (e.g., 'a'). 
                // X11 allows us to show the symbol AND the type if known.
                // Let's stick to the Symbol to be faithful to the grid representation.
                text = string(1, cell.symbol);
                
                // Optional: If you want to see "D4" inside the box visually:
                // if (cell.player == currentPlayer || /* link is revealed logic */) ...
            }
            else if (cell.firewall != -1) {
                bgColour = Orange; // Firewall
                text = "w"; // Or "m" depending on owner? Terminal uses 'w'/'m' usually
                if (cell.firewall == 0) text = "m"; // P1 firewall
                else text = "w"; // P2 firewall
            }
            else {
                // Empty
                text = ".";
            }

            // Draw Box
            fillRectangle(x, y, CELL_SIZE, CELL_SIZE, bgColour);
            
            // Draw Border for Box
            XDrawRectangle(d, w, DefaultGC(d, s), x, y, CELL_SIZE, CELL_SIZE);

            // Draw Text Centered
            // If background is dark (Blue/Red/Green), standard black text might be hard to read.
            // But simple X11 usually handles Black on those colors okay.
            if (!text.empty()) {
                drawString(x + 20, y + 30, text);
            }
        }
    }

    // 4. Draw Bottom Border
    fillRectangle(BOARD_X_OFFSET, BOARD_Y_START + (8*CELL_SIZE) + 2, (8*CELL_SIZE), 3, Black);

    // 5. Draw Player 2 Info (Owner if currentPlayer == 1)
    drawPlayerInfo(1, P2_Y_START, (currentPlayer == 1));
}
