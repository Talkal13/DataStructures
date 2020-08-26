#pragma once

template <class K=int>
struct Node{
    K key;
    Node<K> *l = nullptr;
    Node<K> *r = nullptr;
};


template <class K=int>
class BinarySearchTree {
public:
    virtual void insert(K key) = 0;
    virtual bool search(K key) = 0;
    virtual void remove(K key) = 0;
    virtual void print() = 0;
};