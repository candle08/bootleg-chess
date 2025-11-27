import <iostream>;
import <vector>;
import <algorithm>;
import <string>;
import <fstream>;
import <map>;

import Data;
import Virus;
import Graphic;
import Terminal;
import Gameplay;

using namespace std;

int main(int argc, char* argv[]) {

    // ----- COMMAND LINE READER -----
    string prev_arg = "";

    /**
     * L: LinkBoost
     * F: Firewall
     * D: Download
     * S: Scan
     * P: Polarize
     * B: DoubleDown
     * T: TwoSum
     * W: SmallSwap
     */
    const vector<char> ABILITY_LETTERS = {'L', 'F', 'D', 'S', 'P', 'B', 'T', 'W'};
    
    const map<char, string> ABILITY_NAMES = {
        {'L', "Link Boost"},
        {'F', "Firewall"},
        {'D', "Download"},
        {'S', "Scan"},
        {'P', "Polarize"},
        {'B', "Double Down"},
        {'T', "TwoSum"},
        {'W', "Small Swap"}
    };

    string ability1 = "LFDSP", ability2 = "LFDSP";
    string link1 = "V1V2V3V4D1D2D3D4", link2 = "V1V2V3V4D1D2D3D4";
    bool graphics_enabled = false;

    for (int i = 1; i < argc; i++) {
        string cur_arg = argv[i];
        if (prev_arg != "") {
            if (prev_arg == "-ability1" || prev_arg == "-ability2") {
                // validate length
                if (cur_arg.length() != Board::NUM_ABILITIES) {
                    cerr << "Parameter for " << prev_arg << " is not length " << Board::NUM_ABILITIES << endl;
                    return 1;
                }

                // validate that the argument only has characters valid letters, and that each letter appears no more than twice
                map<char, int> ability_counts;
                for (int j = 0; j < Board::NUM_ABILITIES; j++) {
                    // check that all letters are valid
                    int index_of_letter = -1;
                    for (size_t k = 0; k < ABILITY_LETTERS.size(); k++) {
                        if (cur_arg[j] == ABILITY_LETTERS[k]) {
                            index_of_letter = k;
                            break;
                        }
                    }

                    if (index_of_letter == -1) {
                        cerr << "Parameter for " << prev_arg << " was given unrecognized letter" << endl;
                        return 1;
                    }

                    // check that there are no more than two copies of each letter
                    if (!ability_counts.count(cur_arg[j])) {
                        ability_counts.insert({cur_arg[j], 0});
                    }
                    ability_counts[cur_arg[j]]++;
                    if (ability_counts[cur_arg[j]] > Board::MAX_NUM_OF_EACH_ABILITY) {
                        cerr << "Parameter for " << prev_arg << " had more than two copies of an ability" << endl;
                        return 1;
                    }
                }

                if (prev_arg == "-ability1") {
                    ability1 = cur_arg;
                } else {
                    ability2 = cur_arg;
                }
            } else if (prev_arg == "-link1" || prev_arg == "-link2") {
                // validate length
                if (cur_arg.length() != Board::NUM_LINKS * 2) {
                    cerr << "Parameter for " << prev_arg << " is not length 16" << endl;
                    return 1;
                }
                
                map<string, bool> link_counts; 
                for (int j = 0; j < Board::NUM_LINKS * 2; j += 2) {
                    string link = cur_arg.substr(j, 2);
                    
                    // validate link formatting
                    if (link.length() != 2 ||
                            !(link[0] == 'd' || link[0] == 'D' || link[0] == 'v' || link[0] == 'V') ||
                            !(link[1] >= '1' && link[1] <= '4')) {
                        cerr << "Parameter for " << prev_arg << " is invalid" << endl;
                        return 1;
                    }
                    
                    // validate uniqueness of links
                    if (link_counts.count(link)) {
                        cerr << "Parameter for " << prev_arg << " has two or more copies of link " << link << endl;
                        return 1;
                    }
                    link_counts.insert({link, true});

                    // populate array
                    if (prev_arg == "-link1") {
                        link1 += link;
                    } else {
                        link2 += link;
                    }
                }
            } else {
                // this code should never run but it's here just in case
                cerr << "Unrecognized argument " << prev_arg << endl;
                return 1;
            }
            prev_arg = "";
        } else if (
            cur_arg == "-ability1" ||
            cur_arg == "-ability2" ||
            cur_arg == "-link1" ||
            cur_arg == "-link2"
        ) {
            prev_arg = cur_arg;
        } else if (cur_arg == "-graphics") {
            graphics_enabled = true;
        } else {
            cerr << "Argument " << cur_arg << " not recognized" << endl;
            return 1;
        }
    }

    if (prev_arg != "") {
        cerr << "Missing parameter for " << prev_arg << endl;
        return 1;
    }

    Board board{{link1, link2}, {ability1, ability2}};

    // populate board's observers array
    
    Terminal* terminal = new Terminal{board};
 
    board.subscribe(terminal);

    if (graphics_enabled) {
        Graphic* graphic = new Graphic{board};
        board.subscribe(graphic);    
    }
    
    // ----- INPUT READER -----
    ifstream file_stream;
    istream* current_stream = &cin;
    string in;
    while (*current_stream >> in) {
        // check win condition
        if (board.winner != -1) {
            cout << "Player " << (board.winner + 1) << " has won!" << endl;
            return 0;
        }

        // this string will store the resulting error message, if applicable
        string retval = "";
        if (in == "move") {
            char link;
            string dir;
            *current_stream >> link >> dir;

            if (dir != "up" && dir != "down" && dir != "left" && dir != "right") {
                cerr << "Invalid input for move: direction is invalid" << endl;
            } else {
                retval = board.move(link, dir);
            }
        } else if (in == "abilities") {
            vector<Ability*>& abilities = board.ph.players[board.getCurrentPlayerID()]->abilities;
            cout << "Abilities for player " << to_string(board.getCurrentPlayerID() + 1) << " (* means used):" << endl;
            for (size_t i = 0; i < abilities.size(); i++) {
                cout << to_string(i + 1) << ": " << ABILITY_NAMES.at(abilities[i]->symbol) << (abilities[i]->used ? "*" : "") << endl;
            }
        } else if (in == "board") {
            // prints board again
            board.notifyObservers();
          

        } else if (in == "ability") {
            int id;
            *current_stream >> id;

            id--;

            int req_args = board.getNumArgumentsForAbility(id);
            
            if (req_args == -1) {
                retval = "Ability's symbol not recognized (somehow)";
            } else {
                vector<char> args;
                for (int i = 0; i < req_args; i++) {
                    char c;
                    *current_stream >> c;
                    args.push_back(c);
                }
                retval = board.useAbility(id, args);
            }

        } else if (in == "board") {
            // ------------------------ TODO: call print board ------------------------

        } else if (in == "sequence") {
            string file_name;
            *current_stream >> file_name;
            file_stream.close();
            file_stream.open(file_name);
            if (!file_stream) {
                cerr << "Invalid input for sequence: could not open file" << endl;
            } else {
                current_stream = &file_stream;
            }
            
        } else if (in == "quit") {
            cout << "Quitting game..." << endl;
            return 0;
        } else {
            cout << "Invalid input detected" << endl;
        }

        if (retval != "") {
            cerr << retval << endl;
        }

        if (current_stream == &file_stream && file_stream.eof()) {
            current_stream = &cin;
        }
    }
}