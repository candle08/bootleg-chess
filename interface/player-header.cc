export module PlayerHeader;

import <vector>;

import Player;

export class PlayerHeader {
    vector<Player*> players;

    int num_players;
    ~PlayerHeader();
};
