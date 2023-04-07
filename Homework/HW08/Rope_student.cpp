/*
Write your Rope implementation in this file. 
You do not have to keep any of the code that is already in this file.
Functions that are required that you have not implemented have an assert 0
meaning they will always crash. This should help you make sure you implement
everything.
*/

#include <cassert>
#include "Rope.h"

//Should advance to the next Node using in-order traversal
//It can point at any Node, not just leaves
rope_iterator& rope_iterator::operator++(){
	// If node has right node, enter it and keep entering
	//  all left nodes until there is no left to enter
	if (ptr_->right != NULL) {
		ptr_ = ptr_->right;
		while (ptr_->left != NULL) {
			ptr_ = ptr_->left;
		}
	}
	else {
		// Keep going up as long as I am my parent's right child
		while (ptr_->parent && ptr_->parent->right == ptr_) {
			ptr_ = ptr_->parent;
		}
		// Up once more - will become NULL
		// when at the end of the rope
		ptr_ = ptr_->parent;
	}

	return *this; // return self since it's been changed
}

//Point to the first Node for in-order traversal
rope_iterator Rope::begin() const{
	// If empty tree, return NULL
	if (root==NULL) {return end();}

	// Start ptr at root_ node
	// and continue to leftmost side
	Node* p = root; 
	while (p->left!=NULL) {p = p->left;}

	// return ptr as usable itr
	return rope_iterator(p);
}

Rope::Rope(){
	root = NULL;
	size_ = 0;
}

//Should make the root = p and adjust any member variables
//This should not make a copy of the rope with root at p,
//it should just "steal" the Node*
Rope::Rope(Node* p){
	root = p;
	size_ = size_from_root(p);
}

Rope::~Rope(){
	destroy(root);
	this->root = NULL;
	this->size_ = 0;
}

Rope::Rope(const Rope& r){
	this->root = copy(root, r.root);
	this->size_ = r.size_;
}

Rope& Rope::operator= (const Rope& r){
	// if r not already equal to this...
	if (&r!=this) {
		// delete all info from 
		destroy(root);
		this->root = copy(root, r.root);
		this->size_ = r.size_;
	}
	return *this;
}

//MUST BE ITERATIVE
//Get a single character at index i
bool Rope::index(int i, char& c) const{
	if (i<0 || i>size_) {return false;}

	// Start from root
	Node* ptr = this->root;

	// If no tree, return false
	if (!ptr) {return false;}

	// Until ptr reaches a leaf...
	while (!is_leaf(ptr)) {
		// If index < node's weight, move left
		if (i<ptr->weight) {
			ptr = ptr->left;
		}
		// Else, edit index and move right
		else {
			i -= ptr->weight;
			ptr = ptr->right;
		}
	}
	// Once leaf is reached,
	// get index normally
	c = ptr->value[i];
	return true;
}

//Add the other rope (r)'s string to the end of my string
void Rope::concat(const Rope& r){
	// Create copy of r to be added,
	// not r itself
	Node* rCopy = copy(rCopy, r.root);

	Node* newRoot = new Node;
	// Have new root point to trees
	newRoot->left = root;
	newRoot->right = rCopy;
	// New children should point back
	newRoot->left->parent = newRoot;
	newRoot->right->parent = newRoot;
	// Also weight, not value (no need)
	newRoot->weight = size_from_root(root);

	// Actual rope object should change 
	root = newRoot;
	size_ = size_from_root(root);
}

//Get a substring from index i to index j.
//Includes both the characters at index i and at index j.
//String can be one character if i and j match
//Returns true if a string was returned, and false otherwise
//Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string& s) const{
	s.clear();

	Node* startLeaf = get_leaf(i);
	Node* endLeaf = get_leaf(j);

	// If start and end are same leaf,
	// only print range in startLeaf
	if (startLeaf==endLeaf) {
		for (int k=i ; k<=j ; ++k) {
			s+=startLeaf->value[k];
		}
	}
	// Else if they are differnt nodes...
	else {
		// Add all needed chars from
		// startLeaf to s
		for (int k=i ; k<startLeaf->weight ; ++k) {
			s+=startLeaf->value[k];
		}
		//Looks weird, but works: declare itr to be used
		// within class implementation
		// (reminder: not structured like STL itrs)
		rope_iterator itr(startLeaf);
		// Immdeiately advance to avoid duplicates
		itr++;
		// Visit all leaves until endLeaf reached,
		// adding all values to s
		while (itr!=endLeaf) {
			s+=(*itr);
			itr++;
		}
		// Add all needed chars from
		// endLeaf to s
		for (int k=0 ; k<=j ; ++k) {
			s+=endLeaf->value[k];
		}
	}
	if (s.size()<=0) {return false;}
	else {return true;}
}

