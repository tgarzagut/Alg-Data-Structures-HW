#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

#include <vector>
#include <unordered_map>
#include <utility> // Includes std::pair and std::swap
#include <stdexcept> // Includes std::runtime_error for exception handling

using namespace std;

template <typename T>
class MinPriorityQueue
{
private:
    vector<pair<T, int> > H; // Heap storing pairs of elements and their priorities
    unordered_map<T, int> I; // Map from elements to their indices in the heap

    void moveUp(int idx)
    {
        while (idx > 0 && H[parent(idx)].second > H[idx].second) {
            swap(H[idx], H[parent(idx)]);
            I[H[idx].first] = idx;
            I[H[parent(idx)].first] = parent(idx);
            idx = parent(idx);
        }
    }

    void moveDown(int idx)
    {
        int size = H.size();
        while (true) {
            int smallest = idx;
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;

            if (left < size && H[left].second < H[smallest].second) {
                smallest = left;
            }
            if (right < size && H[right].second < H[smallest].second) {
                smallest = right;
            }
            if (smallest != idx) {
                swap(H[idx], H[smallest]);
                I[H[idx].first] = idx;
                I[H[smallest].first] = smallest;
                idx = smallest;
            } else {
                break;
            }
        }
    }

    int parent(int idx) {
        return (idx - 1) / 2;
    }

public:
    MinPriorityQueue() {}

    bool isEmpty() const {
        return H.empty();
    }

    void push(T x, int p)
    {
        H.push_back(make_pair(x, p));
        I[x] = H.size() - 1;
        moveUp(H.size() - 1);
    }

    T front()
    {
        if (!isEmpty())
            return H[0].first;
        throw runtime_error("Priority queue is empty");
    }

    void pop()
    {
        if (isEmpty())
            throw runtime_error("Priority queue is empty");
        I.erase(H[0].first);
        H[0] = H.back();
        H.pop_back();
        if (!H.empty()) {
            I[H[0].first] = 0;
            moveDown(0);
        }
    }

    void decrease_key(T x, int new_p)
    {
        if (I.find(x) == I.end() || H[I[x]].second <= new_p)
            throw invalid_argument("New priority is not smaller or element not found");
        H[I[x]].second = new_p;
        moveUp(I[x]);
    }
};

#endif