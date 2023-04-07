#include<iostream>
#include<string>

#ifndef unrolled_h_
#define unrolled_h_
const int NUM_ELEMENTS_PER_NODE = 6;


template <class T> class UnrolledLL;										// Forward declarations for all functions to be properly read
template <class T> class Node;
template <class T> class list_iterator;


//----------------NODE - DECLARATION----------------
template <class T>
class Node {
	public:
		// CONSTRUCTORS
		Node();
		Node(const T& input);		

		// Node() : arraySize_(0), next_(NULL), prev_(NULL) {}										
		// Node(const T& input) : array_[0](input), arraySize_(1),					// How to do this properly??? Would like to know
		// 						  next_(NULL), prev_(NULL) {}


		// REPRESENTATION VARIABLES - all publicly accessible
		T array_[NUM_ELEMENTS_PER_NODE];
		int arraySize_;
		Node<T>* next_;
		Node<T>* prev_;
};

//----------------NODE - IMPLEMENTATION----------------
//Node Default Constructor - If no value is given, simply
//							 create new node with no value
template <class T>
Node<T>::Node() {
	arraySize_ = 0;
	next_ = NULL;
	prev_ = NULL;
}

//Node Constructor w/ Params - If value given, place value
//							   in 1st index of node's array
//							   and increase size - same ptrs
template <class T>
Node<T>::Node(const T& input) {
	array_[0] = input;
	arraySize_ = 1;
	next_ = NULL;
	prev_ = NULL;
}
//----------------------------------------------------------------------------------------------------------------------------------------
//----------------ITERATOR - DECLARATION----------------
template <class T>
class list_iterator {
	public:
		// CONSTRUCTOR:
		list_iterator(Node<T>* p=NULL) : ptr_(p), offset(0) {}


		// ACCESSOR:
		T& operator*() {return ptr_->array_[offset]; }						// operator*() - deref. operator gives access to vals at ptr_
		int getOffset() {return offset;}


		// MODIFIERS:
		list_iterator<T> operator++(int);


		// OTHERS:
		bool operator==(const list_iterator<T>& other) const;
		bool operator!=(const list_iterator<T>& other) const;

		friend class UnrolledLL<T>;


	private:
		Node<T>* ptr_;
		int offset;
};


//----------------ITERATOR - IMPLEMENTATION----------------
//operator++(int) - increases position of iterator by one
//					spot - is post-increment (e.g., iter++)
template <class T>
list_iterator<T> list_iterator<T>::operator++(int) {
	list_iterator<T> temp(*this);											// Create pointer to itself to be returned
	if (offset==ptr_->arraySize_-1) {										// If at last index of array_...
		ptr_ = ptr_->next_;														// Advance to next node
		offset = 0;																// Reset offest to 0th index of array_
	}
	else {offset+=1;}														// Else, simply increase offset by 1
	return temp;															// Return pointer to node
}

//operator==() - equal-to operator that returns true if the
//				 iterator is pointing to the same place the
//				 inputted "other" iterator is
template <class T>
bool list_iterator<T>::operator==(const list_iterator<T>& other) const {
	return ((ptr_ == other.ptr_) && (offset == other.offset));
}

//operator!=() - not-equal-to operator that returns true if
//				 the iterator is not pointing to the same
//				 place the inputted "other" iterator is
template <class T>
bool list_iterator<T>::operator!=(const list_iterator<T>& other) const {
	return ((ptr_ != other.ptr_) || (offset != other.offset));
}
//----------------------------------------------------------------------------------------------------------------------------------------
//----------------LIST - DECLARATION----------------
template <class T>
class UnrolledLL {
	public:
		// CONSTRUCTORS:
		UnrolledLL() : head_(NULL), tail_(NULL), size_(0) {}				//UnrolledLL() - default constructor
		UnrolledLL(const UnrolledLL<T>& old) {copy_list(old);}				//UnrolledLL(UnrolledLL<T>) - copy constructor to copy list
		UnrolledLL& operator= (const UnrolledLL<T>& old);
		~UnrolledLL() {destroy_list();}										//~UnrolledLL() - destructor that deletes the list

		typedef list_iterator<T> iterator;

		// ACCESSORS:
		iterator begin() {return iterator(head_);}							//begin() - return pointer to head_ node
		iterator end() {return iterator(tail_->next_);}						//end() - return pointer to NULL
		T& front() const;
		T& back() const;

		unsigned int size() {return size_;}									//size() - returns size of list
		void print(std::ostream& os);


