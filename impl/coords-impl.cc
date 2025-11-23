module Coords
bool Coords::operator==(const Coords other) {
    return (other.r == r && other.c == c);
}