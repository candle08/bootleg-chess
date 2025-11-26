module Graphic;
import Gameplay; 
import Observer;
import <iostream>;
import <string>;
import <vector>;

import xwindow;
using namespace std;

void Graphic::notify(const ISubject & b) {
    Board& boardRef = (Board&)b;    
    printOutput(cout, boardRef);
}

Graphic::Graphic() {
    xw = new Xwindow{};
}



void Graphic::printOutput(ostream& o, Board &b) {
    PlayerHeader& ph = b.ph;
    int player = b.getCurrentPlayerID();

    if (this->xw) {
        int cellSize = 50;
        int offset_x = 25;
        int offset_y = 75; // Space for P1 stats at top

        // Clear view area (simple fill white)
        xw->fillRectangle(0, 0, 500, 600, Xwindow::White);

        // Draw Player 1 Stats at Top
        string p1Str = "P1: " + to_string(ph.players[0]->num_data_downloaded) + "D, " 
                       + to_string(ph.players[0]->num_virus_downloaded) + "V | Abilities: " 
                       + to_string(ph.players[0]->abilities.size());
        xw->drawString(10, 20, p1Str);

        // Draw Grid and Cells
        for (int r = 0; r < b.NUM_ROWS; ++r) {
            for (int c = 0; c < b.NUM_COLS; ++c) {
                Cell &cell = b.board[r][c];
                
                int x = offset_x + c * cellSize;
                int y = offset_y + r * cellSize;
                
                int color = Xwindow::White; 
                string label = "";

                if (cell.item == b.SERVER) {
                    color = Xwindow::Blue; // Arbitrary distinct color for Server
                    label = "S";
                } else if (cell.item != b.EMPTY) {
                    // Logic for Links
                    if (cell.player == player) {
                        // My Link: Color coded by type [cite: 82]
                        if (cell.item == b.DATA) {
                            color = Xwindow::Green;
                            label = "D" + to_string(cell.level);
                        } else if (cell.item == b.VIRUS) {
                            color = Xwindow::Red;
                            label = "V" + to_string(cell.level);
                        }
                    } else {
                        // Opponent Link: Hidden [cite: 72]
                        color = Xwindow::Black;
                        label = "?"; 
                    }
                }

                // Draw Cell Background
                xw->fillRectangle(x, y, cellSize, cellSize, color);
                
                // Draw Firewall Indicator [cite: 96]
                if (cell.firewall) {
                    // Draw an orange border inside the cell to represent firewall
                    xw->fillRectangle(x+2, y+2, cellSize-4, cellSize-4, Xwindow::Orange);
                    if (cell.item == b.EMPTY) label = "M"; // Mark empty firewalls
                }

                // Draw Grid Border
                xw->fillRectangle(x, y, cellSize, cellSize, Xwindow::Black);

                // Draw Text
                if (!label.empty()) {
                    // Ensure text is visible against background
                    /*
                     int textColor = (color == Xwindow::Black || color == Xwindow::Blue || color == Xwindow::Red) 
                                    ? Xwindow::White : Xwindow::Black;
                    */
                   
                    // Centering math (approximate)
                    xw->drawString(x + 20, y + 30, label); 
                }
            }
        }
        
        // Draw Player 2 Stats at Bottom
        string p2Str = "P2: " + to_string(ph.players[1]->num_data_downloaded) + "D, " 
                       + to_string(ph.players[1]->num_virus_downloaded) + "V | Abilities: " 
                       + to_string(ph.players[1]->abilities.size());
        xw->drawString(10, offset_y + (8 * cellSize) + 20, p2Str);
    }
}   

Graphic::~Graphic() {
    delete xw;
}
