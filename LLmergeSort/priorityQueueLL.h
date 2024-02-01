
template <class T>
class priorityQueueLL
{
private:
	class node
	{
	public:
		//put what you need here..
		T data;
		//int priority;
		

		node(T d){
			data = d;
			next = nulptr;
		}
	};

	//add what you wish here
		node* next;
public:

	priorityQueueLL() {

	}

	~priorityQueueLL()
	{}

	//return true if empty, false if not
	bool empty() {
		
	}

	//add item
	void insert(T x)
	{}

	//remove and return smallest item
	T extractMin()
	{}

};