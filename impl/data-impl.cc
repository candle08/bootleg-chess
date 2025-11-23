module Data;

import Coords;

Data::Data(int level, Coords coords): level{level}, coords{coords}, type{"data"} {}

Data::Data(int level, int r, int c): level{level}, coords{{r, c}}, type{"data"} {}