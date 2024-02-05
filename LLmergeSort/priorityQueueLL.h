
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
		

		node(){
			//data = d;
			next = nullptr;
			back = nullptr;
		}
	};

	//add what you wish here
		node* top;
public:

	priorityQueueLL() {
		top = nullptr;
	}

	~priorityQueueLL() {
		node *temp;
        while (top != nullptr)
        {
            temp = top;
            top = top->next;
            delete temp;
        }
	}

	//return true if empty, false if not
	bool empty() {
		if (top==nullptr){
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
		if(top == nullptr || x > top->data){
			if(top != nullptr){
				top->back = add;
				add->next = top;
				top = add;
			}
			else{
			top = add;
			add->back = nullptr;
			add->next = nullptr;	
			}
			
		}
		else{
			node* curr = top;
			while(curr->next != nullptr && x < curr->next->data){
				curr = curr->next;
			}
			add->next = curr->next;
			if(curr->next != nullptr){
				curr->next->back = add;	
			}
			add->back = curr;
			curr->next = add;
		}
	}

	//remove and return smallest item
	T extractMin() {
		node* curr = top;
		node* rem = top;
		T val = top->data;
		if(top->next == nullptr){
			rem = top;
			top = nullptr;
			delete rem;
			return val;
		}
		while(curr->next != nullptr){
			curr = curr->next;
		}
		curr->back->next = nullptr;
		rem = curr;
		val = curr->data;
		delete rem;
		return val;
	}

};