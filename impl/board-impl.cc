module Gameplay;


import Observer;
import Link;
import Coords;
import Virus;
import Data;

import <vector>;
import <algorithm>;
import <string>;
import <iostream>;
import <stdexcept>;

using namespace std;

Cell::Cell() : player{-1}, item{Board::EMPTY}, level{-1}, symbol{Board::EMPTY}, firewall{false} {}

Cell::Cell(int player, char item, int level, char symbol, bool firewall): player{player}, item{item}, level{level}, symbol{symbol}, firewall{firewall} {}

void Cell::clear() {
    // debug
    cerr << "clearing cell\n";
    player = -1;
    item = Board::EMPTY;
    level = -1;
}

ostream& operator<<(ostream& o, const Cell& cell) {
    o << "Cell{ player: " << cell.player << ", item: " << cell.item << ", level: " << cell.level << ", firewall: " << cell.firewall << " }";
    return o;
}

Cell& Cell::operator=(const Cell& other) {
    player = other.player;
    item = other.item;
    level = other.level;
    symbol = other.symbol;
    return *this;
}

Board::Board(vector<string> link_orderings, vector<string> ability_selections) {
    // debug 
    cerr << "board ctor called:" << endl;
    for (size_t i = 0; i < link_orderings.size(); i++) {
        cerr << "link ordering " << i << ": " << link_orderings[i] << endl;
    }
    for (size_t i = 0; i < ability_selections.size(); i++) {
        cerr << "ability_selections " << i << ": " << ability_selections[i] << endl;
    }
    
    turn_number = 0;
    ability_used = false;
    winner = -1;
    double_down = false;

        // debug
    cerr << "turn num " << turn_number << " ability used " << ability_used
    << " winner " << winner << " double down " << double_down << "\n";

    // Create the players
    //debug
    cerr << "creating the player header\n";
    ph = PlayerHeader{};
    for (int i = 0; i < NUM_PLAYERS; i++) {
        // debug
        cerr << "player " << i << " made with: link ordering " << link_orderings[i] << ", ability_selections " << ability_selections[i] <<
        ", symbols ";
        for (int j = 0; j < 8; j++) {
            cerr << symbols[i][j];
        }
        cerr << endl;
        Player* p = new Player{link_orderings[i], ability_selections[i], link_starting_coords[i], symbols[i], i};
        
        // debug
        cerr << "this player's all_data: " << endl;
        for (size_t i = 0; i < p->all_data.size(); i++) {
            cerr << p->all_data[i]->symbol << p->all_data[i]->level;
        }
        cerr << endl;

        cerr << "this player's all_virus: " << endl;
        for (size_t i = 0; i < p->all_virus.size(); i++) {
            cerr << p->all_virus[i]->symbol << p->all_virus[i]->level;
        }
        cerr << endl;

        ph.players.push_back(p);
    }

    // Build the board matrix
    // Build empty matrix
    // debug
    cerr << "building the empty board matrix\n";
    for (int r = 0; r < NUM_ROWS; r++) {
        vector<Cell> v(NUM_COLS);
        board.push_back(v);
    }

    // debug
    cerr << "board is " << NUM_ROWS << " rows by " << NUM_COLS << " cols" << endl;

    // Place player pieces

    //debug
    cerr << "placing the player pieces\n";
    for (int i = 0; i < NUM_PLAYERS; i++) {
        Player* p = ph.players[i];

        // debug
        cerr << "PLAYER " << i << endl;

        // Find viruses of player
        for (size_t j = 0; j < p->all_virus.size(); j++) {
            Virus* virus = p->all_virus[j];
            board[virus->coords.r][virus->coords.c] = Cell{i, VIRUS, virus->level, Board::EMPTY, false};
            // debug
            cerr << "placing virus level " << virus->level << " at (r, c): " << virus->coords.r << ", " << virus->coords.c << endl;
        }

        // Find data of player
        for (size_t j = 0; j < p->all_data.size(); j++) {
            Data* data = p->all_data[j];
            board[data->coords.r][data->coords.c] = Cell{i, DATA, data->level, Board::EMPTY, false};
            // debug
            cerr << "placing data level " << data->level << " at (r, c): " << data->coords.r << ", " << data->coords.c << endl;
        }

        // Place server ports
        for (int j = 0; j < NUM_SERVER_PORTS_PER_PLAYER; j++) {
            board[server_port_coords[i][j].r][server_port_coords[i][j].c] = Cell{j, SERVER, -1, Board::EMPTY, false};
            // debug
            cerr << "placing server port at " << server_port_coords[i][j].r << ", " << server_port_coords[i][j].c << endl;
        }
    }

    
}

