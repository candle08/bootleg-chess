import <iostream>;
import <vector>;
import <algorithm>;
import <string>;
import <fstream>;

import Ability;
import Board;
import Data;
import Virus;
import Display;
import Graphic;
import Player;

using namespace std;

/**
 * Validate whether or not a string represents a valid link
 * @param link The string to check
 */
bool isValidLink(string link) {
    return link.length() == 2 &&
        (link[0] == 'd' || link[0] == 'D' || link[0] == 'v' || link[0] == 'V') &&
        (link[1] >= '1' && link[1] <= '4');
}

/**
 * Validate whether or not coords are within bounds
 * @param r The row to check
 * @param c The col to check
 */
bool isValidCoords(int r, int c) {
    return r <= 7 && r >= 0 && c <= 7 && c >= 0;
}

int main(int argc, char* argv[]) {
    // ----- CONSTANTS -----
    const int NUM_OF_ABILITIES = 5;
    const int MAX_NUM_OF_EACH_ABILITY = 2;
    const int NUM_OF_LINKS = 8;

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
    const vector<string> DEFAULT_LINK_ORDERING = {"V1", "V2", "V3", "V4", "D1", "D2", "D3", "D4"};

    string ability1 = "LFDSP", ability2 = "LFDSP";
    vector<string> link1, link2;
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
                vector<int> ability_counts(ABILITY_LETTERS.size());
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
                    ability_counts[index_of_letter]++;
                    if (ability_counts[index_of_letter] > MAX_NUM_OF_EACH_ABILITY) {
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
                
                vector<bool> link_counts(NUM_OF_LINKS); // ordering will be relative to DEFAULT_LINK_ORDER
                for (int j = 0; j < NUM_OF_LINKS * 2; j += 2) {
                    string link = cur_arg.substr(j, 2);
                    
                    // validate link formatting
                    if (!isValidLink(link)) {
                        cerr << "Parameter for " << prev_arg << " has an invalid character" << endl;
                        return 1;
                    }

                    // validate uniqueness of links
                    for (int k = 0; k < NUM_OF_LINKS; k++) {
                        if (link == DEFAULT_LINK_ORDERING[k]) {
                            if (link_counts[k]) {
                                cerr << "Parameter for " << prev_arg << " has two or more copies of link " << link << endl;
                                return 1;
                            }
                            link_counts[k] = true;
                        }
                    }

                    // populate array
                    if (prev_arg == "-link1") {
                        link1.push_back(link);
                    } else {
                        link2.push_back(link);
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

    if (link1.size() == 0) link1 = DEFAULT_LINK_ORDERING;
    if (link2.size() == 0) link2 = DEFAULT_LINK_ORDERING;

    // Board board{};

    // ----- INPUT READER -----
    ifstream file_stream;
    istream* current_stream = &cin;
    string in;
    while (*current_stream >> in) {
        if (in == "move") {
            string link, dir;
            *current_stream >> link >> dir;

            if (!isValidLink(link)) {
                cerr << "Invalid input for move: invalid link" << endl;
                continue;
            }

            if (dir != "up" && dir != "down" && dir != "left" && dir != "right") {
                cerr << "Invalid input for move: direction is invalid" << endl;
                continue;
            }

            int strength = link[1] - '0';

            // ------------------------ TODO: call move link ------------------------

        } else if (in == "abilities") {
            // list out abilities
        } else if (in == "ability") {
            char id;
            *current_stream >> id;
            if (id > ABILITY_LETTERS.size() || id < 1) {
                cerr << "Invalid input for ability: ID not found" << endl;
                continue;
            }

            if (id == '1' || id == 'l' || id == 'L') {
                // link boost
                string link;
                *current_stream >> link;

                if (!isValidLink(link)) {
                    cerr << "Invalid input for ability - link boost: invalid link" << endl;
                    continue;
                }

                // ------------------------ TODO: call link boost ------------------------
                
            } else if (id == '2' || id == 'f' || id == 'F') {
                // firewall
                int r, c;
                *current_stream >> r >> c;
                if (!isValidCoords(r, c)) {
                    cerr << "Invalid input for ability - firewall: invalid coordinates" << endl;
                    continue;
                }
                // ------------------------ TODO: call firewall ------------------------
            } else if (id == '3' || id == 'd' || id == 'D') {
                // download
                int r, c;
                *current_stream >> r >> c;

                if (!isValidCoords(r, c)) {
                    cerr << "Invalid input for ability - download: invalid coordinates" << endl;
                    continue;
                }

                // ------------------------ TODO: call download ------------------------

            } else if (id == '4' || id == 'p' || id == 'P') {
                // polarize
                int r, c;
                *current_stream >> r >> c;
                if (!isValidCoords(r, c)) {
                    cerr << "Invalid input for ability - polarize: invalid coordinates" << endl;
                    continue;
                }

                // ------------------------ TODO: call polarize ------------------------

            } else if (id == '5' || id == 's' || id == 'S') {
                // scan
                int r, c;
                *current_stream >> r >> c;
                if (!isValidCoords(r, c)) {
                    cerr << "Invalid input for ability - scan: invalid coordinates" << endl;
                    continue;
                }

                // ------------------------ TODO: call scan ------------------------
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
                continue;
            }
            cur = &file_stream;
            continue;
        } else if (in == "quit") {
            cout << "Quitting game..." << endl;
            return 0;
        } else {
            cout << "Invalid input detected" << endl;
            continue;
        }

        // increment board's turn counter

        if (current_stream == &file_stream && file_stream.eof()) {
            current_stream = &cin;
        }
    }
}