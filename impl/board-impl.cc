module Board;

import ISubject;
import IObserver;
import Link;
import PlayerHeader;
import Player;
import <vector>;

using namespace std;

void Cell::clear() {
    player = 0;
    item = '\0';
    level = 0;
}

Board::Board(vector<string> link_orderings, vector<string> ability_selections) {
    turn_number = 0;
    
    ph = PlayerHeader{};
    for (int i = 0; i < NUM_PLAYERS; i++) {
        Player* p = new Player{link_orderings[i], ability_selections[i], link_starting_coords[i]};
        ph.players.push_back(p);
    }

    // Build the board matrix
    // Build empty matrix
    for (int r = 0; r < NUM_ROWS; r++) {
        vector<Cell> v(NUM_COLS);
        board.push_back(v);
    }

    // Place player pieces
    for (int i = 0; i < NUM_PLAYERS; i++) {
        Player* p = ph.player[i];

        // Find viruses of player
        for (int j = 0; j < p->all_virus.size(); j++) {
            Virus* virus = p->all_virus[j];
            board[virus.coords.r][virus.coords.c] = {i, VIRUS, virus.level};
        }

        // Find data of player
        for (int j = 0; j < p->all_data.size(); j++) {
            Data* data = p->all_data[j];
            board[data.coords.r][data.coords.c] = {i, DATA, data.level};
        }

        // Place server ports
        for (int j = 0; j < NUM_SERVER_PORTS_PER_PLAYER; j++) {
            board[server_port_coords[i][j].r][server_port_coords[i][j].c] = {0, 'S', 0};
        }
    }
}

bool Board::isValidPos(const Coords coords) const {
    return coords.r >= 0 && coords.r <= NUM_ROWS && coords.c >= 0 && coords.c <= NUM_COLS;
}

void Board::playTurn(Coords coords, string dir) {
    Player* p = ph.players[turn_number % NUM_PLAYERS];

    // Reject move (return) if there isn't a piece on "from" coords

    // Check if "to" is OOB

    // If "to" is OOB, check if it's on the opposite side

    // Otherwise, reject move

    // Reject move if there's a friendly piece on "to"

    // Check if there's a port on the "to" coords

    // Check if there's an enemy piece on "to"

    // Otherwise, just 

    turn_number++;
}
