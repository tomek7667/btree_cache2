#include <iostream>
#include "Node.h"
#include <cstring>
#define COMMAND_SIZE 1
using namespace std;


int main() {
    char choice[COMMAND_SIZE];
    int val, ch, MIN, MAX;
    int order = 2;
    Node* root = nullptr;
    while (cin >> choice) {
        MIN = order - 1;
        MAX = (2 * order) - 1;
        //cout << "MIN: " << MIN << endl << "MAX: " << MAX << endl;
        if (!strcmp(choice, "I")) {
            cin >> order;
            // create tree of order
        } else if (!strcmp(choice, "A")) {
            cin >> val;
            //insert(val, &root, MIN, MAX);
        } else if (!strcmp(choice, "?")) {
            cin >> val;
            bool found = false;
            //search(val, &ch, root, &found);

            if (!found) cout << val << " -\n";
        } else if (!strcmp(choice, "P")) {
            //revSwitch(root);
            cout << endl;
        } else if (!strcmp(choice, "L")) {
            cin >> order;
        } else if (!strcmp(choice, "S")) {
            // TODO
        } else if (!strcmp(choice, "R")) {
            cin >> val;
            // TODO
        } else if (!strcmp(choice, "#")) {
            ;;
        } else if (!strcmp(choice, "X")) {
            exit(1);
        } else if (!strcmp(choice, "C")) {
            // TODO
        } else {
            cout << "Nie znam komendy : " << choice << endl;
        }
    }


    return 0;
}
