/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Labs/Lab09
g++ -g -Wall -std=c++11 phonebook.cpp -o phonebook.out
./phonebook.out
~/DrMemory-Linux-2.4.0-2/bin64/drmemory -brief -- phonebook.out
*/

// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// add a number, name pair to the phonebook
void add(vector<string> &phonebook, int number, string const& name) {
  phonebook[number] = name;
}

// given a phone number, determine who is calling
void identify(const vector<string> & phonebook, int number) {
  if (phonebook[number] == "UNASSIGNED") 
    cout << "unknown caller!" << endl;
  else 
    cout << phonebook[number] << " is calling!" << endl;
}


int main() {
  // create the phonebook; initially all numbers are unassigned
  vector<string> phonebook(10000, "UNASSIGNED");

  // add several names to the phonebook
  add(phonebook, 1111, "fred");
  add(phonebook, 2222, "sally");
  add(phonebook, 3333, "george");

  // test the phonebook
  identify(phonebook, 2222);
  identify(phonebook, 4444);
}


/*
Big O Notation:
Creating vector = O(N) - must go through every index of the vector to place new key-value pairs
Adding to value in vector = O(1) - no cost for single variable change
Identify key = O(1) - no cost for returning a variable
Total memory = O(4N) = O(N) - memory defined as number of phone numbers in vector currently (N)

As more, larger numbers are added, more memory is used and runtime grows larger
*/