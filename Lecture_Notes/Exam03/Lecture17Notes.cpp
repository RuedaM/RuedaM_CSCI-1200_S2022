//Lecture 17 – Trees, Part I

//PREVIOUS LECTURE(S) REVIEW
/*
- Maps containing more complicated values. Example: index mapping words to the text line numbers on which they appear
- Maps whose keys are class objects. Example: maintaining student records
- Summary discussion of when to use maps
- Lists vs. Graphs vs. Trees
- Intro to Binary Trees, Binary Search Trees, & Balanced Trees
*/


//OVERVIEW
/*
- STL set container class (like STL map, but without the pairs!)
- Implementation of ds_set class using binary search trees
- In-order, pre-order, and post-order traversal
*/


//17.1 Standard Library Sets
/*
- STL SETS are ordered containers storing unique “keys” - an ordering relation on the keys, which defaults to operator<, is necessary - 
   because STL sets are ordered, they are technically not traditional mathematical sets
- Sets are like maps except they have only keys (no associated values) Like maps, the keys are constant: this means you can’t change a key
   while it is in the set. You must remove it, change it, and then reinsert it.
- Access to items in sets is extremely fast! O(log n), just like maps
- Like other containers, sets have the usual constructors as well as the size member function
- This is vry similar to Python sets: all terms are unique and const; STL sets, however, are ordered and Python sets are random
*/


//17.2 Set iterators
/*
- Set iterators, similar to map iterators, are bidirectional: they allow you to step forward (++) and backward (--) through the set
- Sets provide begin() and end() iterators to delimit the bounds of the set
- Set iterators refer to const keys (as opposed to the pairs referred to by map iterators) - for example, the following code outputs all
   strings in the set words:*/
for (set<string>::iterator p = words.begin(); p!= words.end(); ++p) {cout << *p << endl;}


//17.3 Set insert
/*
- There are two different versions of the insert member function:
	- The first version inserts the entry into the set and returns a pair
		- The first component of the returned pair refers to the location in the set containing the entry
		- The second component is true if the entry wasn’t already in the set and therefore was inserted. It is false otherwise:*/
	pair<iterator,bool> set<Key>::insert(const Key& entry);
	/*
	- The second version also inserts the key if it is not already there. The iterator pos is a “hint” as to where to put it
		- This makes the insert faster if the hint is good*/
	iterator set<Key>::insert(iterator pos, const Key& entry);


//17.4 Set erase
/*
- There are three versions of erase:
	- The first erase returns the number of entries removed (either 0 or 1)*/
	size_type set<Key>::erase(const Key& x);
	/*
	- The second and third erase functions are just like the corresponding erase functions for maps.*/
	void set<Key>::erase(iterator p);
	void set<Key>::erase(iterator first, iterator last);
/*
- Note that the erase functions do not return iterators - this is different from the vector and list erase functions
*/


//17.5 Set find
/*
- The find function returns the end iterator if the key is not in the set:*/
const_iterator set<Key>::find(const Key& x) const;


//17.6 Beginning our implementation of ds set: The Tree Node Class
/*
- Here is the class definition for nodes in the tree. We will use this for the tree manipulation code we write:*/
template <class T>
class TreeNode {
	public:
		TreeNode() : left(NULL), right(NULL) {}
		TreeNode(const T& init) : value(init), left(NULL), right(NULL) {}
		
		T value;
		TreeNode* left;
		TreeNode* right;
};
/*
- Note: Sometimes a 3rd pointer — to the parent TreeNode — is added.
*/


//17.7 Exercises
/*
1. Write a templated function to find the smallest value stored in a binary search tree whose root node is pointed to by p:*/
template <class T>
T& find_smallest(const TreeNode<T>& node) {
	assert(p); // make sure p doesn't equal NULL
	while (p->left) {p = p->left;}
	return p->value;

	/*-OR-*/

	assert(p!=NULL);
	/*recursively*/
}

