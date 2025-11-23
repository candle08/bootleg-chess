module Board;
// hi tongtong
import ISubject;
import IObserver;
import Link;
import PlayerHeader;
import <vector>;

using namespace std;
// shall i write a ctor?
// nvm nvm i understand it now
// wait do we need one yuh
// do we need a ctor tho
// gyatt
// yuh hmm okok
// wait
// wdym row
// no row is stored within link
// hm
//.
// .
// .
// wdym?
// acc ok
// our field is pointers
// i think we need a ctor after all
// and then we set it based on input from playerheader
// okok ya we do 
// what would the input be? wdym from ph
// ph is a wrapper ffor player, since we "technica" dont know how many players there are 
// so we pass in playerheader which has players
// and then the players will have arrays of data and virus
// and based on the coords iwthin we can initialize links to point to diff stuff ykwim

// like r we straight up passing in a m

// ctor
// HELLO
// dawg is this right i dont understand refs and ptrs ngl
Board::Board(PlayerHeader &ph) {
    for (auto * player : ph.players) {
        for (auto * virus : player->all_virus) {
            board[][] = ;
        }

        for (auto * data : player->all_data) {

        }
    }

}

bool Board::valid_pos(const Coords c) {
    
}

void Board::playTurn(PlayerHeader &ph, int turn_number) {

    
    turn_number++;
}

Board::~Board() { // I THINK double check if this is right
    // vec should auto deallocate and im just deleting pointers
    for (auto row : board) {
        for (auto * link : row) {
            delete link;
        }
    }
}