		// MODIFIERS:
		void push_front(const T& value);
		void pop_front();
		void push_back(const T& value);
		void pop_back();
		
		iterator insert(list_iterator<T>& itr, const T& value);
		iterator erase(list_iterator<T>& itr);	// Correct declaration?

	private:
		void copy_list(const UnrolledLL<T>& old);
		void destroy_list();

		Node<T>* head_;
		Node<T>* tail_;
		unsigned int size_;
};

//----------------LIST - IMPLEMENTATION----------------
//operator=() - list assignment operator that clears and
//				replaces info fm another list - in the
//				syntax listA = listB means: "listA will
//				become a copy of listB"
template <class T>
UnrolledLL<T>& UnrolledLL<T>::operator=(const UnrolledLL<T>& old) {
  if (&old != this) {														// Check for self-assignment
    destroy_list();																// Completely destroy old list and make it a copy
    copy_list(old);
  }
  return *this;
}

//front() - return the first value of the entire list
template <class T>
T& UnrolledLL<T>::front() const {
	return (head_->array_[0]);
}

//back() - return the last value of the entire list
template <class T>
T& UnrolledLL<T>::back() const {
	return (tail_->array_[tail_->arraySize_-1]);
}

//print() - prints the data stored in each node of the
//			in such a way according to the output - the
//			total size of list is also given
template <class T>
void UnrolledLL<T>::print(std::ostream& os) {
	os<<"UnrolledLL, size: "<<size_<<std::endl;								// Total size given
	Node<T>* temp = head_;													// Node pointer to iterate through nodes
	while (temp != nullptr) {												// While there are nodes to read...
		os<<" node:["<<temp->arraySize_<<"]";									// Node's arraySize_ given
		for (int i=0 ; i<temp->arraySize_ ; ++i) {								// array_ contents printed
			os<<" "<<temp->array_[i];
		}
		os<<std::endl;
		temp = temp->next_;														// When all array_ contents printed, move to next node
	}
}

//push_front() - inserts value at beginning of the
//				 list and sets it as the list's
//				 first value
template <class T>
void UnrolledLL<T>::push_front(const T& value) {
	if (!head_) {															// If head_ is not pointing to anything (no nodes)...
		Node<T>* newNodePtr = new Node<T>(value);								// Create new node with value
		head_ = tail_ = newNodePtr;												// only one node, so head_ and tail_ point to same node
	}
	else if (head_->arraySize_==NUM_ELEMENTS_PER_NODE) {					// Else, if head_ node's array_ is full...
		Node<T>* newNodePtr = new Node<T>(value);								// Create new node before current head_ node with value
		newNodePtr->next_ = head_;												// New node becomes new head_
		head_->prev_ = newNodePtr;
		head_ = newNodePtr;
	}
	else {																	// Else, if head_ node array_ is not full...
		for (int i=head_->arraySize_-1 ; i>=0 ; --i) {							// Rewrite array_ data, shift all index vals right
				head_->array_[i+1] = head_->array_[i];
		}
		head_->array_[0] = value;												//Assign first index as value
		head_->arraySize_++;
	}

	size_++;																// Increase overall size of list
}

//pop_front() - inserts value at end of the list and
//				sets it as the list's last value
template <class T>
void UnrolledLL<T>::pop_front() {
	if (head_->next_ == NULL) {												// If there is only one node...
		if (head_->arraySize_==1) {												// If there is only one value...
			delete head_;															// Delete entire node
			head_ = tail_ = NULL;													// head_ and tail_ point to NULL
		}
		else {																	// Else, if there are multiple values...
			for (int i=0 ; i<head_->arraySize_-1 ; ++i) {							// Rewrite array_ data, shift all index vals left
				head_->array_[i] = head_->array_[i+1];
			}
	    	head_->arraySize_--;
		}
	}
	else if (head_->arraySize_==1) {										// Else, if multiple nodes and head_ node has one value...
		head_ = head_->next_;													// Move head_ pointer to next node
		delete head_->prev_;													// Delete old head_ node
		head_->prev_ = NULL;
	}
	else {																	// Else, if multiple nodes and head_ node has more values...
		for (int i=0 ; i<head_->arraySize_-1 ; ++i) {							// Rewrite array_ data, shift all index vals left
				head_->array_[i] = head_->array_[i+1];
		}
	    head_->arraySize_--;
	}

	size_--;																// Decrease oveall size of list
}

