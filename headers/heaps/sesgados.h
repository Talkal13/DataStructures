#pragma once

#include "priorityQueue.h"
#include "../trees/bt.h"

template <class T=int>
class SkewHeap : public PriorityQueue<T> {
    public:

        SkewHeap() {}

        bool empty() {
            return empty(_head);
        }
        
        bool insert(T elem) {
            Node<T> *t = new Node<T>;
            t->key = elem;
            _head = join(t, _head);
            return true;
        }

        T get() {
            return _head->key;
        }

        void pop() {
            Node<T> *k = join(_head->l, _head->r);
            delete _head;
            _head = k;
        }

        void print() {
            print(_head);
            std::cout << std::endl;
        }
        
    private:

        Node<T>* join(Node<T> *t1, Node<T> *t2) {
            Node<T> *nt = new Node<T>;
            if (empty(t2)) return t1;
            if (t1->key < t2->key) {
                nt->key = t1->key;
                nt->r = t1->l;
                nt->l = join(t2, t1->r);
                delete t1; 
            } else {
                nt->key = t2->key;
                nt->r = t2->l;
                nt->l = join(t1, t2->r);
                delete t2;
            }
            return nt;
        }

        void print(Node<T> *t) {
            if (empty(t)) return;
            std::cout << t->key << " ";
            print(t->l);
            print(t->r);
        }

        bool empty(Node<T> *k) {
            return (k == nullptr);
        }

        Node<T> *_head = nullptr;

};