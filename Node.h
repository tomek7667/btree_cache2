//
// Created by Tomek on 17.05.2021.
//

#ifndef BTREE_CACHE_NODE_H
#define BTREE_CACHE_NODE_H


class Node {
public:
    bool leaf = false;
    Node * root;
    Node ** sons;
    int * keys;
    int currentKeys = 0, order;
    Node(int order, Node* root, bool leaf);
    Node();
    void healthCheck() const;
    bool isRoot() const;
    void insert_nfull(int val);
    void split(int i, Node *node);
    void traverse();
};


#endif //BTREE_CACHE_NODE_H
