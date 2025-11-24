module Terminal;
import Board;
import PlayerHeader;

using namespace std;

void print_player_info(ostream & o, Board & b, PlayerHeader & ph, int player) {
    o << "Player " << player << ":" << endl;
    o << "Downloaded: " << ph[player - 1].num_data_downloaded << "D, " << ph[player - 1].num_virus_downloaded "V" << endl;
    o << "Abilities: " << ph[player-1].abilities.size() << endl;
    for (int i = 0; i < NUM_COLS; i ++) {
        o << char(61 + i) << ": " << ;
        if (i == NUM_COLS/2) {
            o << endl;
        }
    }
}

// currently the output is designed for a two-player setup
// modifications come
&ostream Terminal::operator<<(ostream & o, Board & b, PlayerHeader & ph, int player) {

    print_player_info(o, b, ph, player);
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
            print_player_info(o, b, ph, i);
        }
    }
    return o;
}