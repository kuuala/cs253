#ifndef FIFTEEN_GAME_HPP
#define FIFTEEN_GAME_HPP

#include "Position.hpp"

class Game {
    Position *start;

    bool is_solvable() const {
        std::string line = start->get_field();
        int sum = (int)line.find('0') / 4 + 1;
        for (int i = 0; i < 16; ++i) {
            for (int j = i + 1; j < 16; ++j) {
                if (line[j] < line[i] && line[j] != '0') {
                    ++sum;
                }
            }
        }
        return sum % 2 == 0;
    }

public:
    explicit Game(Position *start): start(start) {}

     void a_star() {
        if (!is_solvable()) {
            throw 2;
        }
    }
};


#endif //FIFTEEN_GAME_HPP