/*
2. Write a function to count the number of odd numbers stored in a binary tree (not necessarily a binary search tree) of integers.
    The function should accept a TreeNode<int> pointer as its sole argument and return an integer. Hint: think recursively!*/
int cout_odds(TreeNode<int>* p) {
	if (!p) {return 0;}

	if (p_.left==NULL && p->right==NULL) {return (p->value % 2);}

	if (p->value % 2) {return (cout_odds(p->left) + cout_odds(p->right) + 1);}

	else {return (cout_odds(p->left) + cout_odds(p->right) + (p->value % 2));}
}


//17.8 ds_set and Binary Search Tree Implementation
/*
- A partial implementation of a set using a binary search tree is in the code attached. We will continue to study this implementation in
   Lab 10 & the next lecture
- The increment+decrement operations for iterators have been omitted from this implementation. Next week in lecture we will discuss a
   couple strategies for adding these operations
- We will use this as the basis both for understanding an initial selection of tree algorithms and for thinking about how standard library
   sets really work
*/


//17.9 ds_set: Class Overview
/*
- There are two auxiliary classes, TreeNode and tree_iterator - all three classes are templated

- The only member variables of the ds_set class are the root and the size (number of tree nodes)
- The tree_iterator class is declared internally, and is effectively a "wrapper" on the TreeNode pointers
	- Note that operator* returns a const reference because the keys can’t change
	- The increment+decrement operators are missing (we’ll fill this in next week in lecture!)
- The main public member functions just call a private (and often recursive) member function (passing the root node) that does all of the
   work

- Because the class stores+manages dynamically allocated memory, a copy constructor, operator=, and destructor must be provided
*/


//17.10 Exercises
/*
1. Provide the implementation of the member function ds_set<T>::begin. This is essentially the problem of finding the node in the tree
    that stores the smallest value:*/
iterator begin() const {
	if (root_==NULL) {return end();} // If empty tree, return end()

	TreeNode<T>* p = root_; // simply return ptr to root_ node...

	while (p->left!=NULL) {p = p->left;} // ...and continue to the left side

	return iterator(p);
}

/*
2. Write a recursive version of the function find():*/
iterator find(const T& key_val, TreeNode<T>* p) {
	if (p==NULL) {return end();}
	else if (p->value==key_val) {return iterator(p);}
	else if (p->value>key_val) {return find(key_val, p->left);}
	else if (p->value<key_val) {return find(key_val, p->right);}
}


//17.11 In-order, Pre-Order, Post-Order Traversal
/*
- One of the fundamental tree operations is “traversing” the nodes in the tree and doing something at each node - the “doing something”
   (which is often just printing the contents of the node) is referred to generically as “visiting” the node

- There are three general orders in which binary trees are traversed: pre-order, in-order and post-order
- In order to explain these, let’s first draw an “exactly balanced” binary search tree with the elements 1-7:
														    _-4-_
														   /     \
														  2       6
													   /   \   /   \
													  1     3 5     7
	- What is the in-order traversal of this tree? Hint: it is monotonically increasing, which is always true for an in-order traversal of
	   a binary search tree!
	1, 2, 3, 4, 5, 6, 7 /// left, myself, right

	- What is the post-order traversal of this tree? Hint, it ends with “4” and the 3rd element printed is “2”.
	1, 3, 2, 5, 7, 6, 4 /// left, right, myself

	- What is the pre-order traversal of this tree? Hint, the last element is the same as the last element of the in-order traversal (but
	   that is not true in general! why not?)
	4, 2, 1, 3, 6, 5, 7 /// myself, left, right
*/



// Partial implementation of binary-tree based set class similar to std::set.
// The iterator increment & decrement operations have been omitted.
#ifndef ds_set_h_
#define ds_set_h_
#include <iostream>
#include <utility>
// -------------------------------------------------------------------

