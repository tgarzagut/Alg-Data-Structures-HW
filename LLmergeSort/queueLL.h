
template <class T>
class queueLL
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
	queueLL() {
		top = nullptr;
		bottom = nullptr;
	}

	~queueLL() {

	}

	//add item to back of queue
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

	//remove and return first item from queue
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

	bool empty() {
		if(top==nullptr){
			return true;
		}
		else{
			return false;
		}
	}

	//Eliminate every 10th item from list
	//https://en.wikipedia.org/wiki/Decimation_(punishment)
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
				return;
			}
			
			delete n;
		}
	}

	//For the final part of the test program, template this class
	//and add a decimate method.

};