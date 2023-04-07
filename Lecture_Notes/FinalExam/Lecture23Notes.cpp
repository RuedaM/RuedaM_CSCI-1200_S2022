//Lecture 23 - Priority Queues

//PREVIOUS LECTURE(S) REVIEW
/*
- Hash Tables, Hash Functions, and Collision Resolution
- Performance of: Hash Tables vs. Binary Search Trees
- Collision resolution: separate chaining vs open addressing
- STL’s unordered_set (and unordered_map)
- Using a hash table to implement a set/map
   - Hash functions as functors/function objects
   - Iterators, find, insert, and erase
- Using STL’s for_each
- Something weird & cool in C++... Function Objects, a.k.a. Functors
- STL Queue and STL Stack
*/


//OVERVIEW
/*
- Definition of a Binary Heap (Lec 21 Notes)
- What’s a Priority Queue? (Lec 21 Notes)
- A Priority Queue as a Heap
- A Heap as a Vector
- Building a Heap
- Heap Sort
*/


//23.1 Implementing Pop (a.k.a. Delete Min)
/*
- Value at top (root) of tree replaced by value stored in last leaf node - This has echoes of erase() in binary search trees
- Last leaf node removed

- QUESTION: How do we find last leaf? Ignore this for now...

- Value now at root likely breaks heap property. We use percolate_down() to restore heap property - this function is written here in terms
   of tree nodes with child pointers (and priority stored as a value), but later it will be written in terms of vector subscripts:*/
percolate_down(TreeNode<T> * p) {
   while (p->left) {
      TreeNode<T>* child;
      // Choose the child to compare against
      if (p->right && p->right->value<p->left->value) {child = p->right;}
      else {child = p->left;}
      
      if (child->value<p->value) {
         swap(child, p); // value and other non-pointer member vars
         p = child;
      }
      else {break;}
   }
}


//23.2 Implementing Push (a.k.a. Insert)
/*
- To add value to heap, new last leaf node in tree is created to store that value
- Then percolate_up() is run - it assumes each node has a pointer to its parent:*/
percolate_up(TreeNode<T> * p) {
   while (p->parent) {
      if (p->value < p->parent->value) {
         swap(p, parent); // value and other non-pointer member vars
         p = p->parent;
      }
      else {break;}
   }
}


//23.3 Push (Insert) and Pop (Delete-Min) Usage Exercise
/*
- Suppose the following operations are applied to an initially empty binary heap of integers. Show resulting heap after each delete_min()
   (Remember: tree must be complete!)

push 5, push 3, push 8, push 10, push 1, push 6,
pop,
push 14, push 2, push 4, push 7,
pop,
pop,
pop


NOTE: height_of_tree = log,base 2, ((#_of_nodes)+1)
*/


//23.4 Heap Operations Analysis
/*
- Both percolate_down and percolate_up are O(log n) in the worst-case - why?
- But, percolate_up (and as a result push) is O(1) in the average case - why?
*/


//23.5 Implementing a Heap with a Vector (instead of Nodes & Pointers)
/*
- In vector implementation, tree is never explicitly constructed; instead, heap is stored as vector, and child + parent “pointers” can be
   implicitly calculated
- To do this, number the nodes in tree starting with 0 first by level (top to bottom) then scanning across each row (left to right); these
   are the vector indices  -place the values in a vector in this order
- As a result, for each subscript, i:
   - Parent, if it exists, is at location (i − 1)/2
   - Left child, if it exists, is at location 2i + 1
   - Right child, if it exists, is at location 2i + 2
- For binary heap containing n values, last leaf is at location n − 1 in vector, and first node with less than two children is at location
   b(n − 1)/2c
- Standard Library (STL) priority_queue is implemented as a binary heap
*/


//23.6 Heap as a Vector Exercises
/*
- Draw a binary heap with values: 52 13 48 7 32 40 18 25 4, first in tree (nodes+pointers) representation, then in vector representation

- Starting with an initially empty heap, show the vector contents for the binary heap after each delete_min() operation:
push 8, push 12, push 7, push 5, push 17, push 1,
pop,
push 6, push 22, push 14, push 9,
pop,
pop,
*/


//23.7 Building A Heap
/*
- In order to build a heap from a vector of values, for each index from b(n−1)/2c down to 0, run percolate_down.
Show that this fully organizes the data as a heap and requires at most O(n) operations.
- If instead, we ran percolate_up from each index starting at index 0 through index n-1, we would get properly
organized heap data, but incur a O(n log n) cost. Why?
*/


//23.8 Heap Sort
/*
- Heap Sort is a simple algorithm to sort vector of values: Build heap, then run n consecutive pop operations, storing each “popped” value
   in a new vector
- It is straightforward to show that this requires O(n*log(n)) time

- Exercise: Implement in-place heap sort; an in-place algorithm uses only the memory holding the input data – a separate, large, temporary
   vector is not needed
*/


//23.9 Summary Notes about Vector-Based Priority Queues
/*
- Priority queues conceptually similar to queues, but order in which values/entries are removed (“popped”) depends on priority
- Heaps, which are conceptually binary trees implemented in vectors, are data structure of choice for a priority queue
- In some applications, priority of an entry may change while entry is IN priority queue; this requires “hooks” (usually in the form of
   indices) into internal structure of priority queue (This is an implementation detail we have not discussed)
*/