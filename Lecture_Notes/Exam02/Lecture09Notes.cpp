//Lecture 9 - Iterators & STL Lists


//PREVIOUS LECTURE(S) REVIEW
/*
- Algorithm Analysis, Formal Definition of Order Notation
- Simple recursion, Visualization of recursion, Iteration vs. Recursion, “Rules” for writing recursive functions
- Lots of examples!
*/


//OVERVIEW
/*
- Another vector operation: pop back
- Erasing items from vectors is inefficient!
- Iterators and iterator operations
- STL lists are a different sequential container class
- Returning references to member variables from member functions
- Vec iterator implementation
*/


//9.1 Review: Constructors, Assignment Operator, and Destructor
Foo f1;				// assignment operator
Foo* f2; 			// copy constructor
f2 = new Foo(f1); // none of the above
f1 = *f2; 			// default constructor
delete f2; 			// destructor



//9.2 Another STL vector operation: pop back
/*
- We have seen how .push_back() adds a value to the end of a vector, increasing the size of the vector by 1. There is a corresponding
   function called .pop_back() which removes the last item in a vector, reducing the size by 1 - essentially the opposite of .push_back()
- There are also vector functions called .front() and .back() which denote (and thereby provide access to) the first + last item in the
   vector, allowing them to be changed - for example:
*/
vector<int> a(5,1);	// a has 5 values, all 1
a.pop_back();			// a now has 4 values
a.front() = 3;			// equivalent to the statement, a[0] = 3;
a.back() = -2;			// equivalent to the statement, a[a.size()-1] = -2


//9.3 Motivating Example: Course Enrollment and Waiting List
/*
classlist_ORIGINAL.cpp
- This program maintains the class list and the waiting list for a single course - the program is structured to handle interactive input,
   and error checking ensures that the input is valid
- Vectors store the enrolled students and the waiting students - the main work is done in the two functions enroll_student() and
   remove_student()
- The invariant on the loop in the main function determines how these functions must behave
*/


//9.4 Exercises
/*
1. Write erase_from_vector(). This function removes the value at index location i from a vector of strings. The size of the vector should
	be reduced by one when the function is finished:
*/
// Remove the value at index location i from a vector of strings
//	The size of the vector should be reduced by one when the function is finished
void erase_from_vector(unsigned int i, vector<string>& v) {
	if (v.empty()) {return;}

	for (unsigned int j=i ; j<(v.size()-1) ; ++j) {
		v[i] = v[i+1]
	}
	v.pop_back();
}
/*
2. Give an order notation estimate of the average cost of erase_from_vector, pop_back(), and push_back()
ANSWER:
erase_from_vector = O(n)
pop_back() = O(1)
push_back() = O(1)
*/


//9.5 What To Do About the Expense of Erasing From a Vector?
/*
- When items are continually being inserted and removed, vectors are not a good choice for the container
- Instead, we need a different sequential container, called a LIST
	- This has a “linked” structure that makes the cost of erasing independent of the size
- We will move toward a list-based implementation of the program in two steps:
	1. Rewriting our classlist vec.cpp code in terms of iterator operations
	2. Replacing vectors with lists
*/


//9.6 Iterators
/*
- Here’s the definition (from Koenig & Moo). An ITERATOR:
	- identifies a container and a specific element stored in the container,
	- lets us examine (and change (except for const iterators)) the value stored at that element of the container,
	- provides operations for moving (the iterators) between elements in the container, and
	- restricts the available operations in ways that correspond to what the container can handle efficiently
- As we will see, iterators for different container classes have many operations in common - this often makes the switch between
   containers fairly straightforward from the programer’s viewpoint
- Iterators in many ways are generalizations of pointers: many operators/operations defined for pointers are also defined for iterators - 
   you should use this to guide your initial understanding and use of iterators
*/


//9.7 Iterator Declarations and Operations
/*
- Iterator types are declared by the CONTAINER CLASS. For example:*/
vector<string>::iterator p;
vector<string>::const_iterator q;
/*
   ...defines two (uninitialized) iterator variables
- The DEREFERENCE OPERATOR (*) is used to access the value stored at an element of the container - the code:*/
p = enrolled.begin();
*p = "012312";
/*
   ...changes the first entry in the vector named enrolled
- The dereference operator is combined with dot-operator for accessing the member variables and member functions of elements stored in
   containers - here’s an example using the Student class and students vector from Lecture 4:*/
