
template <class K=int>
struct Node{
    K key;
    Node<K> *l = nullptr;
    Node<K> *r = nullptr;
};


template <class K=int>
class BinaryTree {
    public:
        BinaryTree() {}

        virtual void insert(K key) = 0;
        virtual void search(K key) = 0;

    protected:
        Node<K> *_head = nullptr;
};