#include <iostream>
#include <queue>
#include <functional>
#include <vector>
#include <set>

using namespace std;

const vector<function<int(int)>> g_funs {
    [] (int num) { return num * 2; },
    [] (int num) { return num + 3; },
    [] (int num) { return num - 2; }
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
};

struct comparator {
    bool operator()(const Position *pos1, const Position *pos2) const {
        return pos1->getNum() < pos2->getNum();
    }
};

Position* task1(int start, int end) {
    set<Position *, comparator> positions;
    queue<Position *> q;
    auto first = new Position(start, 0, nullptr);
    positions.insert(first);
    q.push(first);
    while(!q.empty()) {
        auto current = q.front();
        q.pop();
        if (current->getNum() == end) {
            return current;
        }
        for (const auto& fun: g_funs) {
            auto to = new Position(fun(current->getNum()), current->getStep() + 1, current);
            if (positions.find(to) == positions.end()) {
                q.push(to);
                positions.insert(to);
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
    Position* answer = task1(a, b);
    cout << answer->getStep();
    return 0;
}