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

//derieved class
template <class T_NodeType>
class DoublyLinkedList : private LinkList<T_NodeType>
{
	virtual int append(position newNodePtr);			//append to the end of LinkList"
	T_NodeType* LinkList<T_NodeType>::create_node();		//create a new node 
	virtual void clear();
	virtual void print();
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


int DoublyLinkedList<class T_NodeType>::append(position newNodePtr) {
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
