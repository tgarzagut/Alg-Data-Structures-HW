#include "autocompleter.h"

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
	vector<Entry> list;
	completions_recurse(x, root, list);
	for(int i = 0; i < list.size(); i++){
		T.push_back(list[i].s);
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
	if(p == nullptr){
		return;
	}
	bool matchesp = true;
	for (auto i = 0; i < x.length(); i++) {
		if (i >= p->e.s.length() || p->e.s[i] != x[i]) {
			matchesp = false;
			break;
		}
	}

	if (matchesp) {
		C.push_back(p->e);
		for (int i = C.size() - 1; i > 0; i--) {
			if (C[i - 1].freq < C[i].freq) {
				Entry temp = C[i - 1];
				C[i - 1] = C[i];
				C[i] = temp;
			}
		}
		if (C.size() > 3) {
			C.pop_back();
		}
	}
	completions_recurse(x, p->left, C);
	completions_recurse(x, p->right, C);
}


// Inserts an Entry into an AVL tree rooted at p.
	//
	// Should run in O(log(n)) time.
void Autocompleter::insert_recurse(Entry e, Node* &p){
	if (p == nullptr) {
		p = new Node(e);
	}
	else {
		if (e.s < p->e.s) {
			insert_recurse(e, p->left);
		} 
		else if (e.s > p->e.s) {
			insert_recurse(e, p->right);
		} 
		else {
			return;
		}

		update_height(p);
		rebalance(p);
	}
}

// Rebalances the AVL tree rooted at p.
	// Helpful for insert().
	// Should be called on every node visited during
	// the search in reverse search order.
	// Should run in O(1) time.
void Autocompleter::rebalance(Node* &p){

	if ((height(p->left) - height(p->right)) >= 2) {
		if (height(p->left->left) >= height(p->left->right)) {
			right_rotate(p);
		} 
		else {
			left_rotate(p->left);
			right_rotate(p);
		}
	} 
	else if (height(p->right) - height(p->left) >= 2) {
		if (height(p->right->left) <= height(p->right->right)) {
			left_rotate(p);
		} 
		else {
			right_rotate(p->right);
			left_rotate(p);
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

