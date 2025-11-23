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

Player::Player(string link_ordering, string abilities_selected, vector<Coords> positions) {
    // initialize link_ordering
    for (int i = 0; i < link_ordering.length(); i += 2) {
        int level = link_ordering[i + 1] - '0';
        if (link_ordering[i] == 'D' || link_ordering[i] == 'd') {
            all_data.push_back(new Data{level, positions[i / 2]});
        } else {
            all_virus.push_back(new Virus{level, positions[i / 2]});
        }
    }

    // initialize abilities
    for (int i = 0; i < abilities_selected.length(); i++) {
        if (abilities_selected[i] == 'l' || abilities_selected[i] == 'L') {
            abilities.push_back(new LinkBoost{});
        } else if (abilities_selected[i] == 'd' || abilities_selected[i] == 'D') {
            abilities.push_back(new Download{});
        } else if (abilities_selected[i] == 'b' || abilities_selected[i] == 'B') {
            abilities.push_back(new DoubleDown{});
        } else if (abilities_selected[i] == 'f' || abilities_selected[i] == 'F') {
            abilities.push_back(new Firewall{});
        } else if (abilities_selected[i] == 'p' || abilities_selected[i] == 'P') {
            abilities.push_back(new Polarize{});
        } else if (abilities_selected[i] == 't' || abilities_selected[i] == 'T') {
            abilities.push_back(new TwoSum{});
        } else if (abilities_selected[i] == 's' || abilities_selected[i] == 'S') {
            abilities.push_back(new Scan{});
        } else {
            abilities.push_back(new SmallSwap{});
        }
    }
}

Link* Player::getLinkPointerFromString(string link) {
    if (link == "") {
        return nullptr;
    }

    if (link[0] == 'D') {
        return all_data[link[1] - '1'];
    }
    return all_virus[link[1] - '1'];
}

string Player::useAbility(char ability, Board& b, Coords& c, string link) {
    for (auto it = abilities.begin(); it != abilities.end(); it++) {
        if (it->name == ability) {
            Link* link_pointer = getLinkPointerFromString(link_pointer)
            string ret_val = it->usePower(b, c, link_pointer);
            abilities.erase(it);
            return ret_val;
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