//Lecture 20 – Hash Tables, Part I

//PREVIOUS LECTURE(S) REVIEW
/*
- Last pieces of ds_set: removing an item, erase, operator++
- Breadth-first and depth-first search
*/


//OVERVIEW
/*
- “the single most important data structure known to mankind”
- Hash Tables, Hash Functions, and Collision Resolution
- Performance of: Hash Tables vs. Binary Search Trees
- Collision resolution: separate chaining vs open addressing
- STL’s unordered_set (and unordered_map)
- Using a hash table to implement a set/map
   - Hash functions as functors/function objects
   - Iterators, find, insert, and erase
*/


//20.1 Definition: What’s a Hash Table?
/*
- HASH TABLE - table implementation w/ constant time access
   - Like a set, we can store elements in collection; or like a map, we can store key-value pair associations in hash table. But it’s even
      faster to do find, insert, and erase with hash table; however, hash tables don't store data in sorted order
- Hash table implemented with array at top level
- Each element (key) mapped to slot in array by hash function
*/


//20.2 Definition: What’s a Hash Function?
/*
- HASH FUNCTION: simple function of one argument (key) which returns integer index (bucket/slot in array)
- Ideally, function will “uniformly” distribute keys throughout range of legal index values (0 --> k-1)
- What’s a collision? When hash function maps multiple (different) keys to same index
- How do we deal with collisions? One way is by storing linked list of values at each slot in array
*/


//20.3 Example: Caller ID
/*
- We are given phonebook with 50,000 name/number pairings, each number is 10 digit number. We need to create a data structure to lookup
   the name matching particular phone number; Ideally, name lookup should be O(1) time expected, and caller ID system should use O(n)
   memory (n = 50,000)
- Note: In toy implementations that follow, we use small datasets, but we should evaluate the system scaled up to handle the large dataset
- The basic interface:*/
// add several names to the phonebook
add(phonebook, 1111, "fred");
add(phonebook, 2222, "sally");
add(phonebook, 3333, "george");
// test the phonebook
std::cout<<identify(phonebook, 2222)<<" is calling!"<<std::endl;
std::cout<<identify(phonebook, 4444)<<" is calling!"<<std::endl;
/*
- We’ll review how we solved this problem in Lab 9 w/ STL vector then STL map; finally, we’ll implement w/ hash table
*/


//20.4 Caller ID with an STL Vector
// create an empty phonebook
std::vector<std::string> phonebook(10000, "UNKNOWN CALLER");

// go to place w/ number, store name
void add(std::vector<std::string> &phonebook, int number, std::string name) {phonebook[number] = name;}

std::string identify(const std::vector<std::string> &phonebook, int number) {return phonebook[number];}
/*
- Exercise: What is memory usage for vector-based Caller ID system? What is expected running time for identify, insert, and erase?
ANSWER:
O(1) for all operations since index has already ben declared, and all you're doing is accessing an index; very fast
However, memory would be O(N) where N is number of possible unique values for phone numbers - very bad for memory
*/


//20.5 Caller ID with an STL Map
// create an empty phonebook
std::map<int,std::string> phonebook;

void add(std::map<int,std::string> &phonebook, int number, std::string name) {phonebook[number] = name;}

std::string identify(const std::map<int,std::string> &phonebook, int number) {
   map<int,std::string>::const_iterator tmp = phonebook.find(number);
   if (tmp == phonebook.end()) {return "UNKNOWN CALLER"; else return tmp->second;}
}
/*
- Exercise: What is memory usage for map-based Caller ID system? What is expected running time for identify, add, and erase?
ANSWER:

*/


//20.6 Now let’s implement Caller ID with a Hash Table
#define PHONEBOOK_SIZE 10

class Node {
   public:
      int number;
      string name;
      Node* next;
};

// create the phonebook, initially all numbers are unassigned
Node* phonebook[PHONEBOOK_SIZE];
for (int i=0 ; i<PHONEBOOK_SIZE ; i++) {phonebook[i] = NULL;}

// corresponds a phone number to a slot in the array
int hash_function(int number) {
   return (number%10;) // returns last digit
}

// add a number, name pair to the phonebook
void add(Node* phonebook[PHONEBOOK_SIZE], int number, string name) {
   // find which spot to put number/name in
   int idx = hash_function(number);

   // make new Node, fill in number/name
   Node* tmp = new Node;
   tmp->number = number;
   tmp->name = name;

   // add to hash table
   tmp->next = phonebook[idx]; // connects Bob to Erin
   phonebook[idx] = tmp; // connects phonebook's slot 8 to Bob
}

