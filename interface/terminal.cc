export module Terminal;
import Gameplay;
import GUI;
import Observer;
import <iostream>;

using namespace std;

export class Terminal : public GUI {
    public:
        Terminal(const ISubject & b);
        void notify(const ISubject & b) override;

        /**
         * Prints output to terminal
         */
        void printOutput(ostream& o, Board &b);
        ~Terminal() = default;
        /**
        * Prints each individual player header
        */
        void print_player_info(ostream & o, Board & b, PlayerHeader & ph, int player, bool owner);
};
