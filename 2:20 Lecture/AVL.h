#include <iostream>

class avlTree {
    private:
    class node{
        public:

        double data;
        node* left;
        node* right;

        int height;
        node(double x){
            left = nullptr;
            right = nullptr;
            data = x;
            height = 0;
        }
    };
    int height(node* p){
        if (p==nullptr)
            return -1;
        else{
            
        }
    }
    void jfnsljfn();
    void updateHeight(node* p){
        p->height = 1 + std::max(height(p->left), height(p->right));
    }

    void rightRotation(node* &p){
        node* A = p;
        node* B = p->left;
        node* C = B->right;

        p = B;
        A->left = C;
        B->right = A;

        updateHeight(A);
        updateHeight(B);
    }

    void leftRotation(node* &p){
        node* A = p;
        node* B = p->left;
        node* C = B->left;

        p = B;
        A->left = C;
        B->left = A;

        updateHeight(A);
        updateHeight(B);
    }

    void leftRightRotation(node* &p){

    }

    void rightLeftRotation(node* &p){
        
    }

    void checkFixBalance(node* &p){
    // too high on the left
        if(height(p->left) - height(p->right) > 1){
            if(height(p->left->left) > height(p->left->right)){
                //single rotation
                rightRotation(p);

            }
            else{
                leftRightRotation(p);
            }
        }
        else if (height(p->right) - height(p->left) > 1){
            if(height(p->right->right) > height(p->right->left)){
                //single rotation
                leftRotation(p);

            }
            else{
                rightLeftRotation(p);
            }
        }
        else{
            // youre balanced, do nothing
        }
    }

    //uh oh, p is sus.. might not ve AVL balanved. Check for valance, if not balavnes, apply one of th e four rotations
    void insert(node* &p, double x){
        if (p == nullptr){
            p = new node(x);
        }
        else{
            if(x < p->data){
                
            }
            else{

            }
            updateHeight(p);
            checkFixBalance(p);
        }
    }
};