//push_back() - removes value at beginning of the list
//				and sets next value as the list's
//				first value
template <class T>
void UnrolledLL<T>::push_back(const T& value) {
	if (!tail_) {															// If tail_ is not pointing to anything (no nodes)...
		Node<T>* newNodePtr = new Node<T>(value);								// Create new node with value
		head_ = tail_ = newNodePtr;												// only one node, so head_ and tail_ point to same node
	}
	else if (tail_->arraySize_==NUM_ELEMENTS_PER_NODE) {					// Else, if tail_ node's array_ is full...
		Node<T>* newNodePtr = new Node<T>(value);								// Create new node after current tail_ node with value
		newNodePtr->prev_ = tail_;												// New node becomes new tail_
		tail_->next_ = newNodePtr;
		tail_ = newNodePtr;
	}
	else {																	// Else, if tail_ node array_ is not full...
		tail_->array_[tail_->arraySize_] = value;							// Add value to next empty index of array_
		tail_->arraySize_++;
	}
	
	size_++;																// Increase overall size of list
}

//pop_back() - removes value at end of the list and
//			   sets previous value as the list's
//			   last value
template <class T>
void UnrolledLL<T>::pop_back() {
	if (tail_->prev_ == NULL) {												// If there is only one node...
    	if (tail_->arraySize_==1) {												// If there is only one value...
	    	delete tail_;															// Delete entire node
	    	head_ = tail_ = NULL;													// head_ and tail_ point to NULL
	    }
	    else {																	// Else, if there are multiple values...
	    	// tail_->array_[tail_->arraySize_] = NULL;								// Set last index to NULL?
	    	tail_->arraySize_--;
	    }
	}
	else if (tail_->arraySize_==1) {										// Else, if multiple nodes and tail_ node has one value...
		tail_ = tail_->prev_;													// Move tail_ pointer to prev node
		delete tail_->next_;													// Delete old tail_ node
		tail_->next_ = NULL;
	}
	else {																	// Else, if multiple nodes and tail_ node has more values...
		// tail_->array_[tail_->arraySize_] = NULL;								// Set last index to NULL?
		tail_->arraySize_--;
	}
	
	size_--;																// Decrease oveall size of list
}

//
//insert() - inserts inputted value into list at
//			 inputted iterator and adjusts adjacent
//			 values accordingly
template <class T>
typename UnrolledLL<T>::iterator
UnrolledLL<T>::insert(list_iterator<T>& itr, const T& value) {
	if (itr.ptr_->arraySize_==NUM_ELEMENTS_PER_NODE) {						// If node the itr is inserting in is full...
		Node<T>* newNodePtr = new Node<T>();									// Create new empty node
		 int j = 0;
		for (int i=itr.offset ; i<NUM_ELEMENTS_PER_NODE ; ++i) {				// Loop through all elems.
			newNodePtr->array_[j] = itr.ptr_->array_[i];							// All values from index onward placed in next node
			++j;
		}
		newNodePtr->arraySize_ = j;												// Set new node's arraySize_
		itr.ptr_->array_[itr.offset] = value;									// Add value to current node
		itr.ptr_->arraySize_ = itr.offset+1;									// Reset curent node's arraySize_
		newNodePtr->next_ = itr.ptr_->next_;									// Reassign pointers to fit node into list
		newNodePtr->prev_ = itr.ptr_;
		if (itr.ptr_ == tail_) {tail_ = newNodePtr;}							// If the node was the tail_ make new node the tail
		else {newNodePtr->next_->prev_ = newNodePtr;}
		itr.ptr_->next_ = newNodePtr;
		size_++;
		return iterator(itr);
	}
	else {																	// Else if node not full...
		for (int i=itr.ptr_->arraySize_-1 ; i>=itr.offset ; --i) {				// Rewrite array_ data, shift index vals right
			itr.ptr_->array_[i+1] = itr.ptr_->array_[i];
		}
		itr.ptr_->array_[itr.offset] = value;									//Assign first index as value
		itr.ptr_->arraySize_++;
		size_++;
		return iterator(itr);
	}
	return itr;
}
//

