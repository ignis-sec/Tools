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
		LinkList::append()
			0:list was empty, added to front
			1:added to tail

		LinkList::CreateNode()
			ptr to the new node(should be checked if null)
		
		DoublyLinkList::append()
		0:list was empty, added to front
		1:added to tail
		





*/










typedef class node* position;
typedef class node2way* position2w;

class node{
	//
public:
	virtual void set_node_values();					//empty and should be overridden in inherited class
	position next=NULL;								//example set_node_values(int a, char b){c=a; d=b;}
};

class node2way : public node {
	//
public:
	position2w next = NULL;
	position2w previous=NULL;
};

//LinkList class decleration
template <class T_NodeType>
class LinkList {
public:
	position get_head(){return head;};
	position get_tail(){return tail;};
	unsigned int get_size(){return size;};
	bool is_empty();
	virtual int append(position newNodePtr);			//append to the end of LinkList"
	T_NodeType* LinkList<T_NodeType>::create_node();		//create a new node 
	virtual void clear();
	virtual void print();
private:
	position head=NULL;
	position tail=NULL;
	unsigned int size = 0;

};

bool LinkList<class T_NodeType>::is_empty() {
	if (get_size()) return false;
	else return true;
}

int LinkList<class T_NodeType>::append(position newNodePtr) {
	if (is_empty())
	{
		head = newNodePtr;
		tail = newNodePtr;
		size++;
		return 0;
	}
	tail->next = newNodePtr;
	tail = newNodePtr;
	size++;
	return 1;
	
}

template <class T_NodeType>
T_NodeType* LinkList<T_NodeType>::create_node()					//user should check if enough memory is available (if return is nullptr)
{
	T_NodeType *newNode;
	newNode = (T_NodeType*)malloc(sizeof(T_NodeType));
	return newNode;
}

void LinkList<class T_NodeType>::clear()
{
	position previous = head, cur = head->next;
	while (cur != NULL)											//traverse the list and free previous element each step
	{
		free(previous);
		previous = cur;
		cur = cur->next;
	}
	free(previous);												//free last element		
	head = tail = NULL;											//remove dangling pointers
	size = 0;
	return;
}

void LinkList<class T_NodeType>::print()
{
	unsigned int i = 1;
	position cur = head;
	while (cur != NULL)
	{
		std::cout << i << ". " /* << YOUR VARIABLE HERE << */ << std::endl;
	}
	return;
}


/////////////////////////////////////////////////
//derieved class

class DoublyLinkedList : private LinkList<T_NodeType>
{
public:
	virtual int append(position2w newNodePtr);			//append to the end of LinkList"
	virtual void clear();
private:
	position2w head = NULL;
	position2w tail = NULL;
	unsigned int size = 0;

};

int DoublyLinkedList::append(position2w newNodePtr) {
	if (is_empty())
	{
		head = newNodePtr;
		tail = newNodePtr;
		size++;
		return 0;
	}
	tail->next = newNodePtr;									//tie both next and previous
	newNodePtr->previous = tail;
	tail = newNodePtr;
	size++;
	return 1;

}

void DoublyLinkedList::clear()
{
	position2w cur = head->next;
	while (cur != NULL)											//traverse the list and free previous element each step
	{
		free(cur->previous);
		cur = cur->next;
	}	
	head = tail = NULL;											//remove dangling pointers
	return;
}


/////////////////////////////////////////////////
//derieved class
class CircularLinkedList: public LinkList<T_NodeType> {
public:
	unsigned int get_size() { return size; };
	virtual int append(position newNodePtr);			//append to the end of LinkList
	virtual void print();
private:
	position head = NULL;
	unsigned int size = 0;

};

int CircularLinkedList::append(position newNodePtr) {
	if (is_empty())
	{
		head = newNodePtr;
		newNodePtr->next = newNodePtr;				//loop list around
		size++;
		return 0;
	}
	position temp = head->next;						//insert after the header and tie back
	head->next = newNodePtr;
	newNodePtr->next = temp;
	size++;
	return 1;

}

void CircularLinkedList::print()
{
	bool bFirst = true;
	unsigned int i = 1;
	position cur = head;
	while (cur != head && !bFirst)
	{
		std::cout << i << ". " /* << YOUR VARIABLE HERE << */ << std::endl;
		if(bFirst) bFirst = false;
	}
	return;
}


/////////////////////////////////////////////////
//derieved class
class CircularDoublyLinkedList : public CircularLinkedList {
public:
	unsigned int get_size() { return size; };
	virtual int append(position2w newNodePtr);			//append to the end of LinkList
	virtual void print();
private:
	position2w head = NULL;
	unsigned int size = 0;

};

int CircularDoublyLinkedList::append(position2w newNodePtr) {
	if (is_empty())
	{
		head = newNodePtr;
		newNodePtr->next = newNodePtr;				//loop list around
		newNodePtr->previous = newNodePtr;
		size++;
		return 0;
	}
	position2w temp = head->next;						//insert after the header and tie back
	head->next = newNodePtr;
	newNodePtr->previous = head;
	newNodePtr->next = temp;
	temp->previous = newNodePtr;
	size++;
	return 1;

}

void CircularDoublyLinkedList::print()
{
	bool bFirst = true;
	unsigned int i = 1;
	position2w cur = head;
	while (cur != head && !bFirst)
	{
		std::cout << i << ". " /* << YOUR VARIABLE HERE << */ << std::endl;
		if (bFirst) bFirst = false;
	}
	return;
}