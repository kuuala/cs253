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


Position* task12(int start, int end) {
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

Position* task3(int start, int end) {
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

int main() {
    int a, b;
    cout << "Enter start value: ";
    cin >> a;
    cout << "Enter finish value: ";
    cin >> b;
    Position* answer = task3(a, b);
    cout << answer->getStep();
    return 0;
}