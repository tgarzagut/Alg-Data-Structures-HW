//Linked lists and merge sort:  Implement the methods “split”, “merge”, “slowSort”, and “mergeSort” as described in the following test file.   slowSort can be bubbleSort or selectionSort (or some other sort that is not mergeSort), and mergeSort should use the split and merge methods to implement a O(n log n) Merge Sort.  Apply both sorting algorithms to sort whale.txt and write the output to slowSortedWhale.txt and mergeSortedWhale.txt respectively.  Time each sort with timing code and include the running times with your submission.

#include <iostream>

using namespace std;

template <class T>
class linkedList
{
private:
	//put what you need here...
	class node
	{
	public:
		//put what you need in here
		T data;
		node* next;
		node* back;

		node(){
			next = nullptr;
			back = nullptr;
		}
	};
	node* top;
	node* bottom;

public:
	linkedList() {
		top = nullptr;
		bottom = nullptr;
	}

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

    void print(){
        node* curr = top;
        while(curr != nullptr){
            cout << curr->data << endl;
            curr = curr->next;
        }
        cout << endl;
    }

    void split(linkedList<T>& left, linkedList<T>& right){
        int count = 0;
        node* curr = top;
        while(curr != nullptr){
            curr = curr->next;
            count++;
        }
        curr = top;
        for(int i = 0; i<count; i++){
            if(i < count/2){
                left.push_back(curr->data);

            }
            else{
                right.push_back(curr->data);
            }
            node* rem = curr;
            curr= curr->next;
            delete rem;
        }
        top = bottom = nullptr;
    }

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

    void merge(linkedList<T>& left, linkedList<T>& right){
        node* rem;
        while(left.top != nullptr && right.top != nullptr){

            if(left.top != nullptr && right.top == nullptr){
                push_back(left.top->data);
                delete left.top;
            }
            else if(right.top != nullptr && left.top == nullptr){
                push_back(right.top->data);
                delete right.top;
            }
            else if(left.top->data <= right.top->data){
                push_back(left.top->data);
                if(left.top->next != nullptr){
                    rem = left.top;
                    left.top = left.top->next;
                    delete rem;
                }
                else{
                    delete left.top;
                }
            }
            else if(right.top->data <= left.top->data){
                push_back(right.top->data);
                if(right.top->next != nullptr){
                    rem = right.top;
                    right.top = right.top->next;
                    delete rem;
                }
                else{
                    delete right.top;
                }
            }
        }
    }

};