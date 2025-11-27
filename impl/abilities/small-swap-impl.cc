module Gameplay;

import Coords;
import Link;

import <vector>;
import <string>;
import <iostream>;

using namespace std;

SmallSwap::SmallSwap(): Ability{'W'} {}

string SmallSwap::usePower(Board &b, vector<char> args, Player * p) {
    //debug
    cerr << "small swap called\n";

    if (args.size() != 2) {
        return "Invalid input for SmallSwap: invalid number of arguments";
    }

    char symbol1 = args[0];
    char symbol2 = args[1];
    Link* link1 = b.getLinkPointerFromChar(symbol1);
    Link* link2 = b.getLinkPointerFromChar(symbol2);


    if (link1 == nullptr || link2 == nullptr) {
        return "Error in SmallSwap: link not found";
    }

    swap(*link1, *link2);

    swap(link1->coords, link2->coords);

    // swap cells, except firewall
    Cell temp = b.board[link1->coords.r][link1->coords.c];
    Cell& cell1 = b.board[link1->coords.r][link1->coords.c];
    Cell& cell2 = b.board[link2->coords.r][link2->coords.c];
    cell1.player = cell2.player;
    cell1.item = cell2.item;
    cell1.level = cell2.level;
    cell1.symbol = cell2.symbol;

    cell2.player = temp.player;
    cell2.item = temp.item;
    cell2.level = temp.level;
    cell2.symbol = temp.symbol;

    

    return "";
}
