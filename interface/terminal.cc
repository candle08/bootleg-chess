export module Terminal;
import Board;
import GUI;
import IObserver;
import <iostream>;
import PlayerHeader;

using namespace std;

export class Terminal : public GUI {
    public:
        void notify(const IObserver & b) override;
        void printOutput(ostream& o, Board &b);
};

void print_player_info(ostream& o, Board &b, PlayerHeader & ph, int player);
