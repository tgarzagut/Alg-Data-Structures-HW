#include <iostream>
#include "Q3.cpp"

void inorderTraversal(node* root) {
    if (root == nullptr) return;
    inorderTraversal(root->left);
    std::cout << root->data << " ";
    inorderTraversal(root->right);
}

int main(){
    // std::vector<double> sortedArray1;
    // sortedArray1.push_back(1.2);
    // sortedArray1.push_back(2.4);
    // sortedArray1.push_back(3.6);
    // sortedArray1.push_back(4.8);
    // sortedArray1.push_back(6.0);
    // sortedArray1.push_back(7.2);
    // sortedArray1.push_back(8.4);

   
    // double key = 4.8; // Key to search for

    // int index = fastFind(sortedArray1, key);
    // if (index != -1) {
    //     std::cout << "Key " << key << " found at index " << index << std::endl;
    // } else {
    //     std::cout << "Key " << key << " not found in the array." << std::endl;
    // }

    // int n = sortedArray1.size();

    // node* root = buildTree(sortedArray1, 0, n - 1);

    // std::cout << "Inorder traversal of the constructed binary search tree: " << std::endl;
    // inorderTraversal(root);
    // std::cout << std::endl;

    // Create the binary tree
    node* root = new node(1);
    root->left = new node(2);
    root->right = new node(3);
    root->left->left = new node(4);
    root->left->right = new node(5);
    root->right->left = new node(6);
    root->right->right = new node(7);

    // Perform level order traversal of the binary tree
    levelOrderTraversal(root);

    // Delete the dynamically allocated memory
    // Code to delete the nodes in the tree goes here...

    return 0;
}