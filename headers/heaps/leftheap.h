#pragma once

#include "priorityQueue.h"
#include "../trees/bt.h"
#include <cmath>

template <class T=int>
class LeftHeap : public PriorityQueue<T> {
public:
    bool empty() = 0;
    bool insert(T elem) = 0;
    T get() = 0;
    void pop() = 0;
    void print() = 0;

private:

    Node<T> *join(Node<T> *t1, Node<T> *t2) {
        if (empty(t1)) return t2;
        if (empty(t2)) return t1;
        Node<T> *nl;
        if (t1->key < t2->key) {
            t1->r = join(t1->r, t2);
            nl = t1;
        }
        else {
            t2->r = join(t1, t2->r);
            nl = t2;
        }

        if (minH(nl->l) < minH(nl->r)) {
            Node<T> *aux = nl->l;
            nl-l = nl->r;
            nl->r = aux;
        }

    }

    bool empty(Node<T> *t) {
        return t == nullptr;
    }

    unsigned minH(Node<T> *t) {
        if (empty(t)) return 0;
        else return 1 + std::min(minH(t->l), minH(t->r));
    }

    Node<T> _head;
};