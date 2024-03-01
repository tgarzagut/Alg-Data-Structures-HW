#include "autocompleter.h"
// Creates a new Autocompleter with an empty dictionary.
	//
	// Must run in O(1) time.
	Autocompleter::Autocompleter(){

    }

	// Adds a string x to the dictionary.
	// If x is already in the dictionary, does nothing.
	//
	// Must run in O(log(n)) time.
	void Autocompleter::insert(string x, int freq){
		Entry newEntry;
		newEntry.s = x;
		newEntry.freq = freq;
		Node* newNode = new Node(newEntry);

    }

	// Returns the number of strings in the dictionary
	// of possible completions.
	//
	// Must run in O(n) time.
	int Autocompleter::size(){

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

    }

