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
    if (this->keys[i] == val) return true;
    if (this->leaf) return false;
    return this->sons[i]->search(val);
}

/*
  TreeNode *TreeNode::search(int k) {
  int i = 0;
  while (i < n && k > keys[i])
    i++;

  if (keys[i] == k)
    return this;

  if (leaf == true)
    return NULL;

  return C[i]->search(k);
}
 */

int Node::get_key(int val) const {
    int i = 0;
    while (i < this->currentKeys && this->keys[i] < val) i++;
    return i;
}


void Node::remove(int val) {
    int index = this->get_key(val);
    if (index < this->currentKeys && this->keys[index] == val) {
        if (this->leaf) this->remove_leaf(index);
        else this->remove_nonleaf(index);
    } else {
        if (this->leaf) {
            return;
        }
        bool index_was_equal = (index == this->currentKeys);
        if (this->sons[index]->currentKeys < this->order) this->fill(index);
        if (index_was_equal && index > this->currentKeys) this->sons[index - 1]->remove(val);
        else this->sons[index]->remove(val);
    }
}

void Node::remove_leaf(int index) {
    // shift values to the left from keys
    for (int i = index + 1; i < this->currentKeys; i++) this->keys[i - 1] = this->keys[i];
    this->currentKeys--;
}

void Node::remove_nonleaf(int index) {
    int k = this->keys[index];
    if (this->sons[index]->currentKeys >= this->order) {
        int predecessor_key = getPredecessor(index);
        this->keys[index] = predecessor_key;
        this->sons[index]->remove(predecessor_key);
    } else if (this->sons[index + 1]->currentKeys >= this->order) {
        int successor_key = getSuccessor(index);
        this->keys[index] = successor_key;
        this->sons[index + 1]->remove(successor_key);
    } else {
        this->merge(index);
        this->sons[index]->remove(k);
    }
}

void Node::merge(int index) {
    Node *son = this->sons[index];
    Node *neighbour = this->sons[index + 1];
    son->keys[this->minimum_items()] = this->keys[index];
    // transfer keys and sons
    for (int i = 0; i < neighbour->currentKeys; i++)
        son->keys[this->order + i] = neighbour->keys[i];
    if (!son->leaf)
        for (int i = 0; i <= neighbour->currentKeys; i++)
            son->sons[this->order + i] = neighbour->sons[i];
    // shift the keys and sons
    for (int i = index + 1; i < this->currentKeys; i++) this->keys[i - 1] = this->keys[i];
    for (int i = index + 2; i <= this->currentKeys; i++) this->sons[i - 1] = this->sons[i];
    son->currentKeys += neighbour->currentKeys + 1;
    this->currentKeys--;
    delete neighbour;
}

int Node::getPredecessor(int index) const {
    Node * temp = this->sons[index];
    while (!temp->leaf) temp = temp->sons[temp->currentKeys];
    return temp->keys[temp->currentKeys - 1];
}

int Node::getSuccessor(int index) {
    Node * temp = this->sons[index + 1];
    while (!temp->leaf) temp = temp->sons[0];
    return temp->keys[0];
}

void Node::fill(int index) {
    if (index != 0 && this->sons[index - 1]->currentKeys >= this->order) this->borrow_prev(index);
    else if (index != this->currentKeys && this->sons[index + 1]->currentKeys >= this->order) this->borrow_next(index);
    else {
        if (index != this->currentKeys) this->merge(index);
        else this->merge(index - 1);
    }
}

void Node::borrow_prev(int index) {
    Node * son = this->sons[index];
    Node * neighbour = this->sons[index - 1];
    // shift keys and if not leaf - children of son
    for (int i = son->currentKeys - 1; i >= 0; i--)
        son->keys[i + 1] = son->keys[i];
    if (!son->leaf)
        for (int i = son->currentKeys; i >= 0; i--)
            son->sons[i + 1] = son->sons[i];

    son->keys[0] = this->keys[index - 1];
    if (!son->leaf)
        son->sons[0] = neighbour->sons[neighbour->currentKeys];
    this->keys[index - 1] = neighbour->keys[neighbour->currentKeys - 1];
    son->currentKeys++;
    neighbour->currentKeys--;
}

void Node::borrow_next(int index) {
    Node * son = this->sons[index];
    Node * neighbour = this->sons[index + 1];
    son->keys[son->currentKeys] = this->keys[index];
    if (!son->leaf)
        son->sons[son->currentKeys + 1] = neighbour->sons[0];
    this->keys[index] = neighbour->keys[0];
    // shift neighbour to the left (keys and sons ofc)
    for (int i = 1; i < neighbour->currentKeys; i++)
        neighbour->keys[i - 1] = neighbour->keys[i];
    if (!neighbour->leaf)
        for (int i = 1; i <= neighbour->currentKeys; i++)
            neighbour->sons[i - 1] = neighbour->sons[i];
    son->currentKeys++;
    neighbour->currentKeys--;
}



/*Node::~Node() {
    delete this->sons;
    /* STOS somehow won't accept that solution
     * for (int i = 0; i < this->currentKeys - 1; i++) {
        delete this->sons[i];
    }
}*/

