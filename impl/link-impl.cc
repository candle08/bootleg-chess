module Link;

import Coords;
import <string>;

using namespace std;

Link::Link(int level, Coords coords, string type, char symbol): level{level}, coords{coords}, type{type}, symbol{symbol}, download_status{false}, revealed{false}, linkboost{false}, frozen_on_turn{-1} {}

void Link::move(int row, int col) {
    coords = Coords{row, col};
}

void Link::move(const Coords& new_coords) {
    coords = new_coords;
}