/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Homework/HW10
*/

#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>


// defined in performance.cpp
void usage();


template <class T>
void hash_table_remove_duplicates(std::istream &istr, std::ostream &ostr, int &output_count, int &input_count) { 
  // don't reorder the elements, no need for pairwise comparisons or other operations
  typename std::unordered_map<T, int> ht;
  T s;
  input_count = 0;
  output_count = 0;
  while (istr >> s) {
    // If entry is not in map, print
    if (ht.count(s)<1) {
      ostr<<s<<std::endl;
    }
    ++ht[s];
    ++output_count;
    ++input_count;
  }
}


template <class T>
void hash_table_mode(const std::unordered_map<T, int> &ht, std::ostream &ostr, int &output_count) {
  // Cannot sort a hash table
  // keep track of iterator into the structure
  typename std::unordered_map<T, int>::const_iterator it = ht.begin();
  T mode = (*it).first;
  int mode_count = (*it).second;
  ++it;
  for ( ; it!=ht.end() ; ++it) {
    if ((*it).second>=mode_count) {
      mode = (*it).first;
      mode = (*it).first;
      mode_count = (*it).second;
    }
  }
  // save the mode to the output vector
  output_count = 1;
  ostr << mode << "\n";
}


void hash_table_test(const std::string &operation, const std::string &type,
                     std::istream &istr, std::ostream &ostr,
                     int &input_count, int &output_count, int optional_arg) {

  // HINT: For the string element type, declare your hash table like this:
  // std::unordered_set<std::string> ht;
  // OR 
  // std::unordered_map<std::string,int> ht;
  if (type == "string") {

    if (operation == "remove_duplicates") { hash_table_remove_duplicates<std::string> (istr,ostr,output_count, input_count); return;}

    // load the data into a hash table of strings
    std::unordered_map<std::string,int> ht;
    std::string s;
    input_count = 0;
    while (istr >> s) {
      ++ht[s];
      ++input_count;
    }
    if (operation == "mode")              { hash_table_mode              (ht,ostr,output_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }

  else {
    assert (type == "integer");

    if (operation == "remove_duplicates") { hash_table_remove_duplicates<int> (istr,ostr,output_count, input_count); return;}

    // load the data into a hash table of integers
    std::unordered_map<int,int> ht;
    int v;
    input_count = 0;
    while (istr >> v) {
      ++ht[v];
      ++input_count;
    }
    if (operation == "mode")              { hash_table_mode              (ht,ostr,output_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
}
