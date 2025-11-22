export module Player;

import Virus;
import Data;
import Ability;

export class Player {
    <Virus *> all_virus;
    <Data *> all_data;
    <Ability *> abilities;

    public:
    Player(<Virus *> v, <Data *> d, <Ability *> a);
    ~Player();
};
