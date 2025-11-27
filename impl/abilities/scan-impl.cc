module Gameplay;

import Coords;
import Link;

import <vector>;
import <string>;
import <iostream>;

using namespace std;

Scan::Scan(): Ability{'S'} {}

string Scan::usePower(Board &b, vector<char> args, Player * p) {
    //debug
    cerr << "Scan called\n";

    if (args.size() != 1) {
        return "Invalid input for Scan: invalid number of arguments";
    }

    PlayerHeader& ph = b.ph;
    
    // find link with symbol
    char symbol = args[0];
    for (size_t i = 0; i < ph.players.size(); i++) {
        if (ph.players[i]->id != p->id) {
            for (size_t j = 0; j < ph.players[i]->all_data.size(); j++) {
                if (ph.players[i]->all_data[j]->symbol == symbol) {
                    if (!ph.players[i]->all_data[j]->revealed) {
                        ph.players[i]->all_data[j]->revealed = true;
                        return "";
                    } else {
                        return "Error in Scan: link already revealed";
                    }
                }
            }

            for (size_t j = 0; j < ph.players[i]->all_virus.size(); j++) {
                if (ph.players[i]->all_virus[j]->symbol == symbol) {
                    if (!ph.players[i]->all_virus[j]->revealed) {
                        ph.players[i]->all_virus[j]->revealed = true;
                        return "";
                    } else {
                        return "Error in Scan: link already revealed";
                    }
                }
            }
        }
    }

    return "Invalid input in scan: link not found";
}
