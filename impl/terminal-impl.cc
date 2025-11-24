module Terminal;
import Board;
import PlayerHeader;

// currently the output is designed for a two-player setup
// modifications come
&ostream Terminal::operator<<(ostream & o, Board & b, PlayerHeader & ph, int player) {

    // Symbol of border printed
    const char BORDER = "="
    o << "Player " << player << ":" << endl;
    o << "Downloaded: " << ph[player - 1].num_data_downloaded + ph[player - 1].num_virus_downloaded;
    o << "Abilities: " << 

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
    return o;
}