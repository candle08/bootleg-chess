export module Board;
import ISubject;
import IObserver;
import Link;
import PlayerHeader;
import <vector>;

using namespace std;

export class Board : public ISubject {
    public:
    int turn_num = 0;
    vector<vector<Link>> board;
    void play_turn(PlayerHeader &ph, int turn_num);
    ~Board();
};
