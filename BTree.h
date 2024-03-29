//
// Created by Tomek on 17.05.2021.
//

#ifndef BTREE_CACHE_BTREE_H
#define BTREE_CACHE_BTREE_H
#include "Node.h"

class BTree {
public:
    Node *root;
    int order;
    BTree(int order);
    BTree();
    void traverse() const;
    void insert(int val);
    void remove(int val);
    bool search(int val);
};


#endif //BTREE_CACHE_BTREE_H
