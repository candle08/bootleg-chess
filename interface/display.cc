export module Display;
import Board;
import GUI;
import PlayerHeader;

using namespace std;

export class Display : public GUI {
    public:
        &ostream operator<<(&, Board &b, PlayerHeader & ph, int player) override;
        void notify(const Board & b) override;
};
