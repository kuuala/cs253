#ifndef SEARCH_IN_STATE_SPACE_POSITION_HPP
#define SEARCH_IN_STATE_SPACE_POSITION_HPP

class Position {
    int num;
    int step;
    Position *parent;

public:
    Position(): num(0), step(0), parent(nullptr) {}

    Position(int num, int step, Position *parent): num(num), step(step), parent(parent) {}

    ~Position() { delete parent; }

    int getNum() const { return num; }

    int getStep() const { return step; }

    Position *getPosition() const { return parent; }

    struct comparator {
        bool operator()(const Position *pos1, const Position *pos2) const {
            return pos1->getNum() < pos2->getNum();
        }
    };
};

#endif //SEARCH_IN_STATE_SPACE_POSITION_HPP
