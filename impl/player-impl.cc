module Gameplay;

import <vector>;
import <iostream>;

import Virus;
import Data;

using namespace std;

Player::Player(string link_ordering, string abilities_selected, vector<Coords> positions, vector<char> symbols, int id): id{id} {
    alive = true;
    
    // initialize link_ordering
    for (size_t i = 0; i < link_ordering.length(); i += 2) {
        int level = link_ordering[i + 1] - '0';
        if (link_ordering[i] == 'D' || link_ordering[i] == 'd') {
            all_data.push_back(new Data{level, positions[i / 2], symbols[i / 2]});
        } else {
            all_virus.push_back(new Virus{level, positions[i / 2], symbols[i / 2]});
        }
    }

    // initialize abilities
    for (size_t i = 0; i < abilities_selected.length(); i++) {
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
}

Link* Player::getLinkPointerFromChar(char link) {
    // If link is a Data

    for (size_t i = 0; i < all_data.size(); i++) {
        cerr << "getting link ptr from char, checking data\n";
        if (all_data[i]->symbol == link) {
            return all_data[i];
        }
    }

    // If link is a Virus
    for (size_t i = 0; i < all_virus.size(); i++) {
        cerr << "getting link ptr from char, checking virus\n";
        if (all_virus[i]->symbol == link) {
            return all_virus[i];
        }
    }

    return nullptr;
}

string Player::useAbility(char ability, Board& b, Coords& c, char link1, char link2) {
    // debug
    cerr << "in player's use ability now \n";
    for (auto it = abilities.begin(); it != abilities.end(); it++) {
        // Check that the player has the ability, use and remove it.
        cerr << "checking that the player as the ability: " << ability << "with link 1: "
        << link1 << " and link2: " << link2 << "\n";
        if ((*it)->symbol == ability) {
            cerr << "currently iterator in useability is the symbol: " << (*it)->symbol << "\n";
            Link* link_pointer1 = getLinkPointerFromChar(link1);
            if (!link_pointer1) cerr << "link_pointer1 is null\n";
            Link* link_pointer2 = getLinkPointerFromChar(link2);
            if (!link_pointer2) cerr << "link_pointer2 is null\n";

            string retval = (*it)->usePower(b, c, link_pointer1, link_pointer2, this);
            abilities.erase(it);
            return retval;
        }
    }   
    return "Invalid input: player does not have that ability";
}

Player::~Player() {
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

    // Remove the link from the board
    link->coords = {-1, -1};
    if (link->type == "data") {
        num_data_downloaded++;
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
