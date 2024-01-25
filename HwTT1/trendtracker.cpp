#include "trendtracker.h"
using namespace std;
#include <vector>
#include <string>

// Creates a new Trendtracker tracking no hashtags.
 //
 // Must run in O(1) time.
Trendtracker :: Trendtracker(){
 E.clear();
}
// Inserts a hashtag (tweeted 0 times) into the Trendtracker.
// If the hashtag already is in Trendtracker, does nothing.
//
// Must run in O(n) time.
void Trendtracker :: insert(string ht){
 for(int i =0; i < E.size(); i++){
 if(ht == E.at(i).hashtag){
 return;
 }
 }
 Entry newEntry;
 newEntry.hashtag = ht;
 newEntry.pop = 0;
 E.push_back(newEntry);
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
// Must run in O(n) time.
void Trendtracker :: tweeted(string ht){
 for(int i =0; i < E.size(); i++){
 if(ht == E.at(i).hashtag){
 ++E.at(i).pop;
 }
 }
}
// Returns the number of times a hashtag has been tweeted.
// If the hashtag does not exist in Trendtracker, returns -1.
//
// Must run in O(n) time.
int Trendtracker :: popularity(string name){
 for(int i =0; i < E.size(); i++){
 if(name == E.at(i).hashtag){
 return E.at(i).pop;
 }
 }
 return -1;
}
// Returns a most-tweeted hashtag.
// If the Trendtracker has no hashtags, returns "".
//
// Must run in O(n) time.
string Trendtracker :: top_trend(){
 int max = 0;
 if(E.size() != 0){
 for(int i =0; i < E.size(); i++){
 if(E.at(i).pop > E.at(max).pop){
 max = i;
 }
 }
 return E.at(max).hashtag;
 }
 else{
 return "";
 }
 
}
// Fills the provided vector with the 3 most-tweeted hashtags,
// in order from most-tweeted to least-tweeted.
//
// If there are fewer than 3 hashtags, then the vector is filled
// with all hashtags (in most-tweeted to least-tweeted order).
//
// Must run in O(n) time.
void Trendtracker :: top_three_trends(vector<string> &T){
 T.clear();
 int max1 = -1;
 int max2 = -1;
 int max3 = -1;
 string hash1,hash2,hash3;
 for (int i= 0;i < E.size(); i++){
 Entry &trend = E.at(i);
 if (trend.pop > max1){
 max3 = max2;
 hash3 = hash2;
 max2 = max1;
 hash2 = hash1;
 max1 = trend.pop;
 hash1 = trend.hashtag;
 } 
 else if(trend.pop > max2){
 max3 = max2;
 hash3 = hash2;
 max2 = trend.pop;
 hash2 = trend.hashtag;
 } 
 else if(trend.pop > max3){
 max3 = trend.pop;
 hash3 = trend.hashtag;
 }
 }
 if (max1 != -1) {
 T.push_back(hash1);
 }
 if (max2 != -1) {
 T.push_back(hash2);
 }
 if (max3 != -1) {
 T.push_back(hash3);
 }
}
// Remove the given hashtag from the trendtracker.
//
// Must run in O(n) time.
void Trendtracker :: remove(string ht){
 for(int i = 0; i < E.size(); i++){
 if(ht == E.at(i).hashtag){
 swap(E.at(i), E.back());
 E.pop_back();
 }
 }
}
// Fills the provided vector with the k most-tweeted hashtags,
// in order from most-tweeted to least-tweeted.
//
// If there are fewer than k hashtags, then the vector is filled
// with all hashtags (in most-tweeted to least-tweeted order).
//
// Must run in O(nk) time.
void Trendtracker :: top_k_trends(vector<string> &T, int k){
 T.clear();
 vector<int> highest; 
 for (int i=0; i < min(k, static_cast<int>(E.size())); ++i) {
 int max = 0;
 for (int j=1; j < E.size(); j++) {
 if (find(highest.begin(), highest.end(), j) == highest.end() && E.at(j).pop > E.at(max).pop) {
 max = j;
 }
 }
 highest.push_back(max);
 }
 for(auto i = 0; i < highest.size(); i++){
 T.push_back(E.at(highest.at(i)).hashtag);
 }
}
