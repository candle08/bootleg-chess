module Terminal;
import Board;
import PlayerHeader;
import <iostream>;

using namespace std;

void notify(const Board & b) {
    printOutput(cout, b);
}

void print_player_info(ostream & o, Board & b, PlayerHeader & ph, int player, bool owner) { // owner is the player whose turn it is
    o << "Player " << player << ":" << endl;
    o << "Downloaded: " << ph[player - 1].num_data_downloaded << "D, " << ph[player - 1].num_virus_downloaded "V" << endl;
    o << "Abilities: " << ph[player-1].abilities.size() << endl;

    if (owner) {
        for (int i = 0; i < NUM_COLS; i ++) {
            char reference = 61 + i;
            o << reference << ": " << getLinkPointerFromChar(reference) << "  ";
            if (i == NUM_COLS/2) {
                o << endl;
            }
        }   
    } else {
        for (int i = 0; i < NUM_COLS; i ++) {
            char reference = 61 + i;
            o << reference << ": " 

            // Checking if that char has been revealed
            if (getLinkPointerFromChar(reference)->revealed) {
                o << getLinkPointerFromChar(reference)->symbol << " ";
            } else {
                o << "?  ";
            }
            if (i == NUM_COLS/2) {
                o << endl;
            }
        }
    }
    
}

// currently the output is designed for a two-player setup
// modifications come
void Terminal::printOutput(ostream & o, Board & b) {
    PlayerHeader& ph = b.ph;
    int player = b.getCurrentPlayerId();
    print_player_info(o, b, ph, player, true);
    // Symbol of border printed
    const char BORDER = "="

    // Printing top border of board
    for (int i = 0; i < NUM_COLS; i ++) {
        o << BORDER;
    }

    o << endl;

    // Printing the squares of the boardan
    for (auto * array : b) {
        for (cell c : array) {
            if (player == c.player) {
                o << c.item;
            }
        }
        o << endl;
    }
    o << endl;

    // Printing bottom border of board
    for (int i = 0; i < NUM_COLS; i ++) {
        o << BORDER;
    }

    o << endl;

    // currently this blindly prints out the player info; will have to update so it only prints the obscured version
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (i != player - 1) {
            print_player_info(o, b, ph, i, false);
        }
    }
}