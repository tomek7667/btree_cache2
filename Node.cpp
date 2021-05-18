//
// Created by Tomek on 17.05.2021.
//

#include "Node.h"
#include <iostream>

Node::Node(int order, bool leaf) {
    this->sons = new Node*[order];
    this->keys = new int[(2*order)-1];
    this->order = order;
    this->leaf = leaf;
}

void Node::healthCheck() const {
    if (this->currentKeys < this->minimum_items()) {
        std::cout << "\nN Keys: " << this->currentKeys;
        std::cout << "\n[WARNING] Node contains less than t-1 keys!\n";
    } else if (this->currentKeys > this->maximum_items()) {
        std::cout << "\nN Keys: " << this->currentKeys;
        std::cout << "\n[WARNING] Node contains more than 2t-1 keys!\n";
    }
}

Node::Node() {
    this->sons = nullptr;
    this->keys = nullptr;
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
        //std::cout << "halo\n";
    } else { // when the node is not a leaf
        while (this->keys[i] > val && i >= 0) i--;
        if (this->sons[i + 1]->currentKeys == this->maximum_items()) {
            this->split(i + 1, this->sons[i + 1]); // if is maximum then split
            if (this->keys[i + 1] < val) i++;
        }
        this->sons[i + 1]->insert_nfull(val); // insert to the child node
    }
}

void Node::split(int i, Node *node) {
    // allocating memory for a new node
    Node *new_node = new Node(node->order, node->leaf);
    // minimal number of keys in the first node
    new_node->currentKeys = minimum_items();
    // transfer the keys
    for (int k = 0; k < this->order - 1; k++) {
        new_node->keys[k] = node->keys[k + this->order];
    }
    if (!node->leaf)
        for (int k = 0; k < this->order; k++)
            new_node->sons[k] = node->sons[k + this->order];
    node->currentKeys = this->minimum_items();
    for (int k = this->currentKeys; k >= i + 1; k--)
        this->sons[k + 1] = this->sons[k];
    // setting the new splitted node as a son of the current node
    this->sons[i + 1] = new_node;
    for (int k = minimum_items(); k >= i; k--)
        this->keys[k + 1] = this->keys[k];
    this->keys[i] = node->keys[minimum_items()];
    this->currentKeys++;
}

void Node::traverse() const {
    int i;
    for (i = 0; i < this->currentKeys; i++) {
        if (!this->leaf) this->sons[i]->traverse();
        if (this->leaf) this->healthCheck();
        std::cout << this->keys[i] << " ";
    }
    if (!this->leaf) this->sons[i]->traverse();
}

int Node::maximum_items() const {
    return (2*this->order)-1;
}

int Node::minimum_items() const {
    return this->order-1;
}

bool Node::search(int val) {
    int i = 0;
    while (i < this->currentKeys && val > this->keys[i]) i++;
    if (keys[i] == val) return keys[i] == val;
    if (this->leaf) return false;
    return this->sons[i]->search(val);
}

Node::~Node() {
    delete this->sons;
    /* STOS somehow won't accept that solution
     * for (int i = 0; i < this->currentKeys - 1; i++) {
        delete this->sons[i];
    }*/
}
