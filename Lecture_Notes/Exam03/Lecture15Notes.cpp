//Lecture 15 – Associative Containers (Maps), Part 1

//PREVIOUS LECTURE(S) REVIEW
/*
- How to design and implement algorithms using three steps or stages:
    1. Generating and Evaluating Ideas
    2. Mapping Ideas into Code
    3. Getting the Details Right
- Lots of Examples
*/


//OVERVIEW
/*
- STL Maps: associative containers for fast insert, access and remove
- Example: Counting word occurrences
- STL Pairs
- Map iterators
- Map member functions: operator[], find(), insert(), erase()'s
- Efficiency
- STL maps vs. STL vectors vs. STL lists
*/


//15.1 STL Maps: Associative Containers
/*
- STL MAPS store pairs of “associated” values (like a Python DICTIONARY but not quite...)
- We will see several examples today, in Lab 9, and in Lecture 15:
    - Association btwn a string, representing a word, and an int representing the # of times the word has been seen in an input file
    - Association btwn a string, representing a word, and a vector of ints that stores line # from a text file on which the string occurs
    - Association btwn a phone number and the name of the person with that number
    - Association btwn a class object representing a student name and the student’s info

- A particular instance of a map is defined (declared) w/ syntax:*/ std::map<[key_type], [value_type]> [var_name]/*
- In our first two examples above, key type is std::string; in 1st example, value type is int; in second, std::vector<int>.

- Entries in maps are PAIRS w/ syntax:*/ std::pair<const [key_type], [value_type]>/*

- Map iterators refer to pairs
- Map search(), insert(), and erase() all very fast: O(log(n)) time, where n = # of pairs stored in map
   (Note: The STL map type has similarities to Python dictionaries, Java HashMaps, or a Perl hashes, but the data structures are NOT the
    same: the organization, implementation, and performance are all different - later, we’ll see an STL data structure that is even more
    similar to the Python dictionary)
- Map search(), insert(), and erase() are O(log(n)) - Python dictionaries are O(1)

First, let’s see how this some of this works w/ a program to count occurrences of each word in a file - we’ll look at more details +
 examples later
*/


//15.2 Counting Word Occurrences
/*
- PROBLEM: Write a program to count occurrences of each word in a given input file
   - Here’s a simple + elegant solution to this problem using a map:*/
#include <iostream>
#include <map> // also does #include <pairs>, more on that later
#include <string>

int main() {
    std::string s;
    std::map<std::string, int> counters; // store each word and an associated counter
    
    /*
    int x;
    x = int();
    std::cout<<x<std::endl;
    */

    // read input, keeping track of each word + how often we see it
    while (std::cin >> s) {
        ++counters[s]; // does a multitude of things: see 15.5
    }
    
    // write the words and associated counts
    std::map<std::string, int>::const_iterator it;
    for (it = counters.begin(); it != counters.end(); ++it) {
        std::cout<<it->first<<"\t"<<it->second<<std::endl;
    }

    return 0;
}


//15.3 Maps: Uniqueness and Ordering
/*
- Maps are ordered by increasing value of the key; therefore, there must be an operator< defined for the key
- Once key + its value are entered in the map, the key can’t be changed,only erased (together w/ its associated value)
- Duplicate keys can not be in the map: all duplicates should be comind under the same key
*/


//15.4 STL Pairs
/*
The mechanics of using std::pairs are relatively straightforward:
- std::pairs = templated struct w/ two members: first and second (Reminder: struct = basically a wimpy class, not allowed to create new
   structs, instead use normal classes)
- To work with pairs, you must #include<utility> (Note: header file for maps (#include<map>) itself includes utility, so you don’t have
   to include utility explicitly when you use pairs with maps

- Here are simple examples of manipulating pairs:*/
// Both of these are acceptable to crate a pair object
std::pair<int, double> p1(5, 7.5);                      // p1 -> 5, 7.5
std::pair<int, double> p2 = std::make_pair(8, 9.5);     // p2 -> 8, 9.5

p1.first = p2.first;        // p1 -> 8, 7.5 ; p2 -> 8, 9.5
p2.second = 13.3;           // p1 -> 8, 7.5 ; p2 -> 8, 13.3

std::cout << p1.first << " " << p1.second << std::endl;
std::cout << p2.first << " " << p2.second << std::endl;

p1 = p2;

std::pair<const std::string, double> p3 = std::make_pair(std::string("hello"), 3.5);
p3.second = -1.5;
    // p3.first = std::string("illegal");   //(a)   // ERROR: not allowed to change the first of a pair
    // p1 = p3;                             //(b)   // ERROR: cannot convert between different types
/*
- The function std::make_pair() creates pair object from given values; it's really just a simplified constructor, and as the example shows
   there are other ways of constructing pairs

- Most of the statements in the above code show accessing+changing values in pairs
- The two statements at end = commented out because they cause syntax errors:
    - In (a): first entry of p3 is const, which means it can’t be changed
    - In (b): two pairs are different types! Make sure you understand this
- Returning to maps, each entry in the map is a pair object of type:*/ std::pair<const key_type, value_type>/*
- The const is needed to ensure that the keys aren’t changed! This is crucial since maps are sorted by keys!
*/


