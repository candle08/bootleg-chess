export module Board;
import ISubject;
import IObserver;
import Link;
import PlayerHeader;
import Coords;
import <vector>;

using namespace std;

export class Board : public ISubject {
    Board(PlayerHeader &ph);
    bool valid_pos(const Coords c);
    
    public:
        int turn_number = 0;
        vector<vector<Link*>> board;
        void playTurn(PlayerHeader &ph, int turn_number);
        ~Board();
};
