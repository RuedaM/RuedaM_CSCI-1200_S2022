//Lecture 21 – Hash Tables, Part II

//PREVIOUS LECTURE(S) REVIEW
/*
- Hash Tables, Hash Functions, and Collision Resolution
- Performance of: Hash Tables vs. Binary Search Trees
- Collision resolution: separate chaining vs open addressing
- STL’s unordered_set (and unordered_map)
*/


//21.1 Using STL’s for_each
/*
- First, here’s a tiny helper function:*/
void float_print (float f) {std::cout << f << std::endl;}
/*
- Let’s make an STL vector of floats:*/
std::vector<float> my_data;
my_data.push_back(3.14); my_data.push_back(1.41);
my_data.push_back(6.02); my_data.push_back(2.71);
/*
- Now we can write a loop to print out all the data in our vector:*/
std::vector<float>::iterator itr;
for (itr = my_data.begin(); itr != my_data.end(); itr++) {float_print(*itr);}
/*
- Alternatively, we can use it with STL’s for_each function to visit and print each element:*/
std::for_each(my_data.begin(), my_data.end(), float_print);
/*
   Wow! That’s a lot less to type. Can I stop using regular for- and while-loops altogether?

- We can actually also do the same thing w/out creating + explicitly naming float_print function. We create an anonymous function using
   lambda:*/
std::for_each(my_data.begin(), my_data.end(), [](float f){std::cout<<f<<std::end;});
/*
- Lambda is new to C++ (part of C++11). But lambda is a core piece of many classic, older programming languages including Lisp and Scheme
- Python lambdas and Perl anonymous subroutines are similar. (In fact lambda dates back to the 1930’s, before 1st computers were built!)
   - You’ll learn more about lambda more in later courses like CSCI 4430 - Programming Languages
*/


//21.2 Function Objects, a.k.a. Functors
/*
- In addition to basic mathematical operators (+ - * / < >), another operator we can overload for C++ classes is function call operator
   - Why do we want to do this? This allows instances/objects of our class, to be used like functions; weird, but powerful
- Here’s basic syntax - any specific number of arguments can be used:*/
class my_class_name {
   public:
      // ... normal class stuff ...
      
      my_return_type operator() ( /* my list of args */ );
};


//21.3 Why are Functors Useful?
/*
- One example is default 3rd argument for std::sort: We know that, by default, STL’s sort routines will use less than comparison for the
   type stored inside the container. How exactly do they do that?
- First let’s define another tiny helper function:*/
bool float_less(float x, float y) {return x < y;}
/*
- Remember how we can sort the my_data vector defined above using our own homemade comparison function for sorting:*/
std::sort(my_data.begin(),my_data.end(),float_less);
/*
If we don’t specify a 3rd argument:*/ std::sort(my_data.begin(),my_data.end());/*
This is what STL does by default:*/ std::sort(my_data.begin(),my_data.end(),std::less<float>());

/*
- What is std::less? A templated class
   - Above, we have called the default constructor to make an instance of that class. Then, that instance/object can be used like a
      function - how strange...
- How does it do that? std::less = tiny class that just contains overloaded function call operator:*/
template <class T>
class less {
   public:
      bool operator() (const T& x, const T& y) const { return x < y; }
};
/*
   You can use this instance/object/functor as function that expects exactly two arguments of type T (in this example: float) that returns
    bool. This is exactly what we need for std::sort
   This ultimately does the same thing as our tiny helper homemade compare function
*/


//21.4 Another more Complicated Functor Example
/*
- Constructors of function objects can be used to specify internal data for functor that can then be used during computation of function
   call operator! For example:*/
class between_values {
   private:
      float low, high;
   public:
      between_values(float l, float h) : low(l), high(h) {}
      bool operator() (float val) { return low <= val && val <= high; }
};
/*
- The range between low+high is specified when functor/instance of this class is created - we might have multiple different instances of
   between_values functor, each with their own range. Later, when functor is used, query value will be passed in as argument - function
   call operator accepts that single argument val + compares against internal data low + high

- This can be used with STL’s find_if construct. For example:*/
between_values two_and_four(2,4);
if (std::find_if(my_data.begin(), my_data.end(), two_and_four) != my_data.end()) {
   std::cout << "Found a value greater than 2 & less than 4!" << std::endl;
}
/*
- Alternatively, we could create functor w/out giving it a variable name - In the use below, we also capture the return value to print out
   the first item in vector in this range (Note that it does not print all values in the range):*/
std::vector<float>::iterator itr;
itr = std::find_if(my_data.begin(), my_data.end(), between_values(2,4));
if (itr != my_data.end()) {
   std::cout << "my_data contains " << *itr
            << ", a value greater than 2 & less than 4!" << std::endl;
}