// given a phone number, determine who is calling
void identify(Node* phonebook[PHONEBOOK_SIZE], int number) {
   // find which spot to put number/name in
   int idx = hash_function(number);

   Node* tmp = phonebook[idx];
   while (tmp) {
      if (tmp-> number = number) {return tmp->name;} // found match
   }
   tmp = tmp->next;
}
return "UNKNOWN CALLER"


//20.7 Exercise: Choosing a Hash Function
/*
- What is a good hash function for this application?
ANSWER: 

- What is a bad hash function for this application?
ANSWER: first digit
*/


//20.8 Exercise: Hash Table Performance
/*
- What is memory usage for the hash-table-based Caller ID system?
ANSWER:

- What is expected running time for identify, insert, and erase?
ANSWER:  
*/


//20.9 What makes a Good Hash Function?
/*
- Goals: fast O(1) computation and random, uniform distribution of keys throughout table, despite actual distribution of keys that are to
   be stored
- For example, using: f(k) = abs(k)%N satisfies the first requirement, but may not satisfy the second
- Another example of dangerous hash function on string keys is to add/multiply ascii values of each char:*/
unsigned int hash(string const& k, unsigned int N) {
   unsigned int value = 0;
   for (unsigned int i=0; i<k.size(); ++i) {value += k[i];} // conversion to int is automatic
   return value % N;
}
/*
- The problem is that different permutations of the same string result in the same hash table location.
- This can be improved through multiplications that involve the position and value of the key:*/
unsigned int hash(string const& k, unsigned int N) {
   unsigned int value = 0;
   for (unsigned int i=0; i<k.size(); ++i) {value = value*8 + k[i];} // conversion to int is automatic
   return value % N;
}
/*
- In conclusion, modulo arithmetic is not necessarily a mark of a good hash function since we've shown that value*8 + k[i] is valid too
- The latter is better, but can be improved further - theory of good hash functions quite involved+beyond course's scope
*/


//20.10 How do we Resolve Collisions? METHOD 1: Separate Chaining
/*
- Each table location stores linked list of keys (+ values) hashed to that location (as shown above in phonebook hash table). Thus,
   hashing function really just selects which list to search/modify
- This works well when number of items stored in each list is small, e.g., average of 1. Other data structures (e.g. binary search trees)
   may be used in place of list, but these have even greater overhead considering the (hopefully, very small) # of items stored per bin
*/


//20.11 How do we Resolve Collisions? METHOD 2: Open Addressing
/*
- In open addressing, when chosen table location already stores key (or key-value pair), a different table location is sought to store new
   value (or pair)

- 3 different open addressing variations to handle collision during an insert operation:
   1. Linear probing: If i is chosen hash location, this sequence of table locations is tested (“probed”) until empty location is found:
       (i+1)%N, (i+2)%N, (i+3)%N, ...
   
   2. Quadratic probing: If i is hash location, this sequence of table locations is tested:
       (i+1)%N, (i+2*2)%N, (i+3*3)%N, (i+4*4)%N, ...
      More generally, the jth “probe” of the table is (i + c1j + c2j^2) mod N where c1 and c2 are constants
   
   3. Secondary hashing: when collision occurs, second hash function applied to compute new table location; repeated until empty location
       is found

- For each of these approaches, the find operation follows same sequence of locations as insert operation; key value determined to be
   absent from table only when empty location is found
- When using open addressing to resolve collisions, erase function must mark location as “formerly occupied” - if location is instead
   marked empty, find may fail to return elements in table
   - Formerly-occupied locations may (and should) be reused, but only after find operation has been run to completion

- Problems with open addressing:
   - Slows dramatically when table is nearly full (e.g. ~80%+); particularly problematic for linear probing
   - Fails completely when table is full
   - Cost of computing new hash values
*/


//20.12 Hash Table in STL?
/*
- The STL standard+implementation of hash tables have been slowly evolving over many years. Unfortunately, the names “hashset” and
   “hashmap” were spoiled by developers anticipating STL standard, so to avoid breaking/having name clashes with code using these early
   implementations...
- STL’s agreed-upon standard for hash tables: unordered-set and unordered_map

- Depending on OS/compiler, you may need to add -std=c++11 flag to compile line (or other configuration tweaks) to access these more
   recent pieces of STL. (This will certainly continue to evolve in future years!)
   - Also, STL has good default hash functions for many types, so you may not always need to specify both template parameters!
*/


//20.13 Our Copycat Version: A Set As a Hash Table
/*
- The class is templated over both the key type + hash function type:*/
template < class KeyType, class HashFunc >
class ds_hashset { /*...*/ };
/*
- We use separate chaining for collision resolution; hence, main data structure inside class is:*/
std::vector< std::list<KeyType> > m_table;
/*
- We will use automatic resizing when table is too full. Resize is expensive, of course - similar to automatic reallocation that occurs
   inside vector push_back function, we at least double size of underlying structure to ensure it is rarely needed
*/


