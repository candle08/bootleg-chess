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
    int opponent_id = (turn_number + 1) % NUM_PLAYERS;

    Link *link_ptr = ph.players[player_id]->getLinkPointerFromString(link);
    if (link_ptr->download_status) {
        return "Invalid input: Link is no longer alive";
    }
    // for player 1, start on rows 6 and 7. moving up means row decreases
    // for player 2, start on rows 0 and 1. moving up means row increases
    // p1, down means row increases
    // p2, down means row decreases
    // left and right same for p1, p2

    // Check if the link will stay on the board
    if (dir == "up") {
        if (player_id == 0) {
            if (link_ptr->coords.r - 1 < 0) {
                link_ptr->download_status = true;
                ph.players[player_id]->downloaded.emplace_back(link_ptr);
            }
        } else {

        }
    } else if (dir == "down") {
        if (player_id == 0) {

        } else {

        }
    } else if (dir == "left") {

    } else if (dir == "right") {

    }
    // move the piece, make sure you leave behind empty cell or server port
        
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