//21.5 Using STL’s Associative Hash Table (Map)
/*
- Using the default std::string hash function...
   - with no specified initial table size:*/
      std::unordered_map<std::string,Foo> m;/*
   - optionally specifying initial (minimum) table size:*/
      std::unordered_map<std::string,Foo> m(1000);/*

- Using a home-made std::string hash function... (Note: We are required to specify the initial table size)
   - and manually specifying the hash function type:*/
      std::unordered_map<std::string,Foo,std::function<unsigned int(std::string)> > m(1000, MyHashFunction);/*
   - and using the decltype specifier to get the “declared type of an entity”*/
      std::unordered_map<std::string,Foo,decltype(&MyHashFunction)> m(1000, MyHashFunction);/*

- Using a home-made std::string hash functor/function object...
   - with no specified initial table size:*/
      std::unordered_map<std::string,Foo,MyHashFunctor> m;/*
   - optionally specifying initial (minimum) table size:*/
      std::unordered_map<std::string,Foo,MyHashFunctor> m(1000);/*

- Note: In above examples, we’re creating association btwn 2 types (STL strings + custom Foo object). If you’d like to just create a set
   (no associated 2nd type), simply switch from unordered_map to unordered_set + remove Foo from template type in examples above
*/


//21.6 Additional STL Container Classes: Stacks + Queues
/*
- We’ve studied STL vectors, lists, maps, and sets; these data structures provide wide range of flexibility in terms of operations - one
   way to obtain computational efficiency is to consider a simplified set of operations/functionality
- For example, w/ hash tables, we give up the notion of a sorted table + gain in_find, insert, & erase efficiency
- 2 additional examples are:
   - STACKS allow access/insertion/deletion from only one end called the top
      - No access to values in middle of stack
      - Stacks may be implemented efficiently w/ vectors+lists, although vectors are prefered
      - All stack operations are O(1)
   - QUEUES allow insertion at one end (back) and removal from the other (front)
      - No access to values in middle of queue
      - Queues may be implemented efficiently w/ lists - using vectors for queues also possible but requires more work to get right
      - All queue operations are O(1)
*/


//21.7 Exercises: Tree Traversal using a Stack and Queue
/*
Given a pointer to the root node in a binary tree:
- Use an STL stack to print the elements with a pre-order traversal ordering. This is straightforward:*/
qwerty;
/*
- Use an STL stack to print the elements with an in-order traversal ordering. This is more complicated:*/
qwerty;
/*
- Use an STL queue to print the elements with a breadth-first traversal ordering:*/
qwerty;


//21.8 What’s a Priority Queue?
/*
- PRIORITY QUEUES = used in prioritizing operations. Examples include personal “to do” list, what order to do homework assignments, jobs on
   shop floor, packet routing in network, scheduling in operating system, events in simulation, etc.
- Among the data structures we have studied, their interface is most similar to a queue, including the idea of front (top) + tail (back)
- Each item stored in priority queue using associated “priority” and, therefore, top item is one w/ the lowest value of priority score - 
   tail/back never accessed through public interface to priority queue
- Main operations = push (insert) + pop (delete_min)
*/


//21.9 Some Data Structure Options for Implementing a Priority Queue
/*
- Vector/list, sorted/unsorted
   - At least one of the operations, push/pop, will cost linear time, at least if we think of the container as linear structure
- Binary search trees
   - If we use priority as key, we can use combination of finding minimum key + erase to implement pop. An ordinary binary-search-tree
      insert may be used to implement push
   - This costs logarithmic time in average case (and worst case as well if balancing used)

- Latter is better solution, but we would like to improve upon it — for example, it might be more natural if minimum priority value were
   stored at root
   - Next lecture, we will achieve this w/ binary heap, giving up complete ordering imposed in binary search tree
*/


//21.10 Definition: Binary Heaps
/*
- BINARY HEAP = complete binary tree such that at each internal node, p, value stored is less than value stored at either of p’s children
   - Complete binary tree = completely filled, except perhaps at the lowest level, and at lowest level all leaf nodes are as far to the
      left as possible
- Binary heaps will be drawn as binary trees, but implemented using vectors!
- Alternatively, heap could be organized such that value stored at each internal node is greater than values at its children
*/


//21.11 Exercise: Drawing Binary Heaps
/*
- Draw two different binary heaps with these values: 52 13 48 7 32 40 18 25 4
                                              _-4-_
                                             /     \
                                            7      13
                                          /   \   /  \
                                         18   25 32  40
                                        /  \
                                       40  52

                                              _-4-_
                                             /     \
                                            13      7
                                           /  \    / \
                                         40   18  32 25
                                        /  \
                                       52  48

Both of these work - so long as every node has a value smaller than its children, it is valid

- Draw several other trees with these values that are not binary heaps
*/