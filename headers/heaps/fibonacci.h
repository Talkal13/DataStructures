#include "priorityQueue.h"
#include <cmath>

template <class T=int>
struct NodeFib {
    T key;
    unsigned deg = 0;
    bool mark = false;
    NodeFib<T> *u = nullptr;
    NodeFib<T> *l = nullptr;
    NodeFib<T> *r = nullptr;
    NodeFib<T> *d = nullptr;
};

template <class T=int>
class FibonacciH : public PriorityQueue<T> {

public:
    virtual bool empty() {return _n == 0;}
    virtual bool insert(T elem) {
        NodeFib<T> *e = new NodeFib<T>;
        e->key = elem;

        if (_min == nullptr) {_min = e; _n++; return true;}

        _min = insert(_min, e);

        _n++;

        if (_min->key > e->key) _min = e;

        return true;
    }

    virtual T get() {return _min->key;}

    virtual void pop() {
        NodeFib<T> *next, *prev;
        if (_min == nullptr) return;

        _min = concatenate(_min, _min->d, true);

        next = _min->r;
        prev = _min->l;

        if (next == nullptr) {delete _min; _min = nullptr; _n--; return;}
        
        if (next == prev) {next->r = nullptr; next->l = nullptr;}
        else {
            prev->r = next;
            next->l = prev;
        }

        delete _min;
        _min = next;
        _n--;
        _min = consolidate(_min);
        return;
    }
    virtual void print() {
        print(_min);
        std::cout << std::endl;
    }

private:

    NodeFib<T>* join(NodeFib<T>* h1, NodeFib<T>* h2) {
        NodeFib<T>* h;
        if (h1->key < h2->key) {
            h = concatenate(h1, h2);
        } else {
            h = concatenate(h2, h1);
        }
        return h;
    }

    NodeFib<T>* concatenate(NodeFib<T>* h1, NodeFib<T>* h2, bool del = false) {
        NodeFib<T> *it, *aux = h2;
        if (aux == nullptr) return h1;
        do {
            if (del) aux->u = nullptr;
            it = aux->r;
            insert(h1, aux);
            aux = it;
        } while(it != nullptr && it != h2);
        return h1;
    }

    NodeFib<T>* consolidate(NodeFib<T>*h) {
        unsigned D = ceil(log2(_n)) + 1;
        NodeFib<T>* A[D];
        for (int i = 0; i < D; i++) {A[i] = nullptr;}
        NodeFib<T>*y, *x = h;
        unsigned d;
        do {
            d = x->deg;
            while (A[d] != nullptr) { //Exists other tree with the same degree
                y = A[d];
                if (x->key < y->key) {
                    if (h == y) h = x;
                    x = link(x, y);
                } else {
                    if (h == x) h = y;
                    x = link(y, x); 
                }
                A[d] = nullptr;
                d = x->deg;
            }
            A[d] = x;
            x = x->r;
        } while(x != nullptr && x != h);
        y = nullptr;
        for (int i= 0; i < D; i++) {
            if (A[i] != nullptr) {
                if (y == nullptr || y->key > A[i]->key) {
                    y = A[i];
                }
            }
        }
        return y;
    }

    NodeFib<T>* insert(NodeFib<T>*h, NodeFib<T> *u) {
        if (h == nullptr) {reset(u); return u;}
        u->r = h;
        if (h->r == nullptr) h->r = u;
        if (h->l == nullptr) u->l = h;
        else {
            u->l = h->l;
            h->l->r = u;
        }
        h->l = u;
        return h;
    }

    void print(NodeFib<T> *t) {
        if (t == nullptr) return;
        NodeFib<T> *aux = t;
        do {
            std::cout << "(" << aux->key << ", " << aux->deg << ")";
            if (aux == _min) std::cout << "*";
            if (aux->r != t || aux->r != nullptr) std::cout << "->";
            aux = aux->r;
        } while(aux != nullptr && aux != _min);
    }

    NodeFib<T>* link(NodeFib<T> *x, NodeFib<T> *y) {
        remove(y);
        insert(x->d, y);
        x->d = y;
        y->u = x;
        x->deg++;
        return x;
    }

    void remove(NodeFib<T> *h) {
        NodeFib<T> *next, *prev;
        next = h->r;
        prev = h->l;

        if (next == nullptr) {return;}
        
        if (next == prev) {next->r = nullptr; next->l = nullptr;}
        else {
            prev->r = next;
            next->l = prev;
        }
    }

    void reset(NodeFib<T> *u) {
        u->r = nullptr;
        u->l = nullptr;
        u->d = nullptr;
        u->u = nullptr;
        u->mark = false;
    }

    NodeFib<T> *_min = nullptr;
    unsigned _n = 0;
};