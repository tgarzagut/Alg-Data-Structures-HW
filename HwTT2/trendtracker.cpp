#include "trendtracker.h";

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

	string hashtag;
	Entry current;

	while(getline(inFS, hashtag)){
		current.hashtag = hashtag;
		current.pop = 0;
		E.push_back(current);
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
    E.at(search(ht)).pop += 1;
}

// Returns the number of times a hashtag has been tweeted.
// If the hashtag does not exist in Trendtracker, returns -1.
//
// Must run in O(log(n)) time.
int Trendtracker :: popularity(string name){
	//call search
	return E.at(search(name)).pop;
}

// Returns a most-tweeted hashtag.
// If the Trendtracker has no hashtags, returns "".
//
// Must run in O(1) time.
string Trendtracker :: top_trend(){
	if(E.size()> 0){
		return E.at(0).hashtag;
	}
}

// Fills the provided vector with the 3 most-tweeted hashtags,
// in order from most-tweeted to least-tweeted.
//
// If there are fewer than 3 hashtags, then the vector is filled
// with all hashtags (in most-tweeted to least-tweeted order).
//
// Must run in O(1) time.
void Trendtracker :: top_three_trends(vector<string> &T){
    for(int i=0; i<3; i++){
        if(E.at(i).hashtag.length() != 0){
            T.push_back(E.at(i).hashtag);
        }
    }
}

int Trendtracker:: search(string ht){
	int left = 0;
    int right = E.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Check if the target is present at the middle
        if (E.at(mid).hashtag == ht) {
            return mid;
        }

        // If target is greater, ignore the left half
        else if (E.at(mid).hashtag < ht) {
            left = mid + 1;
        }

        // If target is smaller, ignore the right half
        else {
            right = mid - 1;
        }
    }
	return -1;

}