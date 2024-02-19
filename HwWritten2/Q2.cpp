#include <vector>
#include <iostream>

class node {
    public:
        double data;
        node* left;
        node* right;

        node(double value){
            data = value;
            left = nullptr;
            right = nullptr;
        }
};

node* buildTree(std::vector<double> &A, int start, int end){
    if (start > end){
        return nullptr;
    }
    int mid = (start + end) / 2;
    node* root = new node(A[mid]);

    root->left = buildTree(A, start, mid - 1);
    root->right = buildTree(A, mid + 1, end);

    return root;
}