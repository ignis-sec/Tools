#include <malloc.h>



/*how to use:

//////////FOR LINKED LISTS://////////

only add this to your code:
singly linked list vvv

class mynode:node{
	...
	...your variables
	...
};

doubly linked list vvv

class mynode:node2way{
	...
	...your variables
	...
};

And override the virtual T_NodeType* createNode(); to take node properties as input and set them
*/

/*Returns table:
		linklist::append()
			0:list was empty, added to front
			1:added to tail









*/










typedef class node* position;

class node{
	//
public:
	position next;
};


class node2way : public node {
	//
public:
	position previous;
};

//linklist class decleration
template <class T_NodeType>
class linklist {
public:
	position GetHead(){return head;};
	position GetTail(){return tail;};
	unsigned int GetSize(){return size;};
	bool isEmpty();
	int append(position newNodePtr);		//append to the end of linklist"
	virtual T_NodeType* CreateNode();		//create a new node YOU SHOULD OVERRIDE THIS
private:
	position head;
	position tail;
	unsigned int size = 0;

};


bool linklist<class T_NodeType>::isEmpty() {
	if (GetSize()) return false;
	else return true;
}

int linklist<class T_NodeType>::append(position newNodePtr) {
	if (isEmpty())
	{
		head = newNodePtr;
		tail = newNodePtr;
		return 0;
	}
	tail->next = newNodePtr;
	tail = newNodePtr;
	return 1;
	
}


T_NodeType* linklist<T_NodeType>::CreateNode()
{
	T_NodeType *newNode;
	newNode = (T_NodeType*)malloc(sizeof(T_NodeType));
	return newNode;
}