#pragma once

#include "./priorityQueue.h"
#include <iostream>

template <class T=int>
class Williams: public PriorityQueue<T> {
public:

    Williams(unsigned n) {
        _n = n;
        _vector = new T[n];
    }

    ~Williams() {
        delete[] _vector;
    }

    bool empty() {
        return _k == 0;
    }

    bool full() {
        return _k == _n;
    }

    bool insert(T elem) { //TODO: Float
        if (full()) return false;
        _vector[_k++] = elem;
        qfloat(_k-1);
        return true;
    }

    T get() {
        return _vector[0];
    }

    void pop() {
        _vector[0] = _vector[--_k];
        qsink(0);
    }

    void print(){
        for (unsigned i = 0; i < _k; i++) {
            std::cout << _vector[i] << " ";
        }
        std::cout << std::endl;
    }

private:

    void qfloat(unsigned k) {
        while (k > 0 && _vector[k / 2] > _vector[k]) {
            qswitch(k/2, k);
            k = k/2;
        }
    }

    void qswitch(unsigned a, unsigned b) {
        T c = _vector[a];
        _vector[a] = _vector[b];
        _vector[b] = c;
    }

    void qsink(unsigned k) {
        unsigned m, c = k;
        bool exl = _k > 2*c + 1;
        bool exr = _k > 2*c + 2;
        while (exl || exr) {
            if (exr) {
                (_vector[2*c + 1] < _vector[2*c+2]) ? m = 2*c + 1 : m = 2*c + 2;
            }
            else 
                m = 2*c + 1;

            if (_vector[c] > _vector[m])
                qswitch(c, m);
            else break;
            c = m;
            exl = _k > 2*c + 1;
            exr = _k > 2*c + 2;
        }
    }

    T *_vector;
    unsigned _n;
    unsigned _k = 0;

};