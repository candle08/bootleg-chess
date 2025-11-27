module Link;

import Coords;
import <string>;

using namespace std;

Link::Link(int level, Coords coords, char type, char symbol): level{level}, coords{coords}, type{type}, download_status{false}, symbol{symbol}, revealed{false}, linkboost{0}, frozen_on_turn{-1} {}

void Link::move(const Coords& new_coords) {
    coords = new_coords;
}
