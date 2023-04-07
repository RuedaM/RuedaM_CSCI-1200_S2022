// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>

#include <map>
#include <algorithm>
using namespace std;

// add a number, name pair to the phonebook
/*
void add(vector<string> &phonebook, int number, string const& name) {
  phonebook[number] = name;
}
*/

void add(map<int, string> &phonebook, long int number, string const& name) {
    phonebook.insert(pair<int,string>(number, name)); 
}

// given a phone number, determine who is calling
/*
void identify(const vector<string> & phonebook, int number) {
  if (phonebook[number] == "UNASSIGNED") 
    cout << "unknown caller!" << endl;
  else 
    cout << phonebook[number] << " is calling!" << endl;
}
*/

void identify(const map<int, string> & phonebook, long int number) {
    map<int, string>::const_iterator itr; 
    // If the number can not be found, print unknown caller
    if (phonebook.find(number) == phonebook.end()) {
        cout << "unknown caller!" << endl;
    }
    else { //If it can be found
        itr = phonebook.find(number);
        cout << itr->second << " is calling!" << endl; 
    }
    
}

int main() {
  // create the phonebook; initially all numbers are unassigned
  // vector<string> phonebook(10000, "UNASSIGNED");

  map<int, string> phonebook;

  cout << "Original Test: " << endl; 
  // add several names to the phonebook
  add(phonebook, 1111, "fred");
  add(phonebook, 2222, "sally");
  add(phonebook, 3333, "george");

  // test the phonebook
  identify(phonebook, 2222);
  identify(phonebook, 4444);

  cout << "\nMy Tests: " << endl;
  // Test Cases:
  add(phonebook, 6463339922, "Peter"); // 10 digits
  add(phonebook, 69696969, "Max");     // 8 digits
  add(phonebook, 8887776, "Ivan");     // 7 digits

  identify(phonebook, 6463339922);
  identify(phonebook, 69696969);
  identify(phonebook, 777777777777);
  identify(phonebook, 887776);
}

/*
Vector Big O Notation: 

Constructing the phone book 0(n) -> n = the size of the phonebook, as the size increases, the time to construct it increases linearly
Adding values to phone book 0(1) -> This is 0[1] because it is only replacing one value
Identifying values in phonebook 0(1) -> Again this is finding the position 

Total Memory = 0(4*N) where N = length of phone number

When extended to a 7 or 10 digit number the run time for Constructing a phone book increases and the total memory can double
the current memory needed for a 4 digit number

-----------------------------------------------------------------------------------------------------------------------------------------
Map Big O Notation:

    Adding Function - 
Depending on the type of insert it can be different, but in the code above inserting a pair is typically 0log(n)
n = size of map 

    Identifying Function -
Since the map is unsorted in this program, the best case would be 0(1) 
The worse case would be 0(log(n)) where n = number of elements. Since maps store info as a binary tree, the time
complexity would be relatively low even for large maps

Total memory = 0(4*N) similar to vector
Unlike vectors we would be using less memory when storing numbers of different sizes. For vectors we need to 
allocate a certain amount of memory based on the size of the biggest phone number. This can waste alot of space
if we are storing a bunch of smaller numbers. Maps on the other hand will allocate memory based on the size of the
individual number. This way less memory is wasted. 


*/