//20.14 Our Hash Function (as a Functor/Function Object)
/*
- Next lecture, we’ll talk about “function objects”/“functors”...
   - FUNCTOR = class wrapper around function, and function is implemented as overloaded function call operator for class
- Often, programmer/designer for program using hash function has best understanding of distribution of data to be stored in hash function;
   Thus, they are in best position to define custom hash function (if needed) for data + application

- Here’s example of (generically) good hash function for STL strings, wrapped inside of class:*/
class hash_string_obj {
   public:
      unsigned int operator() (std::string const& key) const {
         unsigned int hash = 1315423911;
         for (unsigned int i=0 ; i<key.length() ; i++) {
            hash ^= ((hash<<5) + key[i] + (hash>>2));
         }
         return hash;
      }
};
// This implementation comes from http://www.partow.net/programming/hashfunctions/
/*
- Once new type containing hash function is defined, we can create instances of our hash set object containing std::string by specifying
   type hash_string_obj as second template parameter to declaration of ds_hashset:*/
ds_hashset<std::string, hash_string_obj> my_hashset;
/*
- Alternatively, we could use function pointers as a non-type template argument.
(We don’t show that syntax here!).
*/


//20.15 Hash Set Iterators
/*
- Iterators move through hash table in order of storage locations rather than ordering imposed by, for example, operator<. Thus,
   visiting/printing order depends on hash function + table size
– Hence, increment operators must move to next entry in current linked list or, if end of current list reached, to 1st entry in next
   non-empty list
- Declaration nested inside ds_hashset declaration in order to avoid explicitly templating iterator over hash function type

- Iterator must store:
   - Pointer to hash table it's associated with; this reflects subtle point about types: even though iterator class is declared inside
      ds_hashset, DOES NOT mean iterator automatically knows about any particular ds_hashset
   - Index of current list in hash table
   - An iterator referencing current location in current list
- Because of way classes are nested, iterator class object must declare ds_hashset class as friend, but reverse is unnecessary
*/
class iterator {
public:
   friend class ds_hashet;
private:
   ds_hashset* m_hs;


};
//dereference
const KeyType& operator*()


//20.16 Implementing begin() and end()
/*
- begin(): Skips over empty lists to find 1st key in table - must tie iterator being created to particular ds_hashset object it is applied
   to, which is done by passing "this pointer" to iterator constructor
- end(): Also associates iterator with specific table, assigns index of -1 (indicating it is not normal valid index), and thus doesn't
   assign particular list iterator

- Exercise: Implement the begin() function:*/
qwerty;


//20.17 Iterator Increment, Decrement, & Comparison Operators
/*
- Increment operators must find next key, either in current list or next non-empty list
- Decrement operator must check if iterator in list is at beginning; if so, it must proceed to find previous non-empty list + find last
   entry in that list
   - This may sound expensive, but remember that lists should be very short
- Comparison operators must accommodate that when at least one of the iterators is end, the internal list iterator won't have useful value
*/


//20.18 Insert & Find
/*
- Computes hash function value then index location
- If key is already in list that is at index location, no changes made to set; but iterator is created referencing location of key, pair
   returned w/ this iterator + false.
- If key not in list at index location, key should be inserted in list (at front is fine), and new iterator created referencing location
   of newly-inserted key a pair is returned with this
iterator and true.
- Exercise: Implement the insert() function, ignoring for now the resize operation:*/


/*
- Find = similar to insert, computing hash function + index, followed by std::find operation:*/
iterator find(const KeyType& key) {
   unsigned int hash_value = m_hash(key);
   unsigned int index = hash_value % m_table.size();

   hash_list_itr p = std::find(m_table[index].begin(), m_table[index].end(), key);
   if (p==m_table[index].end()) {return this->end();}
   else {return iterator(this, index, p);}
}


//20.19 Erase
/*
- Two versions implemented: one based on key value, another based on iterator - these are based on finding appropriate iterator location
   in appropriate list + applying list erase function:*/
it erase(const KeyType& key) {
   // find key, use erase iterator function
   iterator p = find(key);
   if (p==end()) {return 0;}
   else {erase(p); return 1;}
}

void erase(iterator p) {
   m_table[p.m_table]
}


//20.20 Resize
/*
- Must copy contents of current vector into scratch vector, resize current vector, then re-insert each key into resized vector
- Exercise: Write resize():*/
qwerty;


//20.21 Hash Table Iterator Invalidation
/*
- Any insert operation invalidates all ds_hashset iterators because insert operation could cause resize of table. Erase only invalidates
   iterator that references current object
*/