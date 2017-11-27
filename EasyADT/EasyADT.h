


/*how to use:

//////////FOR LINKED LISTS://////////

only add this to your code:
singly linked list vvv

struct mynode:node{
	...
	...your variables
	...
};

doubly linked list vvv

struct mynode:node2way{
	...
	...your variables
	...
};

*/


typedef node* position;

struct node
{
	//... your variables here(no need for pointers)...
	position next;
};


struct node2way : public node {
	//... your variables here(no need for pointers)...
	position previous;
};


class linklist {
public:
	position GetHead() { return head; };
	position GetTail() { return tail; };
	unsigned int GetSize() { return size; };
	
private:
	position head;
	position tail;
	unsigned int size = 0;
};

bool isListEmpty(linklist L) {
	if (L.GetSize()) return true;
	else return false;
}


