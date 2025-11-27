module Terminal;
import Gameplay;
import Link;
import Observer;
import <iostream>;
import <vector>;
import <string>;
import <algorithm>;

using namespace std;

Terminal::Terminal(const ISubject & b) {
    notify(b);
}
void Terminal::notify(const ISubject & b) {
    Board& board = (Board&)b;
    printOutput(cout, board);
}

void print_player_info(ostream & o, Board & b, PlayerHeader & ph, int player, bool owner) { // owner is the player whose turn it is    
    Player* p = ph.players[player];
    o << "Player " << player << ":" << endl;
    o << "Downloaded: " << p->num_data_downloaded << "D, " << p->num_virus_downloaded << "V" << endl;
    o << "Abilities: " << p->abilities.size() << endl;

    // build array of all symbols this player has
    vector<char> symbols;

    for (size_t i = 0; i < p->all_data.size(); i++) {
        symbols.push_back(p->all_data[i]->symbol);
    }
    for (size_t i = 0; i < p->all_virus.size(); i++) {
        symbols.push_back(p->all_virus[i]->symbol);
    }

    sort(symbols.begin(), symbols.end());

    if (owner) {
        for (size_t i = 0; i < symbols.size(); i ++) {
            char reference = symbols[i];
            Link* link_ptr = p->getLinkPointerFromChar(reference);

            if (link_ptr == nullptr) {
                cerr << "somehow, link_ptr in terminal is null" << endl;
            } else {
                o << reference << ": " << link_ptr->type << to_string(link_ptr->level) << " ";
            }

            if (i == Board::NUM_COLS/2 - 1) {
                o << endl;
            }
        }   
    } else {
        for (size_t i = 0; i < symbols.size(); i ++) {
            char reference = symbols[i];
            Link* link_ptr = p->getLinkPointerFromChar(reference);

            if (link_ptr == nullptr) {
                cerr << "somehow, link_ptr in terminal is null" << endl;
            } else if (link_ptr->revealed) {
                o << reference << ": " << link_ptr->type << to_string(link_ptr->level) << " ";
            } else {
                o << "? ";
            }
            
            if (i == Board::NUM_COLS/2 - 1) {
                o << endl;
            }
        }
    }
    
    o << endl;
}

// currently the output is designed for a two-player setup
// modifications come
void Terminal::printOutput(ostream & o, Board & b) {
    PlayerHeader& ph = b.ph;
    // int player = b.getCurrentPlayerID();
    print_player_info(o, b, ph, 0, true);
    // Symbol of border printed
    const char BORDER = '=';

    // Printing top border of board
    for (int i = 0; i < Board::NUM_COLS; i ++) {
        o << BORDER;
    }

    o << endl;

    // Printing the squares of the board
    for (auto array : b.board) {
        for (Cell c : array) {
            o << c.symbol;
        }
        o << endl;
    }
    o << endl;

    // Printing bottom border of board
    for (int i = 0; i < Board::NUM_COLS; i ++) {
        o << BORDER;
    }

    o << endl;

    print_player_info(o, b, ph, 1, false);
}
