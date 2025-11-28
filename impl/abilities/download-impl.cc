module Gameplay;

import Coords;
import Link;

import <iostream>;
import <vector>;
import <string>;

using namespace std;

Download::Download(): Ability{'D'} {}

string Download::usePower(Board &b, vector<char> args, Player * p) {
    // debug
    if (Board::DEBUG) cerr << "download called\n";
    if (args.size() != 1) {
        return "Invalid input for Download: invalid number of args";
    }

    Link* link_ptr = b.getLinkPointerFromChar(args[0]);
    if (link_ptr == nullptr) {
        return "Invalid input for Download: invalid link symbol";
    }

    if (link_ptr->download_status) {
        return "Error in DOwnload: link already downloaded";
    }

    p->download(link_ptr, b);
    return "";
}
