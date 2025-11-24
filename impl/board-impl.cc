module Board;

import ISubject;
import IObserver;
import Link;
import PlayerHeader;
import Player;
import <vector>;

using namespace std;

void Cell::clear() {
    player = -1;
    item = '\0';
    level = -1;
}

Board::Board(vector<string> link_orderings, vector<string> ability_selections) {
    turn_number = 0;
    ability_used = false;

    // Create the players
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
            board[server_port_coords[i][j].r][server_port_coords[i][j].c] = {j, 'S', 0};
        }
    }
}

bool Board::isValidPos(const Coords coords) const {
    return coords.r >= 0 && coords.r <= NUM_ROWS && coords.c >= 0 && coords.c <= NUM_COLS;
}

string Board::move(string link, string dir) {
    // Check if link is alive
    int player_id = turn_number % NUM_PLAYERS;
    if (ph.players[player_id]->getLinkPointerFromString(link)->download_status) {
        return "Invalid input: Link is no longer alive";
    }
    // Check if the link will stay on the board
    
    // move the piece
        

    turn_number++;
    ability_used = false;
}

string Board::useAbility(char ability, Coords coords, string link) {
    if (ability_used) {
        return "Invalid input: ability has already been used this turn";
    }
    ability_used = true;

    return ph.players[turn_number % NUM_PLAYERS]->useAbility(ability, *this, coords, link,);
}




