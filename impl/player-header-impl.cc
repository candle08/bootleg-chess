module Gameplay;

import <iostream>;
import <vector>;
using namespace std;
PlayerHeader::~PlayerHeader() {
    if (Board::DEBUG) cerr << "player header dtor" << endl;
    for (int i = 0; i < Board::NUM_PLAYERS; i++) {
        if (Board::DEBUG) cerr << "deleting player " << i << endl;
        delete players[i];
    }
}
