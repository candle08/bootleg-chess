module Gameplay;

import Coords;
import Link;

import <string>;
import <iostream>;
import <vector>;

using namespace std;

TwoSum::TwoSum(): Ability{'T'} {}

string TwoSum::usePower(Board &b, vector<char> args, Player * p) {
    //debug
    cerr << "two sum called\n";
    if (args.size() != 1) {
        return "Invalid input for TwoSum: invalid number of args";
    }

    char symbol = args[0];
    PlayerHeader& ph = b.ph;
    for (size_t i = 0; i < ph.players.size(); i++) {
        if (ph.players[i]->id != p->id) {
            for (size_t j = 0; j < ph.players[i]->all_data.size(); j++) {
                if (ph.players[i]->all_data[j]->symbol == symbol) {
                    ph.players[i]->all_data[j]->frozen_on_turn = b.turn_number;
                    return "";
                }
            }

            for (size_t j = 0; j < ph.players[i]->all_virus.size(); j++) {
                if (ph.players[i]->all_virus[j]->symbol == symbol) {
                    ph.players[i]->all_data[j]->frozen_on_turn = b.turn_number;
                    return "";
                }
            }
        }
    }

    return "Error in TwoSum: link not found for symbol";
}
