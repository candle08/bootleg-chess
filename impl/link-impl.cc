module Link;

import Coords;

Link::Link(int level, Coords c, string type): level{level}, coords{coords}, type{type} {}

void Link::move(int row, int col) {
    coords = Coords{row, col};
}

void Link::move(const Coords& new_coords) {
    coords = new_coords;
}