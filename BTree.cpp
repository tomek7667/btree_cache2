//
// Created by Tomek on 17.05.2021.
//

#include "BTree.h"
#include <iostream>

BTree::BTree(int order) {
    this->order = order;
    this->root = nullptr;
}

BTree::BTree() {
    this->root = nullptr;
}

void BTree::traverse() const {
    if (this->root != nullptr) this->root->traverse();
}

void BTree::insert(int val) {
    if (root == nullptr) {
        // no root
        root = new Node(this->order, true);
        root->keys[0] = val;
        root->currentKeys++;
    } else {
        if (root->currentKeys == root->maximum_items()) {
            Node *temp = new Node(this->order, false);
            temp->sons[0] = root;
            temp->split(0, root);
            int which_son = 0;
            if (temp->keys[0] < val) which_son++;
            temp->sons[which_son]->insert_nfull(val);
            root = temp;
        } else {
            root->insert_nfull(val);
        }
    }
}

bool BTree::search(int val) {
    return root != nullptr && root->search(val);
}

void BTree::remove(int val) {
    if (this->root == nullptr) return;
    this->root->remove(val);
    if (root->currentKeys == 0) {
        Node *temp = this->root;
        if (root->leaf) this->root = nullptr;
        else this->root = this->root->sons[0];
        delete temp;
    }
}
