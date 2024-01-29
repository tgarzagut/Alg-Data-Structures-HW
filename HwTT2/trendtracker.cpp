#include "trendtracker.h"

using namespace std;

#include <cassert>
#include <fstream>
#include <vector>
#include <string>


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
	//Entry current;

	while(getline(inFS, hash)){
        Entry current;
		current.hashtag = hash;
		current.pop = 0;
		E.push_back(current);
	}
    inFS.close();


    if(E.size() == 0){
        return;
    }
    if(E.size() == 1){
        S.push_back(0);
    }
    if(E.size() == 2){
        S.push_back(0);
        S.push_back(1);
    }
    if(E.size() >= 3){
        for(int i=0; i<3; i++){
            S.push_back(i);
        }
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
    //if its there in the vector
        for(int i=0; i<S.size(); i++){
            if(x == S[i]){
                for(int j = i; j>0; j--){
                    if(E[S[j]].pop > E[S[j-1]].pop){
                        swap(S[i], S[i - 1]);
                    }
                }
                return;
            } 
        }
    //if not previously in top three
        if(E[x].pop > E[S[0]].pop){
            S[2] = S[1];
            S[1] = S[0];
            S[0] = x;
        }
        else if(E[x].pop > E[S[1]].pop){
            S[2] = S[1];
            S[1] = x;
        }
        else if(E[x].pop > E[S[2]].pop){
            S[2] = x;
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
        return E[x].pop;
    }
    return -1;
}

// Returns a most-tweeted hashtag.
// If the Trendtracker has no hashtags, returns "".
//
// Must run in O(1) time.
string Trendtracker :: top_trend(){
	if(S.size() > 0){
		return E[S[0]].hashtag;
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

        for(int i = 0; i<S.size(); i++){
            T.push_back(E[S[i]].hashtag);

    }
}

int Trendtracker:: search(string ht){
	int left = 0;
    int right = E.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (E[mid].hashtag == ht) {
            return mid;
        }
        else if (E[mid].hashtag < ht) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
	return -1;

}