
class stackLL
{
private:
	class node
	{
	public:
		int data;
		node* next;

	//O(1)
		node(){
			next = nullptr;
		}
	};

	node * top;

public:
	//O(1)
	stackLL() {
		top = nullptr;
	}

	//O(n)
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

	//O(1)
	bool empty(){
		if(top == nullptr){
			return true;
		}
		else{
			return false;
		}
	}

	//O(1)
	void push(int x) {
		node* temp = new node();
		temp->data = x;
		temp->next = top;
		top = temp;
	}

	//O(1)
	int pop() {
		node* temp = top;
		top = top->next;
		int popped = temp->data;
		delete temp;
		return popped;
	}

	//O(i)
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