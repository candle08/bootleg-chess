export module Terminal;
import Board;

using namespace std;

export class Terminal : public GUI {
    public:
    
    &ostream operator<<(&, Board &b, int player);
    void notify(const Board & b)
};
