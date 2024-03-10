		#include "autocompleter.h"
        #include <iostream>
        // Creates a new Autocompleter with an empty dictionary.
		//
		// Must run in O(1) time.
		Autocompleter::Autocompleter(){
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

            for (int i = 0; i < x.size(); i++){
                if (arrow->children[(int)x[i]] == nullptr)
                    arrow->children[(int)x[i]] = new Node;
                if(arrow->marked == true){
                    if (arrow->top.empty()){
                        arrow->top.push_back(newEntry);
                    }
                    else{
                        int ts = arrow->top.size();
                        arrow->top.push_back(newEntry);
                        int j = ts - 1;
                        for(int i = ts-2; i >=0; i++){
                            if(arrow->top[i].freq > newEntry.freq){
                                swap(arrow->top[i], arrow->top[j]);
                                j--;
                            }
                        }
                    }
                arrow = arrow->children[(int)x[i]];
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
            
            for(int i = 0; i < 256; i++){
                
            }
        }