
class queueLL
{
private:
	//put what you need here...
	class node
	{
	public:
		//put what you need in here
		int data;
		node* next;

		node(){
			next = nullptr;
		}
	};
	node* top;
	node* bottom;

public:
	queueLL() {
		top = nullptr;
		bottom = nullptr;
	}

	~queueLL() {

	}

	//add item to back of queue
	void enqueue(int x) {
		node* temp = new node();
		temp->data = x;
		temp->next = nullptr;
		if(top == nullptr){
			top = temp;
			bottom = temp;
		}
		else{
			bottom->next = temp;
			bottom = temp;
		}
	}

	//remove and return first item from queue
	int dequeue() {
		node* temp;
		temp = top;
		int value = top->data;
		top = top->next;
		delete temp;
		return value;
	}

	bool empty() {
		if(top==nullptr){
			return true;
		}
		else{
			return false;
		}
	}

	//For the final part of the test program, template this class
	//and add a decimate method.

};