bool Board::isValidPos(const Coords coords) const {
    return coords.r >= 0 && coords.r <= NUM_ROWS && coords.c >= 0 && coords.c <= NUM_COLS;
}

string Board::move(char link, string dir) {
    int player_id = getCurrentPlayerID();
    Link *link_ptr = ph.players[player_id]->getLinkPointerFromChar(link);
    string retval = "";
    try {
        // debug
        cerr << "player_id " << player_id << endl;
        cerr << "turn number: " << turn_number << endl;
        if (link_ptr == nullptr) {
            throw logic_error("Invalid input: No link associated with symbol " + to_string(link));
        }
        if (link_ptr->download_status) {
            throw logic_error("Invalid input: Link is no longer alive");
        }
    
        Coords old_posn = link_ptr->coords;
        Coords new_posn = link_ptr->coords;
        // debug
        cerr << "new_posn: r " << new_posn.r << ", c " << new_posn.c << endl;
        cerr << "link_ptr->level " << link_ptr->level << endl;
    
        // Checking if user is not frozen from twosum
        if (link_ptr->frozen_on_turn != -1 && turn_number < link_ptr->frozen_on_turn + link_ptr->level * 2) {
            // debug
            throw logic_error("Invalid input: link is frozen for " + to_string(((turn_number - link_ptr->frozen_on_turn - link_ptr->level * 2) / 2)) + "more moves");
        }
        cerr << "passed frozen check" << endl;
        
        // Check if the link will stay on the board
        // check if moving onto board, server port, out of bounds, opponent's edge
        // Using LinkBoost ability
        if (link_ptr->linkboost) {
            if (dir == "up") {
                new_posn.r-= 2;
            } else if (dir == "down") {
                new_posn.r+= 2;
            } else if (dir == "left") {
                new_posn.c-= 2;
            } else if (dir == "right") {
                new_posn.c+= 2;
            }
        } else {
            if (dir == "up") {
                new_posn.r--;
            } else if (dir == "down") {
                new_posn.r++;
            } else if (dir == "left") {
                new_posn.c--;
            } else if (dir == "right") {
                new_posn.c++;
            }
        }
        
    
        Cell& new_place = board[new_posn.r][new_posn.c];
        cerr << "new_posn.r " << new_posn.r << ", new_posn.c " << new_posn.c << endl;
        cerr << "player_id " << player_id << endl;
        
        if ((player_id == 1 && new_posn.r < 0) || (player_id == 0 && new_posn.r >= NUM_ROWS)) {
            // Opponent's edge
            ph.players[player_id]->download(link_ptr, *this);
    
        } else if (!isValidPos(new_posn)) {
            // Out of bounds
            throw logic_error("Invalid Input: You cannot move to this cell");
    
        } else if ((new_place.item == SERVER || new_place.item == DATA || new_place.item == VIRUS) 
            && new_place.player == player_id) {
            // Player's own links/servers
            throw logic_error("Invalid Input: You cannot move to this cell");
    
        } else if (new_place.item == SERVER && new_place.player != player_id) {
            // Opponent's server port
            ph.players[new_place.player]->download(link_ptr, *this);
    
        } else if ((new_place.item == DATA || new_place.item == VIRUS) 
            && new_place.player != player_id) {
            // Moving onto opponent's link --> initiates a battle
            if (link_ptr->level >= new_place.level) {
                ph.players[player_id]->download(ph.players[new_place.player]->getLinkPointerFromChar(new_place.item), *this);
                link_ptr->coords = Coords{new_posn.r, new_posn.c};
                board[new_posn.r][new_posn.c] = Cell{player_id, link_ptr->type, link_ptr->level, link_ptr->symbol, false};
            } else {
                ph.players[new_place.player]->download(link_ptr, *this);
            }
        } else {
            // Invalid: out of bounds, own server port, or own link
            if (!isValidPos(new_posn)|| 
            ((new_place.item == SERVER || new_place.item == DATA || new_place.item == VIRUS) && new_place.player == player_id)) {
                throw logic_error("Invalid Input: You cannot move to this cell");
            }
            
            // Update new cell
            board[new_posn.r][new_posn.c] = board[old_posn.r][old_posn.c];
            
            // Update link coords
            link_ptr->move(Coords{new_posn.r, new_posn.c});
        }
        
        // Make sure previous spot is now empty cell
        board[old_posn.r][old_posn.c].clear();
        cerr << "printing out previous, cleared cell after move " << board[link_ptr->coords.r][link_ptr->coords.c] << endl;
    
        // Checking ability usage
        if (double_down) {
            double_down = false;
            ability_used = true;
        } else {
            turn_number++;
            ability_used = false;
        }
    
        cerr << "printing out double_down, ability_used, turn_number (in this order) " << double_down << ability_used << turn_number << endl;
    
        // Using firewall ability after move has been made
        if (board[new_posn.r][new_posn.c].firewall && board[new_posn.r][new_posn.c].player != player_id) { // firewall ability activated
            cerr << "board[new_posn.r][new_posn.c].firewall && board[new_posn.r][new_posn.c].player != player_id  returned true " << endl;
            link_ptr->revealed = true;
            if (link_ptr->type == Board::VIRUS) {
                ph.players[player_id]->download(link_ptr, *this);
            }
        }
    
    
        // Notify the observers
        notifyObservers();
    } catch (const logic_error& e) {
        retval = string(e.what());
    }

    delete link_ptr;

    // debug
    cerr << "MOVE HAS COMPLETED" << endl;

    return retval;
}

