#include "trendtracker.h"

using namespace std;

#include <cassert>
#include <fstream>
#include <vector>
#include <string>

#include <iostream>


// Creates a Trendtracker containing hashtags
// found in the provided file.
// The file is promised to have the following format:
//
// string1
// string2
// ...
// stringN
//
// where string1 < string2 < ... < stringN
//
// Must run in O(n) time.
Trendtracker :: Trendtracker(string filename){
    ifstream inFS;
	inFS.open(filename);

    if(!inFS.is_open()){
        return;
    }

	string hash;
	Entry current;

	while(getline(inFS, hash)){
		current.hashtag = hash;
		current.pop = 0;
		E.push_back(current);
	}
    inFS.close();

    S.clear();
    for(int i=0; i<3; i++){
        S.push_back(-1);
    }
}

// Return the number of hashtags in the Trendtracker.
//
// Must run in O(1) time.
int Trendtracker :: size(){
    return E.size();
}

// Adds 1 to the total number times a hashtag has been tweeted.
// If the hashtag does not exist in TrendTracker, does nothing.
//
// Must run in O(log(n)) time.
void Trendtracker :: tweeted(string ht){
    int x = search(ht);
    if(x != -1){
        E[x].pop += 1;
        bool not_equal = (x != S[0] && x != S[1] && x != S[2]);
        if(S[2] == -1 || (E[x].pop > E[S[2]].pop && not_equal) )
        {
            if(x != S[1] && S[0] != x){
                S[2] = x;
            }
        }
        if((S[1] == -1 || E[S[2]].pop > E[S[1]].pop )){
            swap(S[2], S[1]);
        }
        if((S[0] == -1 || E[S[1]].pop > E[S[0]].pop )){
            swap(S[1], S[0]);
        }
    }
}

// Returns the number of times a hashtag has been tweeted.
// If the hashtag does not exist in Trendtracker, returns -1.
//
// Must run in O(log(n)) time.
int Trendtracker :: popularity(string name){
	//call search
    int x = search(name);
	if(x != -1){
        return E.at(x).pop;
    }
    return -1;
}

// Returns a most-tweeted hashtag.
// If the Trendtracker has no hashtags, returns "".
//
// Must run in O(1) time.
string Trendtracker :: top_trend(){
	if(E.size()> 0){
		return  E.at(S.at(0)).hashtag;
	}
    return "";
}

// Fills the provided vector with the 3 most-tweeted hashtags,
// in order from most-tweeted to least-tweeted.
//
// If there are fewer than 3 hashtags, then the vector is filled
// with all hashtags (in most-tweeted to least-tweeted order).
//
// Must run in O(1) time.
void Trendtracker :: top_three_trends(vector<string> &T){
    T.clear();
    for(int i=0; i<3; i++){
        if(S.at(i) != -1){
            T.push_back(E.at(S.at(i)).hashtag);
        }
        else{
            T.push_back("");
        }
    }
}

int Trendtracker:: search(string ht){
	int left = 0;
    int right = E.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (E.at(mid).hashtag == ht) {
            return mid;
        }
        else if (E.at(mid).hashtag < ht) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
	return -1;

}