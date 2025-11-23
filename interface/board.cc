export module Board;
import ISubject;
import IObserver;
import Link;
import PlayerHeader;
import <vector>;

using namespace std;

export class Board : public ISubject {
    public:
        int turn_number = 0;
        vector<vector<Link*>> board;
        void playTurn(PlayerHeader &ph, int turn_number);
        ~Board();
};
