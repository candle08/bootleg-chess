module Gameplay;

import <vector>;
using namespace std;
void PlayerHeader::addPlayer(Player *p) {
    players.push_back(p);
    num_players++;
}

PlayerHeader::~PlayerHeader() {
    for (int i = 0; i < num_players; i++) {
        delete players[i];
    }
}
