module Terminal;
import Gameplay;
import <iostream>;

using namespace std;

void Terminal::notify(const ISubject & b) {
    Board& board = (Board&)b;
    printOutput(cout, board);
}

void print_player_info(ostream & o, Board & b, PlayerHeader & ph, int player, bool owner) { // owner is the player whose turn it is
    o << "Player " << player << ":" << endl;
    o << "Downloaded: " << ph.players[player]->num_data_downloaded << "D, " << ph.players[player]->num_virus_downloaded << "V" << endl;
    o << "Abilities: " << ph.players[player]->abilities.size() << endl;

    if (owner) {
        for (int i = 0; i < Board::NUM_COLS; i ++) {
            char reference = 'a' + i;
            o << reference << ": "; // TODO: print d1 v1
            if (i == Board::NUM_COLS/2) {
                o << endl;
            }
        }   
    } else {
        for (int i = 0; i < Board::NUM_COLS; i ++) {
            char reference = 'a' + i;
            o << reference << ": ";

            // Checking if that char has been revealed
            if (ph.players[player]->getLinkPointerFromChar(reference)->revealed) {
                o << ph.players[player]->getLinkPointerFromChar(reference)->symbol << " ";
            } else {
                o << "?  ";
            }
            if (i == Board::NUM_COLS/2) {
                o << endl;
            }
        }
    }
    
}

// currently the output is designed for a two-player setup
// modifications come
void Terminal::printOutput(ostream & o, Board & b) {
    PlayerHeader& ph = b.ph;
    int player = b.getCurrentPlayerID();
    print_player_info(o, b, ph, player, true);
    // Symbol of border printed
    const char BORDER = '=';

    // Printing top border of board
    for (int i = 0; i < Board::NUM_COLS; i ++) {
        o << BORDER;
    }

    o << endl;

    // Printing the squares of the boardan
    for (auto array : b.board) {
        for (Cell c : array) {
            if (player == c.player) {
                o << c.item;
            }
        }
        o << endl;
    }
    o << endl;

    // Printing bottom border of board
    for (int i = 0; i < Board::NUM_COLS; i ++) {
        o << BORDER;
    }

    o << endl;

    // currently this blindly prints out the player info; will have to update so it only prints the obscured version
    for (int i = 0; i < Board::NUM_PLAYERS; i++) {
        if (i != player - 1) {
            print_player_info(o, b, ph, i, false);
        }
    }
}
