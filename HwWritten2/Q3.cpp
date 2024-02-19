#include <iostream>
#include <queue>

class node {
public:
    int data;
    node* left;
    node* right;

    node(int value) : data(value), left(nullptr), right(nullptr) {}
};

void levelOrderTraversal(node * r){
    if (r == nullptr){
        return;
    }
    //store parent then children then children of children etc in a queue
    std::queue<node*> list;
    list.push(r);

    int nodesInLevel = 1;

    while (nodesInLevel > 0) {

        for (int i = 0; i < nodesInLevel; ++i) {
            node* current = list.front();
            

            std::cout << current->data << " ";
            list.pop();
            if (current->left != nullptr) {
                list.push(current->left);
            }
            if (current->right != nullptr) {
                list.push(current->right);
            }
        }

        nodesInLevel = list.size();
    }
}