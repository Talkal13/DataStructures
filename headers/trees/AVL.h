#include "BST.h"

#include <cmath>
#include <utility>

template <class T = int>
struct NodeAVL {
    T key;
    unsigned h = 0;
    NodeAVL<T> *l = nullptr;
    NodeAVL<T> *r = nullptr;
};

template <class T = int>
class AVL : public BinarySearchTree<T> {
public:

    void insert(T key) { 
        _root = insert(_root, key);
    }

    bool search(T key) {
        return (search(_root, key) != nullptr) ? true : false;
    }
    void remove(T key) {
        _root = remove(_root, key);
    }

    void print() {
        print(_root);
        std::cout << std::endl;
    }
private:

    NodeAVL<T>* insert(NodeAVL<T> *a, T key) {
        if (a == nullptr) {
            NodeAVL<T>* u = new NodeAVL<T>;
            u->key = key;
            u->h = 1;
            a = u;
        } else if (key < a->key) {
            a->l = insert(a->l, key);
            return balance(a);
        }
        else if (key > a->key) {
            a->r = insert(a->r, key);
            return balance(a);
        }
        
        return a;
    }

    NodeAVL<T>* remove(NodeAVL<T> *a, T key) {
        if (a == nullptr) return a;
        else if (key < a->key) {
            a->l = remove(a->l, key);
            return balance(a);
        } else if (key == a->key) {
            NodeAVL<T> *l, *r;
            r = a->r; l = a->l;
            if (r == nullptr) {
                delete a;
                return l;
            } else {
                NodeAVL<T> *minr;
                std::pair<NodeAVL<T>*, NodeAVL<T>*> pair = switchMin(r);
                minr = pair.first;
                minr->l = l;
                minr->r = pair.second;
                return balance(minr);
            }
        } else {
            a->r = remove(a->r, key);
            return balance(a);
        }
    }

    NodeAVL<T>* search(NodeAVL<T> *a, T key) {
        if (a == nullptr || key == a->key) return a;
        if (key < a->key) return search(a->l, key);
        else return search(a->r, key);
    }

    std::pair<NodeAVL<T>*, NodeAVL<T>*> switchMin(NodeAVL<T> *x) {
        NodeAVL<T> *l = x->l, *r = x->r;
        if (l == nullptr) {
            x->r = nullptr;
            return std::make_pair(x, r);
        }
        else {
            std::pair<NodeAVL<T>*, NodeAVL<T>*> t = switchMin(x->l);
            if (l == t.first) x->l = t.second;
            return std::make_pair(t.first, balance(x));
        }
    }

    NodeAVL<T>* balance(NodeAVL<T> *x) {
        unsigned hl, hr;
        if (x->l == nullptr) hl = 0; else hl = x->l->h;
        if (x->r == nullptr) hr = 0; else hr = x->r->h;
        if (abs(hl - hr) <= 1) {
            x->h = 1 + std::max(hl, hr);
            return x;
        } else if (hl == hr + 2) {
            return unbalLeft(x);
        } else {
            return unbalRight(x);
        }
    }

    NodeAVL<T>* unbalRight(NodeAVL<T> *x) {
        NodeAVL<T> *r = x->r;
        unsigned hrl, hrr;
        if (r->l == nullptr) hrl = 0; else hrl = r->l->h;
        if (r->r == nullptr) hrr = 0; else hrr = r->r->h;
        if (hrr >= hrl) return RR(x);
        else return RL(x);
    }

    NodeAVL<T>* RR(NodeAVL<T> *x) {
        NodeAVL<T>* r = x->r;
        x->r = r->l;
        r->l = x;
        return r;
    }

    NodeAVL<T>* RL(NodeAVL<T> *x) {
        NodeAVL<T> *y = x->r;
        NodeAVL<T> *z = y->l;
        y->l = z->r;
        x->r = z->l;
        z->r = y;
        z->l = x;
        return z;
    }

    NodeAVL<T>* unbalLeft(NodeAVL<T> *x) {
        NodeAVL<T> *l = x->l;
        unsigned hll, hlr;
        if (l->l == nullptr) hll = 0; else hll = l->l->h;
        if (l->r == nullptr) hlr = 0; else hlr = l->r->h;
        if (hll >= hlr) return LL(x);
        else return LR(x);
    }

    NodeAVL<T>* LL(NodeAVL<T> *x) {
        NodeAVL<T> *l = x->l;
        x->l = l->r;
        l->r = x;
        return l;
    }

    NodeAVL<T>* LR(NodeAVL<T> *x) {
        NodeAVL<T> *y = x->l;
        NodeAVL<T> *z = y->r;
        y->r = z->l;
        x->l = z->r;
        z->l = y;
        z->r = x;
        return z;

    }

    void print(NodeAVL<T> *x) {
        if (x == nullptr) {std::cout << "_ "; return;}
        std::cout << x->key << " ";
        print(x->l);
        print(x->r);
    }

    NodeAVL<T> *_root = nullptr;
};

