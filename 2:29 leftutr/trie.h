class trie {
    private:
        class node{
            bool marked;
            node* children[256];

            node(){
                marked = false;
                for (int i = 0; i < 256; i++){
                    children[i] = nullptr;
                }
            }
        };
        node* root;
    public:
        trie(){
        root = new node();
        }
        void insert(string s){
            node* arrow = root;
            for(int i = 0; i < s.size(); i++){
                if(arrow->children[s[i]] == nullptr){
                    arrow->children[s[i]] = new node;
                }
                arrow = arrow->children[s[i]];
            }
            arrow->marked = true;
        }
        void printAll(){
            node* curr = root;
            std::cout << 
        }
};