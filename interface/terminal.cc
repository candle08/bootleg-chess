export module Terminal;
import Board;

export class Terminal : public GUI {
    public:
    
    &ostream operator<<(&, Board &b, int player);
    void notify(const Board & b)
};