//erase() - deletes the value to which the inputted
//			iterator is pointing from the list and
//			adjusts adjacent values accordingly
template <class T>
typename UnrolledLL<T>::iterator
UnrolledLL<T>::erase(list_iterator<T>& itr) {
	iterator after(itr.ptr_->next_);										// In case node pointer needs to advance, use "after"
	if (itr.ptr_->arraySize_==1) {											// If node has one element...
		//std::cout<<"node has 1 elem"<<std::endl;
		if (itr.ptr_==head_ && itr.ptr_==tail_) {								// If there is only one node...
			delete head_;															// Delete entire node
			head_ = tail_ = NULL;													// head_ and tail_ point to NULL
			size_--;
			return NULL;
		}
		else if (itr.ptr_==head_) {												// Else if single-element node is head_...
			head_ = head_->next_;													// Move head_ pointer to next node
			delete head_->prev_;													// Delete old head_ node
			head_->prev_ = NULL;
			size_--;
			return head_;
		}
		else if (itr.ptr_==tail_) {												// Else if single-element node is tail_...
			tail_ = tail_->prev_;													// Move tail_ pointer to prev node
			delete tail_->next_;													// Delete old tail_ node
			tail_->next_ = NULL;
			size_--;
			return NULL;
		}
		else {																	// Else if single-element node is in the middle...
			Node<T>* before = itr.ptr_->prev_;										// Add pointer to node before itr
			itr.ptr_ = itr.ptr_->next_;												// Move itr pointer to next node
			delete itr.ptr_->prev_;													// Delete that node
			before->next_ = itr.ptr_;												// Relink nodes
			itr.ptr_->prev_ = before;
			size_--;
			return itr;
		}
	}
	else if (itr.ptr_->arraySize_>1) {										// If node has many elements...
		if (itr.getOffset()==itr.ptr_->arraySize_-1) {							// If at the last index of a node...
			itr.ptr_->arraySize_--;													// Decrease node's arraySize_
			itr.offset = 0;
			size_--;
			return after;															// Return "after" pointer
		}
		else if (itr.getOffset()<itr.ptr_->arraySize_) {						// Else if at any other lower index...
			for (int i=itr.getOffset() ; i<itr.ptr_->arraySize_-1 ; ++i) {			// Loop through array_ from offest index to the end
				itr.ptr_->array_[i] = itr.ptr_->array_[i+1];							// Shift values to the left
			}
			itr.ptr_->arraySize_--;
			size_--;
			return itr;
		}
	}
	return itr;
}

//copy_list() - remake the list to be a copy of the list
//				in the params - for example, in the syntax
//				listA.copy_list(listB) means: "listA will
//				become a copy of listB"
template <class T>
void UnrolledLL<T>::copy_list(const UnrolledLL<T>& copyFrom) {
	this->destroy_list();													// As a catch-all, delete original list and remake it as copy
	
	size_ = copyFrom.size_;													// Copy copyFrom's size_ into size_
	if (size_ == 0) {														// If copyFrom list was empty, declare new empty node
		head_ = tail_ = new Node<T>();
		return;
	}
	else {																	// Else if not empty...
		head_ = new Node<T>();													// Head node created
		head_->arraySize_ = copyFrom.head_->arraySize_;							// Copy copyFrom's arraySize_ into arraySize_
		for (int i=0 ; i<head_->arraySize_ ; ++i) {								// Copy all copyFrom array_ values into array_
			head_->array_[i] = copyFrom.head_->array_[i];
		}
		tail_ = head_;															// tail_ points to last node created while copying vals
		Node<T>* cFNext = copyFrom.head_->next_;								// cFNext points to next node to be copied in the old list
		while (cFNext) {
			tail_->next_ = new Node<T>();											// Create new node as new list's next_
			tail_->next_->arraySize_ = cFNext->arraySize_;							// Copy cFNext's arraySize_ into arraySize_
			for (int i=0 ; i<tail_->next_->arraySize_ ; ++i) {						// Copy all cFNext's array_ values into array_
				tail_->next_->array_[i] = cFNext->array_[i];
			}
			tail_->next_->prev_ = tail_;											// New node's prev_ will points to current tail_ node
			tail_ = tail_->next_;													// New node becomes new tail_ node
			cFNext = cFNext->next_;													// Advance cFNext to next node to copy from
		}
	}
}

//destroy_list() - Delete each node from the list
//				   entirely - since the list should be
//				   completely deleted, there is no need
//				   to delete individual vals from
//				   arrays
template <class T>
void UnrolledLL<T>::destroy_list() {
	if (size_==0) {return;}													// If list is already empty, simply return
	while (head_->next_!=NULL) {											// While the head is pointing to a next node...
		head_ = head_->next_;													// head_ ptr moves to next node
		delete head_->prev_;													// Current head_'s prev (that old node) is deleted
		head_->prev_ = NULL;													// Current head_'s prev points to NULL
	}
	delete head_;															// When only one node left, delete node and reset all values
	head_ = tail_ = NULL;
	size_ = 0;
}


#endif