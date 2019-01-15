#include "Solver.hpp"

const vector<function<int(int)>> functions {
        [] (int num) { return num * 2; },
        [] (int num) { return num + 3; },
        [] (int num) { return num - 2; }
};

const vector<function<bool(int&)>> back_functions {
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

Position *task12(int start, int end) {
    clock_t s = clock();
    set<Position *, Position::comparator> positions;
    queue<Position *> q;
    auto first = new Position(start, 0, nullptr);
    positions.insert(first);
    q.push(first);
    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        if (current->getNum() == end) {
            cout << "time straight search: " << double(clock() - s) / CLOCKS_PER_SEC << endl;
            cout << "space straight search: " << positions.size() << endl;
            return current;
        }
        for (const auto& fun: functions) {
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
    clock_t s = clock();
    set<Position *, Position::comparator> positions;
    queue<Position *> q;
    auto first = new Position(end, 0, nullptr);
    positions.insert(first);
    q.push(first);
    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        if (current->getNum() == start) {
            cout << "time back search: " << double(clock() - s) / CLOCKS_PER_SEC << endl;
            cout << "space back search: " << positions.size() << endl;
            return current;
        }
        for (const auto &f: back_functions) {
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
    clock_t s = clock();
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
            for (const auto &f: functions) {
                auto next = new Position(f(current->getNum()), current->getStep() + 1, current);
                if (straight_positions.find(next) == straight_positions.end()) {
                    if (reverse_positions.find(next) != reverse_positions.end()) {
                        cout << "time bidirectional search: " << double(clock() - s) / CLOCKS_PER_SEC << endl;
                        cout << "space bidirectional search: " << reverse_positions.size() + straight_positions.size() << endl;
                        return {next, *reverse_positions.find(next)};
                    }
                    q.emplace(next, true);
                    straight_positions.insert(next);
                }
            }
        } else {
            for (const auto &f: back_functions) {
                int num = current->getNum();
                if (f(num)) {
                    auto next = new Position(num, current->getStep() + 1, current);
                    if (reverse_positions.find(next) == reverse_positions.end()) {
                        if (straight_positions.find(next) != straight_positions.end()) {
                            cout << "time back search: " << double(clock() - s) / CLOCKS_PER_SEC << endl;
                            cout << "space back search: " << reverse_positions.size() + straight_positions.size() << endl;
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