#include "headers/heaps/williams.h"
#include "headers/heaps/sesgados.h"
#include "headers/heaps/binomial.h"
#include "headers/heaps/fibonacci.h"
#include "headers/trees/AVL.h"
#include "headers/trees/RedBlack.h"
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

void console(BinarySearchTree<> *q) {
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
        case 'r':
            cin >> val;
            q->remove(val);
            q->print();
            break;
        case 's':
            cin >> val;
            cout << q->search(val) << endl;
            break;
        case 'p':
            q->print();
            break;
        }
        cin >> i;
    }
}

int main(int argc, char **argv) {
    RedBlackTree<> a = RedBlackTree<>();
    console(&a);
}