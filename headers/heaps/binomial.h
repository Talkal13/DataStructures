#include "priorityQueue.h"


template <class T=int>
struct NodeBin {
    T key;
    unsigned degree = 0;
    NodeBin<T> *u = nullptr;
    NodeBin<T> *l = nullptr;
    NodeBin<T> *r = nullptr;
};

template <class T=int>
class Binomial : public PriorityQueue<T> {
public:
    Binomial() {}
    
    ~Binomial() {
        while(_head != nullptr) pop();
    }

    bool empty() {
        return false;
    }
    
    bool insert(T elem) {
        NodeBin<T>* node = new NodeBin<T>;
        node->key = elem;

        _head = join(node, _head);

        if (_min == nullptr) _min = node;
        else if (elem < _min->key) _min = node;
        
        return true;
    }

    T get() {
        return _min->key;
    }
    void pop() {
        NodeBin<T>* childs = deleteMin();
        _head = join(childs, _head);
        _min = setMin();
    }
    void print() {
        print(_head);
        std::cout << std::endl;
    }

private:

    NodeBin<T>* join(NodeBin<T>* t1, NodeBin<T>* t2) {

        NodeBin<T> *prev, *x, *next;
        prev = nullptr;
        x = merge(t1, t2);
        if (x == nullptr) return nullptr;
        NodeBin<T>*start = x;
        next = x->r;

        while (next != nullptr) {
            if ((x->degree != next->degree) || 
                (next->r != nullptr && next->r->degree == next->degree)) {
                prev = x;
                x = next;
            } else if (x->key <= next->key) {
                    x->r = next->r;
                    link(x, next);
            } else  {
                if (prev == nullptr) start = next;
                else prev->r = next;
                x->r = nullptr;
                link(next, x);
                x = next;
            }
            next = x->r;
        }

        return start;

    }

    NodeBin<T>* merge(NodeBin<T>* t1, NodeBin<T>* t2) {
        NodeBin<T>* head;
        if (t2 == nullptr) return t1;
        else if (t1 == nullptr) return t2;

        if (t1->degree <= t2->degree) {
            head = t1;
            head->r = merge(head->r, t2);
        }
        else {
            head = t2;
            head->r = merge(t1, head->r);
        }
        return head;
    }

    NodeBin<T>* link(NodeBin<T>* t1, NodeBin<T> *t2) {
        if (t1->l == nullptr) {
            t1->l = t2;
            t2->r = nullptr;
            t2->u = t1;
            t1->degree++;
            return t1;
            }
        NodeBin<T> *aux = t1->l;
        while (aux->r != nullptr) aux = aux->r;
        aux->r = t2;
        t2->u = aux->u;
        t2->r = nullptr;
        t1->degree++;
        return t1; 
    }

    NodeBin<T>* deleteMin() {
        if (_min == nullptr) return nullptr;
        NodeBin<T>* prev = nullptr;
        NodeBin<T>* aux = _head;
        while (aux != nullptr) {
            if (_min == aux) {
                if (prev == nullptr) _head = aux->r;
                else prev->r = aux->r;
                aux = _min->l;
                prev = aux;
                while (prev != nullptr) {
                    prev->u = nullptr;
                    prev = prev->r;
                }
                delete _min;
                _min = nullptr;
                return aux;
            }
            prev = aux;
            aux = aux->r;
        }
        return nullptr;
    }

    NodeBin<T>* setMin() {
        NodeBin<T>*aux, *amin = _head;
        aux = _head;
        while(aux != nullptr) {
            if (aux->key < amin->key) {
                amin = aux;
            }
            aux = aux->r;
        }
        return amin;
    }

    void print(NodeBin<T> *t) {
        std::cout << "(" << t->key << ", " << t->degree << ")";
        if (t == _min) std::cout << "*";
        if (t->r != nullptr) {std::cout << "->"; print(t->r);}
    }

     NodeBin<T>* _head = nullptr;
     NodeBin<T>* _min = nullptr;

};