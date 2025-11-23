module PlayerHeader;

import vector;

import Player;

void Player::addPlayer(Player *p) {
    players.push_back(p);
    num_players++;
}

PlayerHeader::~PlayerHeader() {
    for (int i = 0; i < num_headers; i++) {
        delete players[i];
    }
}