//15.5 Maps: operator[]
/*
- We’ve used the [] operator on vectors, which is, conceptually, very simple since vectors are just resizable arrays; Arrays+vectors are
   efficient random access data structures
- But operator[] is actually a function call, so it can do things that aren’t so simple too, for example:*/ ++counters[s];/*
- For maps, the [] operator searches the map for the pair w/ the key (string) s
    - If such a pair containing the key is not there, the operator:
        1. creates a pair containing the key + default initialized value,
        2. inserts the pair into the map in appropriate position, and
        3. returns reference to the value (2nd component of the pair) stored in this new pair
            (This second component may then be changed using operator++)
    - If a pair containing the key is there, the operator simply returns a reference to the value in that pair

- In this particular example, the result in either case is that the ++ operator increments the value associated with string s (to 1 if the
   string wasn’t already it a pair in the map)
- For the user of the map, operator[] makes the map feel like a vector, except that indexing is based on a
   string (or any other key) instead of solely an int
- Note: the result of using [] is that the key is ALWAYS in the map afterwards
*/


//15.6 Map Iterators
/*
- Iterators may be used to access the map contents sequentially
- Maps provide begin() and end() functions for accessing the bounding iterators
- Map iterators have ++ and -- operators
- Each iterator refers to a pair stored in the map; thus, given map iterator it,
    - it->first = const string
    - it->second = int
   (Notice the use of it->___; remember it is shorthand for (*it))
*/


//15.7 Exercise
/*
- Write code to create a map where the key is an integer and the value is a double. (Yes, an integer key!) Store each of the following in
   the map: 100 and its sqrt, 100,000 and its sqrt, 5 and its sqrt, and 505 and its sqrt
- Write code to output the contents of the map. Draw a picture of the map contents. What will the output be?*/
int intKey;
std::map<int, double> m;
m[100] = sqrt(100);
m[100000] = sqrt(100000);
m[5] = sqrt(5);
m[505] = sqrt(505);

std::map<int, double>::const_iterator mapItr = m.begin();
while (mapItr!=m.end()) {
	std::cout<<mapItr->first<<",  "<<mapItr->second<<std::endl;
	mapItr++;
}


//15.8 Map Find
/*
- One of the problems with operator[] is that it ALWAYS places a key-value pair in the map; sometimes we don’t want this, and instead we
   just want to check if a key is there
- The find() member function of the map class does this for us; for example:*/ [map_object].find([search_key]); /*
- find() returns a map iterator:
    - If the key is in one of the pairs stored in the map, find returns an iterator referring to this pair
    - If the key is not in one of the pairs stored in the map, find returns m.end()
*/


//15.9 Map Insert
/*
- The prototype for the map insert() member function is:*/ [map_object].insert(std::make_pair([key], [value]));/*
- insert() returns a pair, but not the pair we might expect; it is a pair of a map iterator and a BOOL:*/
   std::pair<map<key_type, value_type>::iterator, bool>
/*
- The insert() function checks to see if the key being inserted is already in the map
    - If so, it doesn't change the value and returns a (new) pair containing an iterator referring to the existing pair in the map + the
       bool value false
    - If not, it enters the pair in the map, and returns a (new) pair containing an iterator referring to the newly added pair in the map
       + the bool value true
*/


//15.10 Map Erase
/*
- Maps provide three different versions of the erase() member function:
    - */ void erase(iterator p);/* will erase the pair referred to by iterator p
    - */ void erase(iterator first, iterator last);/* will erase all pairs from map starting at first and going up to, but not including,
       last
    - */ [size_type] erase(const key_type& k); /*— erase pair containing key k, returning either 0 or 1, based on if the key was in
       a pair in the map or not
*/

//15.10a Extra Notes
/*
 - If key k is in map m, is m.find(k) equivalent to m[k]?
    - m.find(k) will return an iterator map<key_type, val_type>::iterator pointing to the pair with key k
    - m[k] will return a REFERENCE to the value in the pair with key k
*/


//15.11 Exercise
/*
- Re-write the word count program so that it uses find() and insert() instead of operator[]:*/
std::string s;
std::map<std::string, int> counters;

while (std::cin >> s) {
    
    // find() returns itr to key-value in map if exists and map.end() if not
    std::map<std::string, int>::iterator mapItr = counters.find(s);
    if (mapItr==counters.end()) {   // if doesn't exist
        counters.insert(std::make_pair(s, 1))   // create a pair with count 1 already, add to map
    }
    else {  // if does exist
        (mapItr->second)++; // simply add to value
    }
}


std::map<std::string, int>::const_iterator it;
for (it = counters.begin(); it != counters.end(); ++it) {
    std::cout<<it->first<<"\t"<<it->second<<std::endl;
}


//15.12 Choices of Containers
/*
- We can solve this word counting problem using several different approaches+containers:
    - vector/list of strings
    - vector/list of pairs (string + int)
    - map
    - ?
- How do these approaches compare? Which is cleanest, easiest, and most efficient, etc.?
*/