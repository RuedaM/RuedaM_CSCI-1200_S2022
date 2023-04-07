//Lecture 25 — Garbage Collection & Smart Pointers

//PREVIOUS LECTURE(S) REVIEW
/*
- Error handling strategies
- Basic exception mechanisms: try/throw/catch
- Functions & exceptions, constructors & exceptions
- Finishing binary search trees & the ds set class
*/


//OVERVIEW
/*
- What is Garbage?
- 3 Garbage Collection Techniques
- Smart Pointers
*/


//25.1 What is Garbage?
/*
- Not everything sitting in memory is useful: GARBAGE = anything that cannot have any influence on future computation
- With C++, programmer is expected to perform explicit memory management: you must use*/ delete /*when done with dynamically-allocated
   memory (created with*/ new /*)
- In Java and other languages with “garbage collection”, you aren't required to explicitly de-allocate memory: The system automatically
   determines what is garbage + returns it to available pool of memory - certainly, this makes it easier to learn to program in these
   languages, but automatic memory management does have performance+memory usage disadvantages
- Today we’ll overview 3 basic techniques for automatic memory management
*/


//25.2 The Node class
/*
- For our discussion today, we’ll assume all program data is stored in dynamically-allocated instances of a simple node class that can be
   used to build linked lists, trees, and graphs with cycles:*/
class Node {
   public:
      Node(char v, Node* l, Node* r) : value(v), left(l), right(r) {}
      char value;
      Node* left;
      Node* right;
};


//25.3 Garbage Collection Technique #1: Reference Counting
/*
1. Attach counter to each Node in memory
2. When new pointer is connected to that Node, increment counter
3. When pointer is removed, decrement counter
4. Any Node with counter == 0 is garbage + available for reuse
*/


//25.4 Reference Counting Exercise
/*
- Draw “box and pointer” diagram for the following example, keeping a “reference counter” with each Node:*/
Node *a = new Node('a', NULL, NULL);
Node *b = new Node('b', NULL, NULL);
Node *c = new Node('c', a, b);
a = NULL;
b = NULL;
c->left = c;
c = NULL;
/*
- Is there any garbage?
ANSWER: A - nothing is pointing to it
*/


//25.5 Memory Model Exercise
/*
- In memory, we pack Node instances into a big array - in example below, we have only enough room in memory to store 8 Nodes, which are
   addressed 100→107 - 0 is a NULL address
- For simplicity, we’ll assume that the program uses only one variable, root, through which it accesses all data. Draw the box-and-pointer
   diagram for data accessible from root = 105:

address  100  101  102  103  104  105  106  107
value    a    b    c    d    e    f    g    h
left     0    0    100  100  0    102  105  104
right    0    100  103  0    105  106  0    0

root: 105

- What memory is garbage?
*/


//25.6 Garbage Collection Technique #2: Stop and Copy
/*
1. Split memory in half (WORKING and COPY memory)
2. When out of working memory, stop computation, begin garbage collection:
   (a) Place scan + free pointers at start of copy memory
   (b) Copy root to copy memory, incrementing free - whenever node is copied from working memory, leave forwarding address to new location
        in copy memory in left address slot of old location
   (c) Starting at scan pointer, process left+right pointers of each node - look for their locations in working memory. If node has
        already been copied (i.e., it has forwarding address), update reference; otherwise, copy location (as before) + update reference
   (d) Repeat until scan == free
   (e) Swap roles of working+copy memory
*/


//25.7 Stop and Copy Exercise
/*
- Perform stop-and-copy on the following with root = 105:

WORKING MEMORY
address  100  101  102  103  104  105  106  107
value    a    b    c    d    e    f    g    h
left     0    0    100  100  0    102  105  104
right    0    100  103  0    105  106  0    0

COPY MEMORY
address  108  109  110  111  112  113  114  115
value
left
right

root: 105
scan: 
free: 

ANSWER:
WORKING MEMORY, now COPY MEMORY
address  100            101  102           103            104  105            106            107
value    a              b    c             d              e    f              g              h
left     0 (now 111)    0    100 (now 109) 100 (now 112)  0    102 (now 108)  105 (now 110)  104
right    0              100  103           0              105  106            0              0

COPY MEMORY, now WORKING MEMORY
address  108            109            110            111  112            113  114  115
value    f              c              g              a    d
left     102 (now 109)  100 (now 111)  105 (now 108)  0    100 (now 111)
right    106 (now 110)  103 (now 112)  0              0    0

root: 105
scan: 108, now 109, now 110, now 111, now 112
free: 108, now 109, now 110, now 111, now 112, now 113
*/


