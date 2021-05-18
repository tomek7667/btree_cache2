//
// Created by Tomek on 17.05.2021.
//

#ifndef BTREE_CACHE_NODE_H
#define BTREE_CACHE_NODE_H


class Node {
public:
    bool leaf = false;
    Node ** sons;
    int * keys;
    int currentKeys = 0, order;
    Node(int order, bool leaf);
    Node();
    void healthCheck() const;
    void insert_nfull(int val);
    void split(int i, Node *node);
    void traverse() const;
    int maximum_items() const;
    int minimum_items() const;
    bool search(int val);
    // remove functions
    int get_key(int val) const;
    void remove(int val);
    void remove_leaf(int index);
    void remove_nonleaf(int index);
    void merge(int index);
    int getPredecessor(int index) const;
    int getSuccessor(int index);
    void fill(int index);
    void borrow_prev(int index);

    void borrow_next(int index);
};


#endif //BTREE_CACHE_NODE_H
