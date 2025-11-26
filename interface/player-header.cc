export module PlayerHeader;
import <vector>;

using namespace std;

export struct PlayerHeader {
    vector<Player*> players;
    int num_players;
    void addPlayer(Player* p);
    ~PlayerHeader();
};
