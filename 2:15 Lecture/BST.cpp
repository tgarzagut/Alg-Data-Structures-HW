template <class T>

class BinarySearchTree {
    private:
    class node {
        public:
        double data;
        node* left;
        node* right;

        node(double x){
            data = x;
            left = nullptr;
            right = nullptr;
        }
    };

    insert(node* p, double x);
    node* root;

public:
    binarySearchTree(){
        root = nullptr;
    }

    //insert x into tree using *p
    void insert(node* &p = root, double x){

        if (p == nullptr){
            root = new node(x);
        }
        else{
            node* curr = root;
            while(){
                if (x<p->data){
                    //insert item into left subtree
                    insert(p->left, x)
                }
                else{
                    insert(p->right, x)
                }
            }
        }
    }
    void display(node* p){
        if ( p == nullptr){
            //do nothing, no items to print
        }
        else{
            display(p->left);
            std::cout << p->data << endl;
            display(p->right);
            
        }
    }
    int height(node* p){
        
        if(p->left==nullptr && p->right==nullptr){

        }
    }
};