//25.8 Garbage Collection Technique #3: Mark-Sweep
/*
1. Add mark bit to each location in memory
2. Keep one free pointer to head of free list
3. When memory runs out, stop computation, clear mark bits, begin garbage collection
4. Mark
   (a) Start at root, follow accessible structure (keeping stack of where you still need to go)
   (b) Mark every node you visit
   (c) Stop when you see marked node so you don’t go into a cycle
5. Sweep
   (a) Start at end of memory, build new free list
   (b) If node is unmarked, then it’s garbage: hook it into free list by chaining left pointers
*/


//25.9 Mark-Sweep Exercise
/*
- Let’s perform Mark-Sweep on the following with root = 105:

address  100  101  102  103  104  105  106  107
value    a    b    c    d    e    f    g    h
left     0    0    100  100  0    102  105  104
right    0    100  103  0    105  106  0    0
marks    

root: 105
free: 
stack: 

ANSWER:
address  100  101  102  103  104          105  106  107
value    a    b    c    d    e            f    g    h
left     0    0    100  100  0 (now 107)  102  105  104 (now 0)
right    0    100  103  0    105          106  0    0
marks    Tr   Fls  Tr   Tr   Fls          Tr   Tr   Fls

root: 105
free: 107 199 101 104 107 0
stack: 106 103 100 105

insert('k', 100, 106)
*/


//25.10 Garbage Collection Comparison
/*
- Reference Counting:
   + fast, incremental
   – CANNOT handle cyclical data structures
   ? requires ∼33% extra memory (1 integer per node)
- Stop & Copy:
   – requires long pause in program execution
   + CAN handle cyclical data structures!
   – requires 100% extra memory (you can only use half the memory)
   + runs fast if most memory is garbage (it only touches the nodes reachable from root)
   + data clustered together, memory “de-fragmented”
- Mark-Sweep:
   – requires long pause in program execution
   + CAN handle cyclical data structures!
   + requires ∼1% extra memory (1 bit per node)
   – runs same speed regardless of how much memory is garbage

It must touch all nodes in mark phase and must link together all garbage nodes into free list
*/


//25.11 Practical Garbage Collection Methodology in C++: Smart Pointers
/*
- GARBAGE COLLECTION looks like attractive option both when quickly drafting a prototype system and when we are developing big complex
   programs that process+rearrange lots of data
- Unfortunately, general-purpose, invisible garbage collection isn’t something we can just tack onto C++, an enormous beast of a
   programming language (but that doesn’t stop people from trying!) - so, is there anything we can do? Yes, we can use Smart Pointers to
   gain some features of garbage collection
- Some examples below are modified from these nice online references:
http://ootips.org/yonat/4dev/smart-pointers.html
http://www.codeproject.com/KB/stl/boostsmartptr.aspx
http://en.wikipedia.org/wiki/Smart_pointer
http://www.boost.org/doc/libs/1_48_0/libs/smart_ptr/smart_ptr.htm
http://www.acodersjourney.com/2016/05/top-10-dumb-mistakes-avoid-c-11-smart-pointers/
*/


//25.12 What’s a Smart Pointer?
/*
- GOAL: create widget that works just like regular pointer most of the time, except at beginning+end of lifetime -syntax of how we
   construct smart pointers is different, and we don’t need to obsess about how/when it will get deleted (it happens automatically)
- Here’s one flavor of smart pointer (simplified from STL):*/
template <class T>
class auto_ptr {
   public:
      explicit auto_ptr(T* p = NULL) : ptr(p) {} /* prevents cast/conversion */
      ~auto_ptr() { delete ptr; }
      T& operator*() { return *ptr; }
      T* operator->() { return ptr; } /* fakes being a pointer */
   private:
      T* ptr;
};
/*
- And let’s start with some example code without smart pointers:
*/
void foo() {
   Polygon* p(new Polygon(/* stuff */));
   p->DoSomething();
   delete p;
}
/*
- Here’s how we can re-write same example with auto_ptr:
*/
void foo() {
   auto_ptr<Polygon> p(new Polygon(/* stuff */));
   p->DoSomething();
}
/*
- We don’t have to call*/ delete/*! There’s no memory leak/error in code
*/


