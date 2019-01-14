#ifndef FIFTEEN_POSITION_HPP
#define FIFTEEN_POSITION_HPP

#include <unordered_map>
#include <string>
#include <set>

extern std::unordered_map<char, std::pair<int, int>> base;

class Position {
    std::string field;
    int heuristic;
    int dist;
    int forecast;
    Position *parent;

    bool is_correct_line(const std::string &field) {
        if (field.length() != 16) {
            return false;
        }
        std::set<char> temp;
        for (const auto &c: field) {
            temp.insert(c);
        }
        if (temp.size() != 16) {
            return false;
        }
        for (char i = '0'; i <= '9'; ++i) {
            if (temp.find(i) == temp.end()) {
                return false;
            }
        }
        for (char i = 'A'; i <= 'F'; ++i) {
            if (temp.find(i) == temp.end()) {
                return false;
            }
        }
        return true;
    }

    int calc_heuristic() {
        return 0;
    }

public:
    Position(const std::string &field): dist(0) {
        if (!is_correct_line(field)) {
            throw -1;
        }
        this->field = field;
        heuristic = calc_heuristic();
        forecast = dist + heuristic;
        parent = nullptr;
    }

    ~Position() {
        delete parent;
    }
};


#endif //FIFTEEN_POSITION_HPP