// TREE NODE CLASS
template <class T>
class TreeNode {
	public:
		TreeNode() : left(NULL), right(NULL) {}
		TreeNode(const T& init) : value(init), left(NULL), right(NULL) {}
		
		T value;
		TreeNode* left;
		TreeNode* right;
};

template <class T> class ds_set;

// -------------------------------------------------------------------

// TREE NODE ITERATOR CLASS
template <class T>
class tree_iterator {
	public:
		tree_iterator() : ptr_(NULL) {}
		tree_iterator(TreeNode<T>* p) : ptr_(p) {}
		tree_iterator(const tree_iterator& old) : ptr_(old.ptr_) {}
		~tree_iterator() {}
		

		tree_iterator& operator=(const tree_iterator& old) { ptr_ = old.ptr_; return *this; }
		// operator* gives constant access to the value at the pointer
		const T& operator*() const { return ptr_->value; }
		
		// comparions operators are straightforward
		bool operator==(const tree_iterator& r) { return ptr_ == r.ptr_; }
		bool operator!=(const tree_iterator& r) { return ptr_ != r.ptr_; }
		// increment & decrement will be discussed in Lecture 18 and Lab 11
		/*...*/

	private:
		// representation
		TreeNode<T>* ptr_;
};
// -------------------------------------------------------------------

// DS SET CLASS
template <class T>
class ds_set {
	public:
		ds_set() : root_(NULL), size_(0) {}
		ds_set(const ds_set<T>& old) : size_(old.size_) {
			root_ = this->copy_tree(old.root_);
		}
		~ds_set() { this->destroy_tree(root_); root_ = NULL; }
		
		ds_set& operator=(const ds_set<T>& old) {
			if (&old != this) {
				this->destroy_tree(root_);
				root_ = this->copy_tree(old.root_);
				size_ = old.size_;
			}
			return *this;
		}

		typedef tree_iterator<T> iterator;
		
		int size() const { return size_; }
		bool operator==(const ds_set<T>& old) const { return (old.root_ == this->root_); }

		// FIND, INSERT & ERASE
		iterator find(const T& key_value) { return find(key_value, root_); }
		std::pair< iterator, bool > insert(T const& key_value) { return insert(key_value, root_); }
		int erase(T const& key_value) { return erase(key_value, root_); }

		// OUTPUT & PRINTING
		friend std::ostream& operator<< (std::ostream& ostr, const ds_set<T>& s) {
			s.print_in_order(ostr, s.root_);
			return ostr;
		}
		void print_as_sideways_tree(std::ostream& ostr) const { print_as_sideways_tree(ostr, root_, 0); }
		
		// ITERATORS
		iterator begin() const {/*...*/} // Implemented in Lecture 17
		iterator end() const { return iterator(NULL); }

	private:
		// REPRESENTATION
		TreeNode<T>* root_;
		int size_;

		// PRIVATE HELPER FUNCTIONS
		TreeNode<T>* copy_tree(TreeNode<T>* old_root) { /* Implemented in Lab 9 */ }
		void destroy_tree(TreeNode<T>* p) { /* Implemented in Lecture 18 */ }
		
		iterator find(const T& key_value, TreeNode<T>* p) {/*...*/} // Implemented in Lecture 17
		std::pair<iterator,bool> insert(const T& key_value, TreeNode<T>*& p) { /* Discussed in Lecture 18 */ }
		int erase(T const& key_value, TreeNode<T>* &p) { /* Implemented in Lecture 19 */ }
		
		void print_in_order(std::ostream& ostr, const TreeNode<T>* p) const {
			// Discussed in Lecture 18
			if (p) {
				print_in_order(ostr, p->left);
				ostr << p->value << "\n";
				print_in_order(ostr, p->right);
			}
		}
		void print_as_sideways_tree(std::ostream& ostr, const TreeNode<T>* p, int depth) const {/*...*/} /* Discussed in Lecture 17 */

};

#endif