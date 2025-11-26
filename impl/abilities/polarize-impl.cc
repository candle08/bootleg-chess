module Gameplay;

import Coords;
import Link;
import Data;
import Virus;

import <string>;
import <algorithm>;
import <vector>;

using namespace std;

Polarize::Polarize(): Ability{'P'} {}

string Polarize::usePower(Board &b, Coords &c, Link * link1, Link * link2, Player * p) {
    if (link1) {
        // changing the type of the link from data to virus or vice versa
        // and updating the corresponding vectors in player
        if (link1->type == "data") {
            link1->type = "virus";
            
            // Find and remove the Data object from data vector
            auto data_it = find(p->all_data.begin(), p->all_data.end(), static_cast<Data*>(link1));
            if (data_it != p->all_data.end()) {
                p->all_data.erase(data_it);
            }
            
            // Add as Virus to all_virus
            Virus* virus = static_cast<Virus*>(link1);
            p->all_virus.push_back(virus);
            
        } else {
            link1->type = "data";
            
            // Find and remove the Virus object from all_virus
            auto virus_it = find(p->all_virus.begin(), p->all_virus.end(), static_cast<Virus*>(link1));
            if (virus_it != p->all_virus.end()) {
                p->all_virus.erase(virus_it);
            }
            
            // Add as Data to all_data
            Data* data = static_cast<Data*>(link1);
            p->all_data.push_back(data);
        }

        return "";
    } else {
        return "link1 nullptr bruh";
    }
}
