module Gameplay;

import Coords;
import Link;
import Data;
import Virus;

import <string>;
import <algorithm>;
import <vector>;
import <iostream>;

using namespace std;

Polarize::Polarize(): Ability{'P'} {}

string Polarize::usePower(Board &b, vector<char> args, Player * p) {
    // debug
    cerr << "polarize called\n";
    if (args.size() != 1) {
        return "Invalid input for polarize: invalid number of abilities";
    }

    Link* link_ptr = b.getLinkPointerFromChar(args[0]);
    if (link_ptr) {
        // changing the type of the link from data to virus or vice versa
        // and updating the corresponding vectors in player
        if (link_ptr->type == Board::DATA) {
            link_ptr->type = Board::VIRUS;
            
            // Find and remove the Data object from data vector
            cerr << "in polarize, removing the data object from data vector\n";
            auto data_it = find(p->all_data.begin(), p->all_data.end(), static_cast<Data*>(link_ptr));
            if (data_it != p->all_data.end()) {
                p->all_data.erase(data_it);
                // debug
            }
            
            // Add as Virus to all_virus
            cerr << "in polarize, adding a virus to the list\n";

            Virus* virus = static_cast<Virus*>(link_ptr);
            p->all_virus.push_back(virus);
            // debug
            
        } else {
            link_ptr->type = Board::DATA;
            
            cerr << "in polarize, removing the virus from the list\n";
            // Find and remove the Virus object from all_virus
            auto virus_it = find(p->all_virus.begin(), p->all_virus.end(), static_cast<Virus*>(link_ptr));
            if (virus_it != p->all_virus.end()) {
                p->all_virus.erase(virus_it);
                // debug
            }
            
            cerr << "in polarize, adding a data to the list\n";
            // Add as Data to all_data
            Data* data = static_cast<Data*>(link_ptr);
            p->all_data.push_back(data);
            //debug
        }

        return "";
    } else {
        return "link_ptr nullptr bruh in POLARIZE";
    }
}
