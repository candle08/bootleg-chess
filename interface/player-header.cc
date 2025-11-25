export module PlayerHeader;
import Player;
import <vector>;

using namespace std;

export struct PlayerHeader {
    vector<Player*> players;
    int num_players;
    void addPlayer(Player* p);
    ~PlayerHeader();
};
