#include "Solver.hpp"

int main() {
    int a, b;
    cout << "Enter start value: ";
    cin >> a;
    cout << "Enter finish value: ";
    cin >> b;
    cout << "=======================" << endl;
    auto straight_answer = task12(a, b);
    cout << straight_answer->getStep() << endl;
    cout << "=======================" << endl;
    auto back_answer = task3(a, b);
    cout << back_answer->getStep() << endl;
    cout << "=======================" << endl;
    auto bidirectional_answer = task4(a, b);
    cout << bidirectional_answer.first->getStep() << " + " << bidirectional_answer.second->getStep() << endl;
    cout << "=======================" << endl;
    return 0;
}
