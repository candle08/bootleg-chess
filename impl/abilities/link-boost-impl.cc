module LinkBoost;

string LinkBoost::usePower(Board &b, Coords &c, Link* link1, Link* link2, Player * p) override {
    if (link1->linkboost) {
        return "already linkboosted pick another link";
    } else {
        link1->linkboost = true;
    }
    return "";
}
