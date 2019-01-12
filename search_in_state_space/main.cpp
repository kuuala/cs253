#include <iostream>
#include <queue>
#include <functional>
#include <vector>
#include <set>

using namespace std;

const vector<function<int(int)>> funs {
        [] (int num) { return num * 2; },
        [] (int num) { return num + 3; },
        [] (int num) { return num - 2; }
};
const vector<function<bool(int&)>> refuns {
        [] (int &num) {
            if (num % 2)
                return false;
            num /= 2;
            return true;
        },
        [] (int &num) {
            num -= 3;
            return true;
        },
        [] (int &num) {
            num += 2;
            return true;
        }
};

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


Position *task12(int start, int end) {
    set<Position *, Position::comparator> positions;
    queue<Position *> q;
    auto first = new Position(start, 0, nullptr);
    positions.insert(first);
    q.push(first);
    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        if (current->getNum() == end) {
            return current;
        }
        for (const auto& fun: funs) {
            auto next = new Position(fun(current->getNum()), current->getStep() + 1, current);
            if (positions.find(next) == positions.end()) {
                q.push(next);
                positions.insert(next);
            }
        }
    }
    return nullptr;
}

Position *task3(int start, int end) {
    set<Position *, Position::comparator> positions;
    queue<Position *> q;
    auto first = new Position(end, 0, nullptr);
    positions.insert(first);
    q.push(first);
    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        if (current->getNum() == start) {
            return current;
        }
        for (const auto &f: refuns) {
            int num = current->getNum();
            if (f(num)) {
                auto next = new Position(num, current->getStep() + 1, current);
                if (positions.find(next) == positions.end()) {
                    q.push(next);
                    positions.insert(next);
                }
            }
        }
    }
    return nullptr;
}

pair<Position*, Position*> task4(int start, int end) {
    set<Position *, Position::comparator> straight_positions;
    set<Position *, Position::comparator> reverse_positions;
    queue<pair<Position *, bool>> q;
    auto head = new Position(start, 0, nullptr);
    straight_positions.insert(head);
    q.emplace(head, true);
    auto tail = new Position(end, 0, nullptr);
    straight_positions.insert(tail);
    q.emplace(tail, false);
    while (!q.empty()) {
        bool is_straight = q.front().second;
        auto current = q.front().first;
        q.pop();
        if (is_straight) {
            for (const auto &f: funs) {
                auto next = new Position(f(current->getNum()), current->getStep() + 1, current);
                if (straight_positions.find(next) == straight_positions.end()) {
                    if (reverse_positions.find(next) != reverse_positions.end()) {
                        return {next, *reverse_positions.find(next)};
                    }
                    q.emplace(next, true);
                    straight_positions.insert(next);
                }
            }
        } else {
            for (const auto &f: refuns) {
                int num = current->getNum();
                if (f(num)) {
                    auto next = new Position(num, current->getStep() + 1, current);
                    if (reverse_positions.find(next) == reverse_positions.end()) {
                        if (straight_positions.find(next) != straight_positions.end()) {
                            return {*straight_positions.find(next), next};
                        }
                        q.emplace(next, false);
                        reverse_positions.insert(next);
                    }
                }
            }
        }
    }
    return {nullptr, nullptr};
}

int main() {
    int a, b;
    cout << "Enter start value: ";
    cin >> a;
    cout << "Enter finish value: ";
    cin >> b;
    auto answer = task4(a, b);
    cout << answer.first->getStep() + answer.second->getStep();
    return 0;
}