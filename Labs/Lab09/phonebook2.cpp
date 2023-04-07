/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Labs/Lab09
g++ -g -Wall -std=c++11 phonebook2.cpp -o phonebook2.out
./phonebook2.out
~/DrMemory-Linux-2.4.0-2/bin64/drmemory -brief -- phonebook2.out
*/

// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

// add a number, name pair to the phonebook
void add(map<int, string> &phonebook, int number, string const& name) {
  phonebook.insert(pair<int,string>(number, name));
}

// given a phone number, determine who is calling
void identify(const map<int, string> & phonebook, long int number) {
    map<int, string>::const_iterator mItr; 
    // If the number can not be found, print unknown caller
    if (phonebook.find(number) == phonebook.end()) {
        cout << "unknown caller!" << endl;
    }
    else { //If it can be found
        mItr = phonebook.find(number);
        cout << mItr->second << " is calling!" << endl; 
    }
    
}


int main() {
  map<int, string> phonebook;

  // add several names to the phonebook
  add(phonebook, 1111, "fred");
  add(phonebook, 2222, "sally");
  add(phonebook, 3333, "george");

  // test the phonebook
  identify(phonebook, 2222);
  identify(phonebook, 4444);

  cout<<endl;
  cout<<endl;

  add(phonebook, 2315, "Tom");
  add(phonebook, 90011009, "Dick");
  add(phonebook, 4158675309, "Jenny");

  identify(phonebook, 90011008);
  identify(phonebook, 2222);
  identify(phonebook, 1234567890);
  identify(phonebook, 2315);
  identify(phonebook, 4158675309);
}


/*
Big O Notation:
Adding to value in map = O(log(n)) - standard for insert() for map
Identify key = O(log(n)) - standard for find() for map()
Total memory = O(n) - memory defined as number of phone numbers in map currently, BUT DIFFERENT
                      Rather than having to allocate memory based on the size of the number, a map
                      can store an entre large number as one key
*/