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
    winner = -1;
    double_down = false;

    // Create the players
    ph = PlayerHeader{};
    for (int i = 0; i < NUM_PLAYERS; i++) {
        Player* p = new Player{link_orderings[i], ability_selections[i], link_starting_coords[i], symbols[i], i};
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

string Board::move(char link, string dir) {
    // Check if link is alive
    int player_id = getCurrentPlayerID();
    
    Link *link_ptr = ph.players[player_id]->getLinkPointerFromChar(link);

    if (link_ptr->download_status) {
        return "Invalid input: Link is no longer alive";
    }

    Coord new_posn = link_ptr->coords;

    // checking if user is not frozen from twosum
    if (link_ptr->frozen_on_turn != -1 && turn_number < link_ptr->frozen_on_turn + link_ptr->level * 2) {
        return "Invalid input: link is frozen for " + link_ptr->level - (turn_number - link->frozen_on_turn) + "more moves";
    }
    
    // Check if the link will stay on the board
    // check if moving onto board, server port, out of bounds, opponent's edge
    // Using LinkBoost ability
    if (link_ptr->linkboost = true) {
        if (dir == "up") {
            new_posn.r+= 2;
        } else if (dir == "down") {
            new_posn.r-= 2;
        } else if (dir == "left") {
            new_posn.c-= 2;
        } else if (dir == "right") {
            new_posn.c+= 2;
        }
    } else {
        if (dir == "up") {
            new_posn.r++;
        } else if (dir == "down") {
            new_posn.r--;
        } else if (dir == "left") {
            new_posn.c--;
        } else if (dir == "right") {
            new_posn.c++;
        }
    }
    

    Cell new_place = board[new_posn.r][new_posn.c];
    
    if ((player_id == 1 && new_posn.r < 0) || (player_id == 0 && new_posn.r >= NUM_ROWS)) {
        // Opponent's edge
        ph.players[player_id]->download(link_ptr);

    } else if (!isValidPos(new_posn)) {
        // Out of bounds
        return "Invalid Input: You cannot move to this cell";

    } else if ((new_place.item == SERVER || new_place.item == DATA || new_place.item == VIRUS) 
        && new_place.player == player_id) {
        // Player's own links/servers
        return "Invalid Input: You cannot move to this cell";

    } else if (new_place.item == SERVER && new_place.player != player_id) {
        // Opponent's server port
        ph.players[new_place.player]->download(link_ptr);

    } else if ((new_place.item == DATA || new_place.item == VIRUS) 
        && new_place.player != player_id) {
        // Moving onto opponent's link --> initiates a battle
        if (link_ptr->level >= new_place.level) {
            ph.players[player_id]->download(ph.player[new_place.player]->getLinkPointerFromChar(new_place.item));
            link_ptr->coords = {new_posn.r, new_posn.c};
            board[new_posn.r][new_posn.c] = {player_id, link_ptr->symbol, link_ptr->level};
        } else {
            ph.players[new_place.player]->download(link_ptr);
        }
    }
    
    // Invalid: out of bounds, own server port, or own link
    if (!isValidPos(new_posn)|| 
    ((new_place.item == SERVER || new_place.item == DATA || new_place.item == VIRUS) && new_place.player == player_id)) {
        return "Invalid Input: You cannot move to this cell";
    }

    

    // Make sure previous spot is now empty cell
    board[link_ptr->coords.r][link_ptr->coords.c] = {-1, '\0', -1};

    // Checking ability usage
    if (double_down) {
        double_down = false;
        ability_used = true;
    } else {
        turn_number++;
        ability_used = false;
    }

    // Using firewall ability after move has been made
    if (board[new_posn.r][new_posn.c]->firewall && board[new_posn.r][new_posn.c]->player != ph.players[player_id]) { // firewall ability activated
        getLinkPointerFromChar(link)->revealed = true;
        if (getLinkPointerFromChar(link)->type = "virus") {
            download(getLinkPointerFromChar(link), *this);
        }
    }

    

    // Notify the observers
    return "";
}

string Board::useAbility(char ability, Coords coords, char link1, char link2) {
    if (ability_used) {
        return "Invalid input: ability has already been used this turn";
    }
    
    string retval = ph.players[turn_number % NUM_PLAYERS]->useAbility(ability, *this, coords, link1, link2);
    if (retval == "") {
        ability_used = true;
    }
    return retval;
}

Player* Board::getCurrentPlayer() {
    return ph.players[getCurrentPlayerID()];
}

int Board::getCurrentPlayerID() {
    return turn_number % NUM_PLAYERS;
}

void win(int index) {
    winner = index;
}

void checkWinCondition() {
    int winner = -1;
    for (int i = 0; i < ph.players.size(); i++) {
        if (ph.players[i].alive) {
            if (winner != -1) {
                // at least two alive: no one has won
                return;
            } else {
                winner = i;
            }
        }
    }
    if (winner != -1) {
        win(winner);
    }
}