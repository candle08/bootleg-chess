export module Player;
import Virus;
import Data;
import Ability;
import <vector>;

using namespace std;

export class Player {
    vector<Virus *> all_virus;
    vector<Data *> all_data;
    vector<Ability *> abilities;

    public:
        Player(vector<Virus *> v, vector<Data *> d, vector<Ability *> a);
        ~Player();
};
