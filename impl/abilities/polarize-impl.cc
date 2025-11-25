module Polarize;

string Polarize::usePower(Board &b, Coords &c, Link * link, Player * p) override {

    // changing the type of the link from data to virus or vice versa and deleting the link from its corresponding vector in player
    if (link->type == "data") {
        link->type = "virus";
        p->all_data.erase(find(p->all_data.begin(), p->all_data.end(), this));
    } else {
        link->type = "data";
        p->all_virus.erase(find(p->all_virus.begin(), p->all_virus.end(), this));
    }
    
    // iterates through abilities and deletes that ability
    p->abilities.erase(find(p->abilities.begin(), p->abilities.end(), this));
}