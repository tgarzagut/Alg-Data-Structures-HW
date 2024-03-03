#include "autocompleter.h"
#include <iostream>

// Creates a new Autocompleter with an empty dictionary.
	//
	// Must run in O(1) time.
	Autocompleter::Autocompleter(){
		root = nullptr;
    }

	// Adds a string x to the dictionary.
	// If x is already in the dictionary, does nothing.
	//
	// Must run in O(log(n)) time.
	void Autocompleter::insert(string x, int freq){
		Entry newEntry;
		newEntry.s = x;
		newEntry.freq = freq;
		insert_recurse(newEntry, root);
		std::cout << newEntry.s << " freq: " << newEntry.freq << std::endl;
    }

	// Returns the number of strings in the dictionary
	// of possible completions.
	//
	// Must run in O(n) time.
	int Autocompleter::size(){
		return size_recurse(root);
    }

	// Fills the vector T with the three most-frequent completions of x.
	// If x has less than three completions, then
	// T is filled with all completions of x.
	// The completions appear in T from most to least frequent.
	//
	// Must run fast.  In particular, you should not search all nodes in the
	// tree for possible completions.
	// Instead, only search regions of the tree for which a completion could
	// be present, which will yield a run time bound of O(k log n ) time,
	// where k is the number of completions in the tree.
	void Autocompleter::completions(string x, vector<string> &T){
		T.clear();
  		vector<Entry> Placeholder;
  		completions_recurse(x, root, Placeholder);
  		for(int i = 0; i < Placeholder.size(); i++){
    	T.push_back(Placeholder[i].s);
  		}  
	}


	// Optional helper methods (you'll probably want them)

	// Returns the size of the binary tree rooted at p.
	//
	// Should run in O(n) time.
	int Autocompleter::size_recurse(Node* p){
		if (p == nullptr) {
            return 0;
		}
        int _left = size_recurse(p->left);
        int _right = size_recurse(p->right);
        return 1 + _left + _right;
	}

	void Autocompleter::completions_recurse(string x, Node* p, vector<Entry> &C){
		//for now
	}

	// Inserts an Entry into an AVL tree rooted at p.
	//
	// Should run in O(log(n)) time.
	void Autocompleter::insert_recurse(Entry e, Node* &p){
		if (p == nullptr) {
            p = new Node(e);
        }
        if (e.s < p->e.s) {
            insert_recurse(e, p->left);
        } 
		else if (e.s > p->e.s) {
            insert_recurse(e, p->right);
        }
		rebalance(p);
		update_height(p);

    }

	// Rebalances the AVL tree rooted at p.
	// Helpful for insert().
	// Should be called on every node visited during
	// the search in reverse search order.
	// Should run in O(1) time.
	void Autocompleter::rebalance(Node* &p){
    if (p == nullptr) {
        return; // Null check
    }

    if (height(p->left) - height(p->right) >= 2){//left height is too high
        if (p->left != nullptr && height(p->left->left) > height(p->left->right)) {
            right_rotate(p);
        } 
        else {
            if (p->left != nullptr) {
                left_rotate(p);
            }
            if (p->left != nullptr) {
                right_rotate(p);
            }
        }
    }
    else if (height(p->right) - height(p->left) >= 2){
        if (p->right != nullptr && height(p->right->right) > height(p->right->left)) {
            left_rotate(p);
        }
        else {
            if (p->right != nullptr) {
                right_rotate(p);
            }
            if (p->right != nullptr) {
                left_rotate(p);
            }
        }   
    }
	}

	// Perform left and right rotations
	// of an AVL tree rooted at p (helpful for implementing rebalance).
	//
	// Should run in O(1) time.
	void Autocompleter::right_rotate(Node* &p){
		Node* A = p;
		Node* B = p->left;
		Node* br = B->right;

		A->left = br;
		B->right = A;
		p = B;

		update_height(A);
		update_height(B);
	}
	void Autocompleter::left_rotate(Node* &p){
		Node* A = p;
		Node* B = p->right;
		Node* bl = B->left;

		A->right = bl;
		B->left = A;
		p = B;

		update_height(A);
		update_height(B);
	}

