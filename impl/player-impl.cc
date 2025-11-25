module Player;

import <vector>;

import LinkBoost;
import Firewall;
import Polarize;
import Scan;
import SmallSwap;
import TwoSum; 
import DoubleDown; 
import Download;
import Virus;
import Data;

using namespace std;

Player::Player(string link_ordering, string abilities_selected, vector<Coords> positions, vector<char> symbols, int id): id{id} {
    alive = true;
    
    // initialize link_ordering
    for (int i = 0; i < link_ordering.length(); i += 2) {
        int level = link_ordering[i + 1] - '0';
        if (link_ordering[i] == 'D' || link_ordering[i] == 'd') {
            all_data.push_back(new Data{level, positions[i / 2], symbols[i / 2]});
        } else {
            all_virus.push_back(new Virus{level, positions[i / 2], symbols[i / 2]});
        }
    }

    // initialize abilities
    for (int i = 0; i < abilities_selected.length(); i++) {
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
    for (int i = 0; i < all_data.size(); i++) {
        if (all_data[i]->symbol == link) {
            return all_data[i];
        }
    }

    for (int i = 0; i < all_virus.size(); i++) {
        if (all_virus[i]->symbol == link) {
            return all_virus[i];
        }
    }

    return nullptr;
}

string Player::useAbility(char ability, Board& b, Coords& c, string link) {
    for (auto it = abilities.begin(); it != abilities.end(); it++) {
        if (it->name == ability) {
            Link* link_pointer = getLinkPointerFromString(link)
            string retval = it->usePower(b, c, link_pointer);
            abilities.erase(it);
            return retval;
        }
    }   
    return "Invalid input: player does not have that ability";
}

Player::~Player() {
    for (int i = 0; i < all_virus.size(); i++) {
        delete all_virus[i];
    }
    for (int i = 0; i < all_data.size(); i++) {
        delete all_data[i];
    }
    for (int i = 0; i < abilities.size(); i++) {
        delete abilities[i];
    }
}

void Player::download(Link* link, Board& b) {
    link->download_status = true;
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