vector<Student>::iterator i = students.begin();
(*i).compute_averages(0.45);
/*
   ...where i is a Student obj. with unique variables+functions, one of them being compute_averages()
   Note:
	- This operation would be illegal if i had been defined as a const iterator because compute_averages() is a non-const member function
	- The parentheses on the *i are required (because of operator precedence)
- There is a “syntactic sugar” for the combination of the dereference operator and the dot-operator, which is exactly equivalent:*/
vector<Student>::iterator i = students.begin();
i->compute_averages(0.45);
/*
- Just like pointers, iterators can be incremented+decremented using the ++ and -- operators to move to the next or previous element of
   any container
- Iterators can be compared using the == and != operators
- Iterators can be assigned, just like any other variable
- Vector iterators have several additional operations:
	- Integer values may be added to them or subtracted from them. This leads to statements like:*/
	enrolled.erase(enrolled.begin() + 5);
	/*
	- Vector iterators may be compared using operators like <, <=, etc.
	- For most containers (other than vectors), these “random access” iterator operations are not legal and therefore prevented by the
	   compiler - the reasons will become clear as we look at their implementations
*/


//9.8 Exercise: Revising the Class List Program to Use Iterators
/*
- Now let’s modify the class list program to use iterators (First rewrite the erase from vector to use iterators):*/
void erase_from_vector(vector<string>::iterator itr, vector<string>& v) {
	if (v.empty()) {return;}

	vector<string>::iterator itr2 = (itr+1);					// Have iterator in front of passed iterator - keep track of both
	
	for (unsigned int j=i ; itr2 != v.end() ; itr++, itr2++) {	// Go until itr2 reaches the area past vector (end())
		*itr = *itr2;
		itr2++;
	}
	v.pop_back();
}
/*
   (Note: the STL vector class has a function that does just this... called erase!)
- Now, edit the rest of the file to remove all use of the vector subscripting operator
*/


//9.9 A New Datatype: The STL list Container Class
/*
- Lists are our second standard-library container class (Vectors were the first) - both lists & vectors store sequential data that can
   shrink or grow
- However, the use of memory is fundamentally different: vectors are formed as a single contiguous array-like block of memory, and lists
   are formed as a sequentially linked structure instead

- Although the interface (functions called) of lists and vectors and their iterators are quite similar, their implementations are VERY
   different - clues to these differences can be seen in the operations that are NOT in common, such as:
	- STL vectors/arrays allow “random-access”/indexing /[]-subscripting - we can immediately jump to an arbitrary location within the
	   vector/array
	- STL lists have no subscripting operation (we can’t use [] to access data); the only way to get to the middle of a list is to follow
	   pointers one link at a time - here is where iterators come in
	- Lists have .push_front() and .pop_front() functions in addition to the .push_back() and .pop_back() functions of vectors
	- .erase() and. insert() in the middle of the STL list is very efficient, independent of the size of the list - both are implemented
	   by rearranging pointers between the small blocks of memory (We’ll see this when we discuss the implementation details next week)
	- We can’t use the same STL sort function we used for vector; we must use a special sort function defined by the STL list type
*/
	std::vector<int> my_vec;
	std::list<int> my_lst;
	// ... put some data in my_vec & my_lst
	std::sort(my_vec.begin(), my_vec.end(), optional_compare_function);
	my_lst.sort(optional_compare_function);
/*
	   Note: STL list sort member function is just as efficient, O(n log n), and will also take the same optional compare function as STL
	   vector
	- Several operations invalidate the values of vector iterators, but not list iterators:
		∗ erase() invalidates all iterators after the point of erasure in vectors
		∗ .push_back() and .resize() invalidate ALL iterators in a vector
	   The value of any associated vector iterator must be re-assigned / re-initialized after these operations
*/


//9.10 Exercise: Revising the Class List Program to Use Lists (& Iterators)
/*
classlist_ORIGINAL.cpp
- Now let’s further modify the program to use lists instead of vectors. Because we’ve already switched to iterators,
this change will be relatively easy. And now the program will be more efficient!
*/


