export module Terminal;
import Board;
import GUI;

using namespace std;

export class Terminal : public GUI {
    public:
        &ostream operator<<(&, Board &b, int player);
        void notify(const Board & b) override;
};
