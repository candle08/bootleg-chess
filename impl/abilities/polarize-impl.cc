module Polarize;

string Polarize::usePower(Board &b, Coords &c, Link * link1, Link * link2, Player * p) override {

    // changing the type of the link from data to virus or vice versa and deleting the link from its corresponding vector in player
    if (link1->type == "data") {
        link1->type = "virus";
        p->all_data.erase(find(p->all_data.begin(), p->all_data.end(), this));
        p->all_virus.push_back(link);
    } else {
        link1->type = "data";
        p->all_virus.erase(find(p->all_virus.begin(), p->all_virus.end(), this));
        p->all_data.push_back(link);
    }

    return "";
}