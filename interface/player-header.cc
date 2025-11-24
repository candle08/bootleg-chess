export module PlayerHeader;
import Player;
import <vector>;

export class PlayerHeader {
    vector<Player*> players;

    int num_players;
    public:
        void addPlayer(Player* p);
        ~PlayerHeader();
        friend class Board;
};
