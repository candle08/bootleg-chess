import <iostream>;
import <vector>;
import <algorithm>;
import <string>;
import <fstream>;
import <map>;

import Ability;
import Board;
import Data;
import Virus;
import Display;
import Graphic;
import Player;

using namespace std;

int main(int argc, char* argv[]) {

    // ----- COMMAND LINE READER -----
    string prev_arg = "";

    /**
     * L: LinkBoost
     * F: Firewall
     * D: Download
     * S: Scan
     * B: DoubleDown
     * T: TwoSum
     * W: SmallSwap
     */
    const vector<char> ABILITY_LETTERS = {'L', 'F', 'D', 'S', 'P', 'B', 'T', 'W'};

    string ability1 = "LFDSP", ability2 = "LFDSP";
    string link1 = "V1V2V3V4D1D2D3D4", link2 = "V1V2V3V4D1D2D3D4";
    bool graphics_enabled = false;

    for (int i = 1; i < argc; i++) {
        string cur_arg = argv[i];
        if (prev_arg != "") {
            if (prev_arg == "-ability1" || prev_arg == "-ability2") {
                // validate length
                if (cur_arg.length() != NUM_OF_ABILITIES) {
                    cerr << "Parameter for " << prev_arg << " is not length " << NUM_OF_ABILITIES << endl;
                    return 1;
                }

                // validate that the argument only has characters valid letters, and that each letter appears no more than twice
                map<char, int> ability_counts;
                for (int j = 0; j < NUM_OF_ABILITIES; j++) {
                    // check that all letters are valid
                    int index_of_letter = -1;
                    for (int k = 0; k < ABILITY_LETTERS.size(); k++) {
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
                    if (ability_counts[cur_arg[j]] > MAX_NUM_OF_EACH_ABILITY) {
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
                if (cur_arg.length() != NUM_OF_LINKS * 2) {
                    cerr << "Parameter for " << prev_arg << " is not length 16" << endl;
                    return 1;
                }
                
                map<string, bool> link_counts; 
                for (int j = 0; j < NUM_OF_LINKS * 2; j += 2) {
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
            }/
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
            char link, dir;
            *current_stream >> link >> dir;

            if (dir != "up" && dir != "down" && dir != "left" && dir != "right") {
                cerr << "Invalid input for move: direction is invalid" << endl;
            } else {
                retval = board.move(link, dir);
            }
        } else if (in == "abilities") {
            // list out abilities
        } else if (in == "ability") {
            char id;
            *current_stream >> id;

            if (id == '1' || id == 'l' || id == 'L') {
                // link boost
                char link;
                *current_stream >> link;

                retval = board.useAbility('L', link);
            } else if (id == '2' || id == 'f' || id == 'F') {
                // firewall
                int r, c;
                *current_stream >> r >> c;

                retval = board.useAbility('F', '\0', {r, c});
            } else if (id == '3' || id == 'd' || id == 'D') {
                // download
                char link;
                *current_stream >> link;

                retval = board.useAbility('L', link);
            } else if (id == '4' || id == 'p' || id == 'P') {
                // polarize
                char link;
                *current_stream >> link;

                retval = board.useAbility('P', link);
            } else if (id == '5' || id == 's' || id == 'S') {
                // scan
                char link;
                *current_stream >> link;
                retval = board.useAbility('S', link);
            } else if (id == '6' || id == 'b' || id == 'B') {
                // doubledown
                retval = board.useAbility('B');
            } else if (id == '7' || id == 't' || id == 'T') {
                // twosum
                char link;
                *current_stream >> link;
                retval = board.useAbility('T', link);
            } else if (id == '8' || id == 'w' || id == 'W') {
                // smallswap
                char link1, link2;
                *current_stream >> link1 >> link2;
                retval = board.useAbility('W', link2, {-1, -1}, link2);
            } else {
                cerr << "Invalid input for ability" << endl;
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
                cur = &file_stream;
            }
            
        } else if (in == "quit") {
            cout << "Quitting game..." << endl;
            return 0;
        } else {
            cout << "Invalid input detected" << endl;
        }

        if (retval) {
            cerr << retval << endl;
        }

        if (current_stream == &file_stream && file_stream.eof()) {
            current_stream = &cin;
        }
    }
}