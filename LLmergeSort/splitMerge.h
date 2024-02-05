//Linked lists and merge sort:  Implement the methods “split”, “merge”, “slowSort”, and “mergeSort” as described in the following test file.   slowSort can be bubbleSort or selectionSort (or some other sort that is not mergeSort), and mergeSort should use the split and merge methods to implement a O(n log n) Merge Sort.  Apply both sorting algorithms to sort whale.txt and write the output to slowSortedWhale.txt and mergeSortedWhale.txt respectively.  Time each sort with timing code and include the running times with your submission.

#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class linkedList
{
private:
	class node
	{
	public:
		//put what you need in here
		T data;
		node* next;
		node* back;
        //O(1)
		node(){
			next = nullptr;
			back = nullptr;
		}
	};
	node* top;
	node* bottom;

public:

    //O(1)
	linkedList() {
		top = nullptr;
		bottom = nullptr;
	}

    //O(1)
    void push_back(T f){
        //adds a given item to the back of the list
        node* temp = new node();
        temp->data = f;
        if(bottom == nullptr){
            top = temp;
            bottom = temp;
            temp->next = nullptr;
            temp->back = nullptr;
        }
        else{
            bottom->next = temp;
            temp->back = bottom;
            bottom = temp;
        }

    }

    //O(n)
    void print(){
        node* curr = top;
        while(curr != nullptr){
            cout << curr->data << endl;
            curr = curr->next;
        }
        cout << endl;
    }

    //O(n)
    void split(linkedList<T>& left, linkedList<T>& right){
     if(top == nullptr)
        return;
//time2 goes two nodes at a time and time1 one
    node* time2 = top;
    node* time1 = top;

    while(time2 != nullptr && time2->next != nullptr){
        time2 = time2->next->next;
        time1 = time1->next;
    }

    if(time1->back != nullptr)
        time1->back->next = nullptr;

    left.top = top;
    left.bottom = time1->back;
    right.top = time1;
    right.bottom = bottom;

    top = bottom = nullptr;
    }

    //O(n^2)
    void slowSort(){
    //bubble sort O(n^2)
        bool swapped = true;
        while (swapped) {
            swapped = false;
            node* curr = top;
            while (curr->next != nullptr) {
                if (curr->data > curr->next->data) {
                swap(curr->data, curr->next->data);
                swapped = true;
                }
                curr = curr->next;
            }
        }
    }

    //O(n + m) 
    void merge(linkedList<T>& left, linkedList<T>& right){
        top = bottom = nullptr;

        while(left.top != nullptr && right.top != nullptr){
            if(left.top->data < right.top->data){
                push_back(left.top->data);
                left.top = left.top->next;
            } else {
                push_back(right.top->data);
                right.top = right.top->next;
            }
        }
    //After one is empty, just insert what is left
        while(left.top != nullptr){
            push_back(left.top->data);
            left.top = left.top->next;
        }

        while(right.top != nullptr){
            push_back(right.top->data);
            right.top = right.top->next;
        }
    }

    //O(n)
    void loadFromFile(string filename){
        ifstream inFS;
        inFS.open(filename);

        if(!inFS.is_open()){
            cout << "Error: File not open." <<endl;
            return;
        }

        string word;
        while(inFS >> word){
            push_back(word);
        }

        inFS.close();
    }

    //O(nlogn)
    void mergeSort(){
        if (top == nullptr || top->next == nullptr){
            return;
        }
        linkedList<string> left;
        linkedList<string> right;
        split(left, right);

        left.mergeSort();
        right.mergeSort();

        merge(left, right);
    }

    //O(n)
    void writeToFile(string filename){
        
        ofstream outFS;
        outFS.open(filename);

        if(!outFS.is_open()){
            cout << "Error: File not open." << endl;
            return;
        }

        node* curr = top;
        while(curr != nullptr){
            outFS << curr->data << endl;
            curr = curr->next;
        }

        outFS.close();
    }


};