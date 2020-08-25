#include "headers/heaps/williams.h"
#include "headers/heaps/sesgados.h"
#include "headers/heaps/binomial.h"
#include "headers/heaps/fibonacci.h"
#include <iostream>

using namespace std;


void console(PriorityQueue<> *q) {
    char i;
    int val;
    cin >> i;
    while (i != 'e') {
        switch (i) {
        case 'i':
            cin >> val;
            q->insert(val);
            q->print();
            break;
        case 'd':
            q->pop();
            q->print();
            break;
        case 'g':
            cout << q->get() << endl;
            break;
        case 'p':
            q->print();
            break;
        default:
            return;
        }
        cin >> i;
    }
}

int main(int argc, char **argv) {
    Binomial<> b = Binomial<>();
    Williams<> s = Williams<>(20);
    FibonacciH<> f = FibonacciH<>();
    console(&f);
}