#pragma once

template <class T=int>
class PriorityQueue {
    public:
    virtual bool empty() = 0;
    virtual bool insert(T elem) = 0;
    virtual T get() = 0;
    virtual void pop() = 0;
    virtual void print() = 0;

};