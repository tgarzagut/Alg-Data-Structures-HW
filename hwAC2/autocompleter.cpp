#include "autocompleter.h"
#include <iostream>
// Creates a new Autocompleter with an empty dictionary.
    //
    // Must run in O(1) time.
Autocompleter::Autocompleter() {
    Node* newNode = new Node();
    root = newNode;
    count = 0;
}

// Adds a string x to the dictionary.
    // If x is already in the dictionary, does nothing.
    //
    // Must run in O(1) time.
void Autocompleter::insert(string x, int freq){
    Node* arrow = root;
    Entry newEntry;
    newEntry.s = x;
    newEntry.freq = freq;
    int idx = arrow->top.size();

    //for the root  
    while (idx > 0 && arrow->top[idx - 1].freq < freq){
        idx--;
    }
    arrow->top.insert(arrow->top.begin() + idx, newEntry);

    while (arrow->top.size() > 3){
        arrow->top.pop_back();
    }
    
    for (int i = 0; i < x.size(); i++){
        if (arrow->children[(int)x[i]] == nullptr){
            arrow->children[(int)x[i]] = new Node;
        }

        arrow = arrow->children[(int)x[i]];
        int idx = arrow->top.size();
        
        while (idx > 0 && arrow->top[idx - 1].freq < freq){
            idx--;
        }

        arrow->top.insert(arrow->top.begin() + idx, newEntry);

        while (arrow->top.size() > 3){
            arrow->top.pop_back();
        }
    }

    if (arrow->marked != true){
        count++;
        arrow->marked = true;
    }

}

// Returns the number of strings in the dictionary.
    // 
    // Must run in O(1) time.
int Autocompleter::size(){
    return count;
}

// Fills the vector T with the three most-frequent completions of x.
    // If x has less than three completions, then 
    // T is filled with all completions of x.
    // The completions appear in T from most to least frequent.
    // 
    // Must run in O(1) time.
void Autocompleter::completions(string x, vector<string> &T){
    T.clear();
    Node* arrow = root;
    for (int i = 0; i < x.size(); i++){
        if(arrow->children[(int)x[i]] == nullptr){
            return;
        }
        arrow = arrow->children[(int)x[i]];
    }

    for(int i = 0; i < arrow->top.size(); i++){
        T.push_back(arrow->top[i].s);
    }
    
}