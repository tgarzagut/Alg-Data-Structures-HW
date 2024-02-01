
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
		//int priority;
		

		node(T d){
			data = d;
			next = nulptr;
		}
	};

	//add what you wish here
		node* top;
		node* bottom;	
public:

	priorityQueueLL() {
		top = bottom = nullptr;
	}

	~priorityQueueLL()
	{}

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

	}

	//remove and return smallest item
	T extractMin() {
		node* curr = top;
		int min = curr->data;
		while curr != nullptr {
			
		}
	}

};