//
// Created by Tomek on 17.05.2021.
//

#include "Node.h"
#include <iostream>

Node::Node(int order, Node *root, bool leaf) {
    this->sons = new Node*[order];
    this->keys = new int[(2*order)-1];
    this->root = root;
    this->order = order;
    this->leaf = leaf;
}

void Node::healthCheck() const {
    if (this->currentKeys < (this->order-1)) {
        std::cout << "[WARNING] Node contains less than t-1 keys!\n";
    } else if (this->currentKeys > ((this->order*2)-1)) {
        std::cout << "[WARNING] Node contains more than 2t-1 keys!\n";
    }
}

bool Node::isRoot() const {
    return (this->root == nullptr);
}

Node::Node() {
    this->sons = nullptr;
    this->keys = nullptr;
    this->root = nullptr;
}

void Node::insert_nfull(int val) {
    int i = this->currentKeys - 1;
    // Normal case when
    if (this->leaf) {
        while (this->keys[i] > val && i >= 0) {
            this->keys[i + 1] = this->keys[i];
            i--;
        }
        this->keys[i + 1] = val;
        this->currentKeys++;
    }
}

void Node::split(int i, Node *node) {

}

void Node::traverse() {
    int i;
    for (i = 0; i < this->currentKeys; i++) {
        if (!this->leaf) this->sons[i]->traverse();
        std::cout << this->keys[i] << " ";
    }
    if (!this->leaf) this->sons[i]->traverse();
}

