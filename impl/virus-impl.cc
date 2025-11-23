
module Virus;

import Coords;

Virus::Virus(int level, Coords coords): level{level}, coords{coords}, type{"virus"} {}

Virus::Virus(int level, int r, int c): level{level}, coords{{r, c}}, type{"virus"} {}