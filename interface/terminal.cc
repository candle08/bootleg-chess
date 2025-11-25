export module Terminal;
import Board;
import GUI;

using namespace std;

export class Terminal : public GUI {
    public:
        void notify(const Board & b) override;
        string printOutput(ostream& o, Board &b);
};

void print_player_info(&ostream o, Board &b, PlayerHeader & ph, int player);