//25.13 So, What are the Advantages of Smart Pointers?
/*
- Smart pointers are magical: they allow us to be lazy! All time spent learning about dynamically-allocated memory, copy constructors,
   destructors, memory leaks, and segmentation faults this semester was unnecessary. Whoa...that’s overstating things more than slightly!!
- With practice, smart pointers can result in code that's more concise+elegant with fewer errors. Why?

- With thoughtful use, smart pointers make it easier to follow principles of RAII + make code exception safe. In auto_ptr example above,
   if DoSomething throws exception, memory for object p will be properly deallocated when we leave scope of foo function! This is not the
   case with original version

- The STL shared_ptr flavor implements reference counting garbage collection - awesome
- They play nice with STL containers: say you make std::vector (or std::list, or std::map, etc.) of regular pointers to Polygon objects,
   Polygon*'s (especially handy if this is a polymorphic collection of objects!) - You allocate them all with new, and when finished you
   must remember to explicitly deallocate each of the objects.*/
class Polygon { /*...*/ };
class Triangle : public Polygon { /*...*/ };
class Quad : public Polygon { /*...*/ };

std::vector<Polygon*> polys;
polys.push_back(new Triangle( /*...*/ ));
polys.push_back(new Quad( /*...*/ ));

for (unsigned int i = 0; i < polys.size(); i++) {delete polys[i];}
polys.clear();
/*

In contrast, with smart pointers they will be deallocated automagically!*/
std::vector<shared_ptr<Polygon> > polys;

polys.push_back(shared_ptr<Polygon>(new Triangle(/*...*/)));
polys.push_back(shared_ptr<Polygon>(new Quad(/*...*/)));

polys.clear(); // cleanup is automatic!


//25.14 Why are Smart Pointers Tricky?
/*
- Smart pointers do not alleviate need to master pointers, basic memory (de)allocation, copy constructors, destructors, assignment
   operators, and reference variables
- You can still make mistakes in smart pointer code that yield same types of memory corruption, seg.faults, + memory leaks as regular
   pointers
- There are several different flavors of smart pointers to choose from (developed for different uses, for common design patterns) - You
   need to understand your application + different pitfalls when selecting appropriate implementation
*/


//25.15 What are the Different Types of Smart Pointers?
/*
- Like other parts of the C++ standard, these tools are still evolving. The different choices reflect different ownership
semantics and different design patterns. There are some smart pointers in STL, and also some in Boost (a C++
library that further extends the current STL). A quick overview:

- auto_ptr
   - When “copied” (copy constructor), the new object takes ownership and the old object is now empty. Deprecated in new C++ standard
- unique_ptr
   - Cannot be copied (copy constructor not public). Can only be “moved” to transfer ownership. Explicit ownership transfer. Intended to
      replace auto_ptr. std::unique ptr has memory overhead only if you provide it with some non-trivial deleter. It has time overhead
      only during constructor (if it has to copy the provided deleter) and during destructor (to destroy the owned object)
- scoped_ptr (Boost)
   - “Remembers” to delete things when they go out of scope. Alternate to auto_ptr. Cannot be copied.
- shared_ptr
   - Reference counted ownership of pointer. Unfortunately, circular references are still a problem. Different sub-flavors based on where
      the counter is stored in memory relative to the object, e.g., intrusive_ptr, which is more memory efficient. std::unique ptr has
      memory overhead only if you provide it with some non-trivial deleter. It has time overhead in constructor (to create the reference
      counter), in destructor (to decrement the reference counter and possibly destroy the object) and in assignment operator (to
      increment the reference counter).
- weak_ptr
   - Use with shared_ptr. Memory is destroyed when no more shared_ptrs are pointing to object. So each time a weak_ptr is used you should
      first “lock” the data by creating a shared_ptr.
- scoped_array and shared_array (Boost)

*/