export module Board;
import ISubject;
import IObserver;
import Link;
import PlayerHeader;

export class Board : public ISubject {
    public:
    int turn_num;
    vector<vector<Link>> board;
    void play_turn(PlayerHeader & ph, int turn_num);
    ~Board();
};

// hi