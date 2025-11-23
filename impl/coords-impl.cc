module Coords
bool Coords::operator==(const Coords other) {
    return (other.x == this->x && other.y == this->y);
}