//9.11 Erase & Iterators
/*
- STL lists and vectors each have a special member function called erase. In particular, given list of ints s, consider the example:
*/
std::list<int>::iterator p = s.begin();
++p;
std::list<int>::iterator q = s.erase(p);
/*
- After the code above is executed:
	- The integer stored in the second entry of the list has been removed
	- The size of the list has shrunk by one
	- The iterator p does not refer to a valid entry
	- The iterator q refers to the item that was the third entry and is now the second

- To reuse the iterator p and make it a valid entry, you will often see the code written:
*/
std::list<int>::iterator p = s.begin();
++p;
p = s.erase(p);
/*
- Even though the erase function has the same syntax for vectors and lists, the vector version is O(n), whereas the list version is O(1)
*/


//9.12 Insert
/*
- Similarly, there is an insert function for STL lists that takes an iterator and a value and adds a link in the chain with the new value
   immediately before the item pointed to by the iterator
- The call returns an iterator that points to the newly added element. Variants on the basic insert function are also defined
*/


//9.13 Exercise: Using STL list Erase & Insert
/*
- Write a function that takes an STL list of integers, lst, and an integer, x. The function should 1) remove all negative numbers from the
   list, 2) verify that the remaining elements in the list are sorted in increasing order, and 3) insert x into the list such that the
   order is maintained
*/
void ex9_13()(std::list<int>& lst, int x) {
	
	//Create 2 iterators
	std::list<int>::iterator itr1;
	std::list<int>::iterator itr2;

	//1. Remove all negatives from the list
	//Need to delete the negative node and point previous node to next one
	itr = lst.begin();
	while (itr != lst.end()) {
		if (*itr<0) {
			itr = lst.erase(itr);	//.erase() doesn't change the iterator; it deletes the node its at and advances to next node
		}
	itr++;
	}

	//2. Verify if elements are sorted - don't actually sort i
	if (lst.size() > 0) {

		itr1 = lst.begin();
		itr2 = lst.begin();		//CANNOT HAVE lst.begin()+1, WOULD NOT COMPILE - MUST HAVE ++itr
		++itr2;
		while(itr2 != lst.end()) {
			assert (*itr <= *itr2);
			itr1++; itr2++;
		}
	}

	//3. Inert x into list
	itr = lst.begin();
	bool found = false;
	while (itr != lst.end()) {
		if (*itr > x) {
			lst.insert(itr, x);
			found = true;
			break;
		}
	}
}


//9.14 Implementing Vec<T> Iterators
/*
- • Let’s add iterators to our Vec<T> class declaration from last lecture:
*/
public:
	// TYPEDEFS
	typedef T* iterator;
	typedef const T* const_iterator;
	
	// MODIFIERS
	iterator erase(iterator p);
	
	// ITERATOR OPERATIONS
	iterator begin() { return m_data; }
	const_iterator begin() const { return m_data; }
	iterator end() { return m_data + m_size; }
	const_iterator end() const { return m_data + m_size; }
/*
• First, remember that typedef statements create custom, alternate names for existing types: Vec<int>::iterator is an iterator type
   defined by the Vec<int> class. It is just a T * (an int *); thus, internal to the declarations and member functions, T* and iterator
   may be used interchangeably
• Because the underlying implementation of Vec uses an array, and because pointers are the “iterator”s of arrays, the implementation of
   vector iterators is quite simple. Note: the implementation of iterators for other STL containers is more involved!
• Thus, begin() returns a pointer to the first slot in the m data array. And end() returns a pointer to the “slot” just beyond the last
   legal element in the m data array (as prescribed in the STL standard)
• Furthermore, dereferencing a Vec<T>::iterator (dereferencing a pointer to type T) correctly returns one of the objects in the m data, an
   object with type T
• And similarly, the ++, --, <, ==, !=, >=, etc. operators on pointers automatically apply to Vec iterators
• The erase function requires a bit more attention. We’ve implemented the core of this function above. The STL standard further specifies
   that the return value of erase is an iterator pointing to the new location of the element just after the one that was deleted
• Finally, note that after a push back or erase or resize call some or all iterators referring to elements in that vector may be
   invalidated - why? You must take care when designing your program logic to avoid invalid iterator bugs!
*/