//The first i characters should stay in the current rope, while a new
//Rope (rhs) should contain the remaining size_-i characters.
//A valid split should always result in two ropes of non-zero length.
//If the split would not be valid, this rope should not be changed,
//and the rhs rope should be an empty rope.
//The return value should be this rope (the "left") part of the string
//This function should move the nodes to the rhs instead of making new copies.
Rope& Rope::split(int i, Rope& rhs){
	int iCopy = i;
	Node* tmpRoot = get_leaf(iCopy);
	// If index at center/end of value in leaf, create
	// children nodes and place correct values
	if (iCopy!=0) {
		// Creation of left node
		tmpRoot->left = new Node;
		tmpRoot->left->parent = tmpRoot;
		tmpRoot->left->weight = tmpRoot->left->value.size();
		std::string tmpStr = "";
		for (int k=0 ; k<iCopy ; ++k) {tmpStr+=tmpRoot->value[k];}
		tmpRoot->left->value = tmpStr;

		// Creation of right node
		tmpRoot->right = new Node;
		tmpRoot->right->parent = tmpRoot;
		tmpRoot->right->weight = tmpRoot->right->value.size();
		tmpStr.clear();
		for (int k=iCopy ; k<tmpRoot->weight ; ++k) {tmpStr+=tmpRoot->value[k];}
		tmpRoot->right->value = tmpStr;

		// Change values in old leaf
		tmpRoot->value.clear();
		tmpRoot->weight = tmpRoot->left->weight;
	}
	Node* nodePtr = get_leaf(i); nodePtr = nodePtr->parent;
	//std::cout<<"nodePtr->right->value: "<<nodePtr->right->value<<std::endl;

	Rope leftConcat, rightConcat;
	Node* prevNode = NULL;

	// Keep going up until past root...
	while (nodePtr!=NULL) {
		// If current node has right and is not right child of parent...
		if ((nodePtr->right) && nodePtr->right!=prevNode) {
			// If leftConcat uninitialized (1st iteration),
			// set this branch-off as leftConcat
			if (leftConcat.root==NULL) {
				Rope tmpRope(nodePtr->right);
				leftConcat = tmpRope;
			}
			// Else if leftConcat initialized...
			else {
				// Set this branch-off as rightConcat
				Rope tmpRope(nodePtr->right);
				rightConcat = tmpRope;

				//char c; for (int i=0 ; i<leftConcat.size_ ; ++i)
				//{leftConcat.index(i, c); std::cout<<c;}
				//std::cout<<std::endl;
				//for (int i=0 ; i<rightConcat.size_ ; ++i)
				//{rightConcat.index(i, c); std::cout<<c;}
				//std::cout<<std::endl;
				
				// Now both exist - concat to leftConcat
				leftConcat.concat_no_copy(rightConcat);
				
				//for (int i=0 ; i<leftConcat.size_ ; ++i)
				//{leftConcat.index(i, c); std::cout<<c;}
				//std::cout<<std::endl;
			}
			// Cut off right child and resize
			nodePtr->right = NULL;
			size_ = size_from_root(root);
		}
		prevNode = nodePtr;
		nodePtr = nodePtr->parent;
	}
	//std::cout<<"In summary:"<<std::endl;
	//char c; for (int i=0 ; i<size_ ; ++i)
	//{index(i, c); std::cout<<c;}
	//std::cout<<size_<<std::endl;
	//for (int i=0 ; i<leftConcat.size_ ; ++i)
	//{leftConcat.index(i, c); std::cout<<c;}
	//std::cout<<leftConcat.size_<<std::endl;
	//print_strings(std::cout);
	//leftConcat.print_strings(std::cout);
	rhs = leftConcat;
	//std::cout<<"rhs CHANGED - DONE"<<std::endl;

	return *this;
	
}



//
// ADDED FUNCTIONS:

// Using the root node, go through each node
// recursively and see if it is a leaf - if
// so, return size of string held in it
int Rope::size_from_root(Node* p) {
	if (is_leaf(p)) {return p->value.size();}

	int sum = 0;
	if (p->left) {sum+=size_from_root(p->left);}
	if (p->right) {sum+=size_from_root(p->right);}
	
	return sum;
}


// Returns ptr to leaf that holds desired
// index of rope - does exactly what index()
// does except return a specific character
// - const used since dealing w/ const Rope
Node* Rope::get_leaf(int& i) const {
	Node* ptr = this->root;
	while (!is_leaf(ptr)) {
		if (i<ptr->weight) {
			ptr = ptr->left;
		}
		else {
			i -= ptr->weight;
			ptr = ptr->right;
		}
	}

	return ptr;
}


// exactly the same as copy(), but r is not
// passed as const and rather than concat'ing
// a copy of r you instead just concat r
void Rope::concat_no_copy(Rope& r) {
	// Point to r.root since it will be
	// outright changed
	Node* rCopy = r.root;

	Node* newRoot = new Node;
	// Have new root point to trees
	newRoot->left = root;
	newRoot->right = rCopy;
	// New children should point back
	newRoot->left->parent = newRoot;
	newRoot->right->parent = newRoot;
	// Also weight, not value (no need)
	newRoot->weight = size_from_root(root);

	// Actual rope object should change 
	root = newRoot;
	size_ = size_from_root(root);
}


// Copy help function that is called when calling
// the copy constructor and other functions - using
// an old node fromthe original tree and a new node
// and going through all nodes recursively, a new
// tree will be created that has all of its
// information 
Node* Rope::copy(Node* &oldNode, Node* newNode) {
	if (newNode==NULL) {oldNode = NULL;}
	
	else {
		oldNode = new Node;
		oldNode->weight = newNode->weight;
		oldNode->value = newNode->value;
		oldNode->left = copy(oldNode->left, newNode->left);
		oldNode->right = copy(oldNode->right, newNode->right);
		if (oldNode->left) {oldNode->left->parent = oldNode;}
		if (oldNode->right) {oldNode->right->parent = oldNode;}
	}

	return oldNode;
}
// ~~OLD VERSION~~
// Node* Rope::copy(Node* oldNode, Node* oldNodeParent) {
// 	Node* newTree = NULL;
//     if (oldNode!=NULL) {
// 		newTree = new Node();
// 		newTree->weight = oldNode->weight;
// 		newTree->value = oldNode->value;
// 		newTree->parent = oldNodeParent;
// 		newTree->left = copy(oldNode->left, oldNode);
// 		newTree->right = copy(oldNode->right, oldNode);
//     }
//    return newTree;
// }


// Destroy helper function allows destroy
// to be called recursively, deleting each
// node from the bottom upwards
void Rope::destroy(Node* p) {
	if (!p) {return;}

	destroy(p->left);
	destroy(p->right);

	delete p;
}