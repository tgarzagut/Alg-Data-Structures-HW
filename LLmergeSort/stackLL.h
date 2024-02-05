
class stackLL
{
private:
	class node
	{
	public:
		//put what you need in here
		int data;
		node* next;

	//O(1)
		node(){
			next = nullptr;
		}
	};

	node * top;

public:

	stackLL() {
		top = nullptr;
	}

	//Take care of memory leaks...
	~stackLL()
	{
        node *temp;
        while (top != nullptr)
        {
            temp = top;
            top = top->next;
            delete temp;
        }
	}

	//return true if empty, false if not
	bool empty(){
		if(top == nullptr){
			return true;
		}
		else{
			return false;
		}
	}
	//add item to top of stack
	void push(int x) {
		node* temp = new node();
		temp->data = x;
		temp->next = top;
		top = temp;
	}

	//remove and return top item from stack
	int pop() {
		node* temp = top;
		top = top->next;
		int popped = temp->data;
		delete temp;
		return popped;
	}

	//add item x to stack, but insert it
	//right after the current ith item from the top
	//(and before the i+1 item).
	void insertAt(int x, int i) {
		node* curr = top;
		node* temp = new node();
		temp->data = x;
		if(i==0){
			push(x);
			return;
		}
		else{
			for(int j = 1; j<i; j++){
				curr = curr->next;
			}
		}
		temp->next = curr->next;
		curr->next = temp;
	}

};