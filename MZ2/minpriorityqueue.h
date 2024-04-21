
#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

// NOTE: You may not include any other libraries!
#include <unordered_map>
#include <vector>
#include <utility> // Has pair and swap

using namespace std;

template <typename T>
class MinPriorityQueue
{
// For the mandatory running times below:
    //
    // n is the number of elements in the MinPriorityQueue.
    //
    // Assume that the operations of unordered_map are O(1) time
    // (they are average case, but not worst-case).

public:
// Creates an empty MinPriorityQueue
    MinPriorityQueue()
    {
    }

// Returns the number of elements in the MinPriorityQueue.
    //
    // Must run in O(1) time.
    int size()
    {
        return H.size();
    }

// Pushes a new value x with priority p
    // into the MinPriorityQueue.
    //
    // Must run in O(log(n)) time.
    void push(T x, int p)
    {
        H.push_back(make_pair(x, p));
        I[x] = H.size() - 1;
        moveUp(H.size() - 1);
    }

// Returns the value at the front of the MinPriorityQueue.
    // Undefined behavior if the MinPriorityQueue is empty.
    //
    // Must run in O(1) time.
    T front()
    {
        return H[0].first;
    }

// Removes the value at the front of the MinPriorityQueue.
    // Undefined behavior if the MinPriorityQueue is empty.
    //
    // Must run in O(log(n)) time.
    void pop()
    {
        if (H.empty()){
    		return;
		}
		H[0] = std::move(H.back());
		H.pop_back();
		if (!H.empty()){
    		moveDown(0);
		}
    }

// If x is in the MinPriorityQueue
    // with current priority at least new_p,
    // then changes the priority of x to new_p.
    // Undefined behavior otherwise.
    //
    // Must run in O(log(n)) time.
    void decrease_key(T x, int new_p)
    {
        int vec = I[x];
        H[vec].second = new_p;
        moveUp(vec);
    }

private:
// You don't need any other instance variables,
    // but you can add some if you want to.
    vector<pair<T, int> > H;  // The heap. Holds the number of elements inside the heap.
    unordered_map<T, int> I; // Maps values to their indices in H.

//extra methods
    T getKeyAtIndex(int index) {
        for (const auto& pair : I) {
            if (pair.second == index) {
                return pair.first;
            }
        }
            return nullptr;
    }
    int parent(int i)
    {
        return (i - 1) / 2;
    }

    pair<int, int> children(int i)
    {
        int child1 = 1 + (2 * i);
        int child2 = 2 + (2 * i);
        return make_pair(child1, child2);
    }

    void moveUp(int i)
    {
		while(i > 0){
			int index = (i - 1) / 2;
			if(H[i].second < H[index].second) {
				swap(H[i], H[index]);
				swap(I[H[i].first], I[H[index].first]);
				i = index;
			}
			else {
				break;
			}
		}
    }

    void moveDown(int i)
    {
        int sizeheap = H.size();
		while (true) {
			int s = i;
			int child1 = 2 * i + 1;
			int child2 = 2 * i + 2;

			if (child1 < sizeheap && H[child1].second < H[s].second) {
				s = child1;
			}

			if (child2 < sizeheap && H[child2].second < H[s].second) {
				s = child2;
			}

			if (s != i) {
				swap(H[i], H[s]);
				swap(I[H[i].first], I[H[s].first]);
				i = s;
			} 
			else {
				break;
			}
		}
    }
};

#endif
