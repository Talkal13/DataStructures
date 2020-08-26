#pragma once

#include "BST.h"

#define RED true
#define BLACK false

template <class T=int>
struct NodeRB {
    T key;
    bool color = RED;
    NodeRB<T> *l = nullptr;
    NodeRB<T> *r = nullptr;
};

template <class T=int>
class RedBlackTree : public BinarySearchTree<T> {
public:
    void insert(T key) {
        _root = insert(_root, key);
        _root->color = BLACK;
    }

    bool search(T key) {
        return (search(_root, key) != nullptr) ? true : false;
    }
    void remove(T key) {
        _root = remove(_root, key);
        _root->color = BLACK;
    }

    void print() {
        print(_root);
        std::cout << std::endl;
    }

private:

    NodeRB<T>* insert(NodeRB<T> *x, T key) {
        if (x == nullptr) {
            NodeRB<T> *e = new NodeRB<T>;
            e->key = key;
            return e; // New node: RED flag at the end
        }

        // Way down
        if (isRed(x->l) && isRed(x->r)) // both red 
            x = colorFlip(x);

        // Insert
        if (key < x->key) x->l = insert(x->l, key);
        else if (key > x->key) x->r = insert(x->r, key);

        // Way up
        if (isRed(x->r)) 
            x = rotateLeft(x);
        if (isRed(x->l) && isRed(x->l->l))
            x = rotateRight(x);

        return x;
    }

    NodeRB<T>* deleteMax(NodeRB<T> *x, T key) {
        if (isRed(x->l))
            x = rotateRight(x);
        if (x->r == nullptr) return nullptr;
        if (isNotRed(x->r) && isNotRed(x->r->r))
            x = moveRedRigth(x);
        
        x->r = deleteMax(x->r);

        return fixUp(x);
    }

    NodeRB<T>* moveRedRight(NodeRB<T> *x) {
        colorFlip(x);
        if (x->l != nullptr && isRead(x->l->l)) {
            x = rotateRight(x);
            colorFlip(x);
        }
        return x;
    }

    NodeRB<T>* rotateLeft(NodeRB<T> *x) {
        NodeRB<T> *y = x->r;
        if (y == nullptr) return x;
        x->r = y->l;
        y->l = x;
        y->color = x->color;
        x->color = RED;
        return y;
    }

    NodeRB<T>* rotateRight(NodeRB<T>*x) {
        NodeRB<T> *y = x->l;
        if (y == nullptr) return x;
        x->l = y->r;
        y->r = x;
        y->color = x->color;
        x->color = RED;
        return y;
    }

    NodeRB<T>* colorFlip(NodeRB<T>* x) {
        if (x->l == nullptr || x->r == nullptr) return x;
        x->color = !x->color;
        x->l->color = !x->l->color;
        x->r->color = !x->r->color;
        return x;
    }

    NodeRB<T>* fixUp(NodeRB<T> *x) {
        if (x == nullptr) return x;
        if (isRed(x->r))
            x = rotateLeft(x);
        if (isRed(x->l) && isRed(x->l->l))
            x = rotateRight(x);
        if (isRed(x->l) && isRed(x->r)) {
            x = colorFlip(x);
        }
        return x;
    }

    bool isRed(NodeRB<T> *x) {
        return x != nullptr && x->color;
    }

    bool isNotRed(NodeRB<T> *x) {
        return x != nullptr && !x->color;
    }

    NodeRB<T>* search(NodeRB<T> *a, T key) {
        if (a == nullptr || key == a->key) return a;
        if (key < a->key) return search(a->l, key);
        else return search(a->r, key);
    }

    void print(NodeRB<T> *x) {
        if (x == nullptr) {std::cout << "_ "; return;}
        std::cout << x->key;
        (x->color) ? std::cout << "* " : std::cout << " ";
        print(x->l);
        print(x->r);
    }

    NodeRB<T> *_root;
}; 