module Gameplay;

import Coords;
import Link;

import <vector>;
import <string>;
import <iostream>;

using namespace std;

SmallSwap::SmallSwap(): Ability{'W'} {}

string SmallSwap::usePower(Board &b, vector<char> args, Player * p) {
    //debug
    cerr << "small swap called\n";

    if (args.size() != 2) {
        return "Invalid input for SmallSwap: invalid number of arguments";
    }

    PlayerHeader& ph = b.ph;

    Link* link1 = nullptr;
    Link* link2 = nullptr;
    char symbol1 = args[0];
    char symbol2 = args[1];

    // find link 1
    for (size_t i = 0; i < ph.players.size(); i++) {
        if (ph.players[i]->id == p->id) { // link1
            for (size_t j = 0; j < ph.players[i]->all_data.size(); j++) {
                if (ph.players[i]->all_data[j]->symbol == symbol1) {
                    link1 = (Link*)ph.players[i]->all_data[j];
                    break;
                }
            }

            if (link1 != nullptr) {
                break;
            }

            for (size_t j = 0; j < ph.players[i]->all_virus.size(); j++) {
                if (ph.players[i]->all_virus[j]->symbol == symbol1) {
                    link1 = (Link*)ph.players[i]->all_virus[j];
                    break;
                }
            }
        } else {
            for (size_t j = 0; j < ph.players[i]->all_data.size(); j++) {
                if (ph.players[i]->all_data[j]->symbol == symbol2) {
                    link2 = (Link*)ph.players[i]->all_data[j];
                    break;
                }
            }

            if (link2 != nullptr) {
                break;
            }

            for (size_t j = 0; j < ph.players[i]->all_virus.size(); j++) {
                if (ph.players[i]->all_virus[j]->symbol == symbol2) {
                    link2 = (Link*)ph.players[i]->all_virus[j];
                    break;
                }
            }
        }
    }

    if (link1 == nullptr || link2 == nullptr) {
        return "Error in small swap: link not found";
    }

    swap(*link1, *link2);
    return "";
}
