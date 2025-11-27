module Gameplay;

import <vector>;
import <iostream>;
import <algorithm>;
import <iostream>;

import Virus;
import Data;

using namespace std;

Player::Player(string link_ordering, string abilities_selected, vector<Coords> positions, vector<char> symbols, int id): id{id} {
    // debug
    cerr << endl << "PLAYER CTOR " << endl;
    
    alive = true;
    
    // initialize link_ordering
    for (size_t i = 0; i < link_ordering.length(); i += 2) {
        int level = link_ordering[i + 1] - '0';
        if (link_ordering[i] == 'D' || link_ordering[i] == 'd') {
            // debug
            cerr << "initializing data: level: " << level << ", coords: (" << positions[i / 2].r << ", " << positions[i / 2].c << "), symbol: " << symbols[i / 2] << endl; 
            all_data.push_back(new Data{level, positions[i / 2], symbols[i / 2]});
        } else {
            // debug
            cerr << "initializing virus: level: " << level << ", coords: (" << positions[i / 2].r << ", " << positions[i / 2].c << "), symbol: " << symbols[i / 2] << endl; 
            all_virus.push_back(new Virus{level, positions[i / 2], symbols[i / 2]});
        }
    }

    // initialize abilities
    for (size_t i = 0; i < abilities_selected.length(); i++) {
        // debug
        cerr << "ability: " << abilities_selected[i] << endl;
        if (abilities_selected[i] == 'L') {
            abilities.push_back(new LinkBoost{});
        } else if (abilities_selected[i] == 'D') {
            abilities.push_back(new Download{});
        } else if (abilities_selected[i] == 'B') {
            abilities.push_back(new DoubleDown{});
        } else if (abilities_selected[i] == 'F') {
            abilities.push_back(new Firewall{});
        } else if (abilities_selected[i] == 'P') {
            abilities.push_back(new Polarize{});
        } else if (abilities_selected[i] == 'T') {
            abilities.push_back(new TwoSum{});
        } else if (abilities_selected[i] == 'S') {
            abilities.push_back(new Scan{});
        } else {
            abilities.push_back(new SmallSwap{});
        }
    }
    // debug
    cerr << endl << "END OF PLAYER CTOR " << endl;
}

Link* Player::getLinkPointerFromChar(char link) {
    // If link is a Data
    // cerr << endl << "CHECKING GET LINK PTR FROM CHAR" << endl;
    
    for (size_t i = 0; i < all_data.size(); i++) {
        // cerr << "all data[i] symbol is " << all_data[i]->symbol << endl;
        if (all_data[i]->symbol == link) {
            // cerr << "found data!!";
            return all_data[i];
        }
    }
    
    // If link is a Virus
    for (size_t i = 0; i < all_virus.size(); i++) {
        // cerr << "all virus[i] symbol is " << all_data[i]->symbol << endl;
        if (all_virus[i]->symbol == link) {
            // cerr << "found virus!!";
            return all_virus[i];
        }
    }

    // cerr << "found nothing" << endl;

    return nullptr;
}

string Player::useAbility(int id, vector<char> args, Board& b) {
    // debug
    cerr << "in player's use ability now \n";
    if (!abilities[id]->used) {
        string retval = abilities[id]->usePower(b, args, this);
        if (retval == "") {
            abilities[id]->used = true;
        }
        return retval;
    } else {
        return "Ability has already been used";
    }
}

Player::~Player() {
    cerr << "player dtor" << endl;

    for (size_t i = 0; i < all_virus.size(); i++) {
        delete all_virus[i];
    }
    for (size_t i = 0; i < all_data.size(); i++) {
        delete all_data[i];
    }
    for (size_t i = 0; i < abilities.size(); i++) {
        delete abilities[i];
    }
}

void Player::download(Link* link, Board& b) {
    link->download_status = true;
    if (!link) {
        cerr << "link is null\n";
    }

    // update board
    b.board[link->coords.r][link->coords.c].clear();

    // Remove the link from the board
    link->coords = {-1, -1};

    if (link->type == Board::DATA) {
        num_data_downloaded++;
        cerr << "Data downloaded! we now have " << num_data_downloaded << endl;
        if (num_data_downloaded >= b.NUM_DATA_DOWNLOADED_TO_WIN) {
            b.win(id);
        }
    } else {
        num_virus_downloaded++;
        if (num_virus_downloaded >= b.NUM_VIRUS_DOWNLOADED_TO_LOSE) {
            alive = false;
            b.checkWinCondition();
        }
    }
}