string Board::useAbility(char ability, Coords coords, char link1, char link2) {
    //debug
    cerr << "board's useAbility called for ability " << ability << " with link1: " << link1 <<
    " and link2: " << link2 << "\n";
    // Check if ability has already been used
    if (ability_used) {
        return "Invalid input: ability has already been used this turn";
    }

    cerr << "calling player's use ability in board\n";
    string retval = ph.players[turn_number % NUM_PLAYERS]->useAbility(ability, *this, coords, link1, link2);
    if (retval == "") {
    // Ability use succeeded
        ability_used = true;
        notifyObservers();
    }
    return retval;
}

Player* Board::getCurrentPlayer() {
    return ph.players[getCurrentPlayerID()];
}

int Board::getCurrentPlayerID() {
    return turn_number % NUM_PLAYERS;
}

void Board::win(int p) {
    winner = p;
}

void Board::checkWinCondition() {
    int winner = -1;
    for (size_t i = 0; i < ph.players.size(); i++) {
        if (ph.players[i]->alive) {
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

void Board::subscribe(IObserver* o) {
    observers.push_back(o);
}

void Board::unsubscribe(IObserver* o) {
    observers.erase(find(observers.begin(), observers.end(), o));
}   

void Board::notifyObservers() {
    for (auto o : observers) {
        o->notify(*this);
    }
}

Board::~Board() {
    for (auto o : observers) {
        delete o;
    }
}
