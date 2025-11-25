module Link;

import Coords;

Link::Link(int level, Coords coords, string type, char symbol): level{level}, coords{coords}, type{type}, symbol{symbol}, download_status{false}, revealed{false} {}

void Link::move(int row, int col) {
    coords = Coords{row, col};
}

void Link::move(const Coords& new_coords) {
    coords = new_coords;
}