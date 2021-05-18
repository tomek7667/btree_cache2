#include <iostream>
#include "Node.h"
#include "BTree.h"
#include <cstring>
#define COMMAND_SIZE 1
using namespace std;


int main() {
    char choice[COMMAND_SIZE];
    int val;
    int order;
    BTree tree;
    while (cin >> choice) {
        if (!strcmp(choice, "I")) {
            cin >> order;
            tree = BTree(order);
        } else if (!strcmp(choice, "A")) {
            cin >> val;
            tree.insert(val);
        } else if (!strcmp(choice, "?")) {
            cin >> val;
            cout << val;
            tree.search(val) ? cout << " +\n" : cout << " -\n";
        } else if (!strcmp(choice, "P")) {
            tree.traverse();
            cout << endl;
        } else if (!strcmp(choice, "L")) {
            cin >> order;
            tree = BTree(order);
        } else if (!strcmp(choice, "S")) {
            // TODO
        } else if (!strcmp(choice, "R")) {
            cin >> val;
            tree.remove(val);
        } else if (!strcmp(choice, "#")) {
            ;;
        } else if (!strcmp(choice, "X")) {
            while (tree.root != nullptr) tree.remove(tree.root->keys[tree.root->currentKeys-1]);
            return 1;
        } else if (!strcmp(choice, "C")) {
            // TODO
        } else {
            cout << "Nie znam komendy : " << choice << endl;
        }
    }
    return -1;
}
