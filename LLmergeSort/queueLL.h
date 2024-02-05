
template <class T>
class queueLL
{
private:
	class node
	{
	public:
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
	queueLL() {
		top = nullptr;
		bottom = nullptr;
	}
	//O(n)
	~queueLL() {
		node *temp;
        while (top != nullptr)
        {
            temp = top;
            top = top->next;
            delete temp;
        }
	}

	//O(1)
	void enqueue(T x) {
		node* temp = new node();
		temp->data = x;
		temp->next = nullptr;
		if(top == nullptr){
			top = temp;
			temp->back = nullptr;
			bottom = temp;
		}
		else{
			bottom->next = temp;
			temp->back = bottom;
			bottom = temp;
		}
	}

	//O(1)
	T dequeue() {
		node* temp = top;
		T value = top->data;
		top = top->next;
		if (top != nullptr){
			top->back = nullptr;	
		}
		
		delete temp;
		return value;
	}

	//O(1)
	bool empty() {
		if(top==nullptr){
			return true;
		}
		else{
			return false;
		}
	}
	//O(n)
	void decimate(){
		node* wcurr = top;
		while (wcurr != nullptr){
			for(int i = 1; i < 10; i++){
				if(wcurr->next != nullptr){
					wcurr = wcurr->next;	
				}
				else{
					return;
				}
			}
			node* n = wcurr;
			wcurr = wcurr->next;
			if(n->next != nullptr){
				n->back->next = n->next;
				n->next->back = n->back;
			}
			else{
				bottom = n->back;
				bottom->next = nullptr;
				delete n;
				return;
			}
			
			delete n;
		}
	}

};