export module PlayerHeader;
import Player;
import <vector>;

export class PlayerHeader {
    vector<Player*> players;

    int num_players;
    public:
        ~PlayerHeader();
};
