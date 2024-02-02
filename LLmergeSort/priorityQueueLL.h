
template <class T>
class priorityQueueLL
{
private:
	class node
	{
	public:
		//put what you need here..
		T data;
		node* next;
		node* back;
		//int priority;
		

		node(T d){
			data = d;
			next = nullptr;
			back = nullptr
		}
	};

	//add what you wish here
		node* top;
public:

	priorityQueueLL() {
		top = nullptr;
	}

	~priorityQueueLL() {
		
	}

	//return true if empty, false if not
	bool empty() {
		if (top==nullptrs){
			return true;
		}
		else{
			return false;
		}
	}

	//add item
	void insert(T x) {
		node* add = new node();
		add->data = x;
		add->next = nullptr;
		if(top == nullptr){
			top = add;
			add->back = nullptr;
		}
		else{
			add->next = top;
			top->back = add;
			top = add;
		}
	}

	//remove and return smallest item
	T extractMin() {
		node* curr = top;
		node* min = top;
		node* temp = top;
		while curr != nullptr {
			if (curr->data < min->data){
				min = curr->data;
			}
			curr = curr->next;
		}
		if(min->next != nullptr){
			temp->next = min->next
		}
		delete temp;
		return min;
	}

};