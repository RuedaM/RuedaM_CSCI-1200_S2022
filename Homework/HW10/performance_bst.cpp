/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Homework/HW10
*/

#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <map>


// defined in performance.cpp
void usage();


template <class T>
void bst_sort(const std::map<T, int> &mp, std::ostream &ostr, int &output_count) {
  // A BST is already sorted, no need for more operations
  output_count = mp.size();
  typename std::map<T, int>::const_iterator it = mp.begin();
  for ( ; it!=mp.end() ; ++it) {
    for (int i=0 ; i<(*it).second ; ++i) {
      ostr << (*it).first << "\n";
    }
  }
}


template <class T>
void bst_remove_duplicates(std::istream &istr, std::ostream &ostr, int &output_count, int &input_count) {
  // A BST is already sorted, must print in correct order before inserting
  typename std::map<T, int> mp;
    T s;
    input_count = 0;
    output_count = 0;
    while (istr >> s) {
      // If entry is not in map, print
      if (mp.count(s)<1) {
        ostr<<s<<std::endl;
      }
      ++mp[s];
      ++output_count;
      ++input_count;
    }
}


template <class T>
void bst_mode(const std::map<T, int> &mp, std::ostream &ostr, int &output_count) {
  // A BST is already sorted, no need for more operations
  // keep track of iterator into the structure
  typename std::map<T, int>::const_iterator it = mp.begin();
  T mode = (*it).first;
  int mode_count = (*it).second;
  ++it;
  for ( ; it!=mp.end() ; ++it) {
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


// note: closest_pair is only available for integer data (not string data)
void bst_closest_pair(const std::map<int, int> &mp, std::ostream &ostr, int &output_count) {
  assert (mp.size() >= 2);
  // A BST is already sorted, no need for more operations
  output_count = 2;
  std::map<int, int>::const_iterator best_ptr = mp.end();
  std::map<int, int>::const_iterator best_ptr2 = mp.end();
  int best;
  // the two elements with closest value must be next to each other in sorted order
  std::map<int, int>::const_iterator first = mp.begin(); ++first;
  std::map<int, int>::const_iterator second = mp.begin();
  for ( ; first!=mp.end() ; ++first, ++second) {
    int diff = (*first).first-(*second).first;
    if (best_ptr==mp.end() || diff<best) {
      best = diff;
      best_ptr = first;
      best_ptr2 = second;
    }
  }
  // print the two elements
  output_count = 2;
  ostr << (*best_ptr2).first << "\n";
  ostr << (*best_ptr).first << "\n";
}


template <class T>
void bst_first_sorted(const std::map<T, int> &mp, std::ostream &ostr, int &output_count, int optional_arg) {
  assert (optional_arg >= 1);
  assert ((int)mp.size() >= optional_arg);
  // A BST is already sorted, no need for more operations
  output_count = optional_arg;
  typename std::map<T, int>::const_iterator it = mp.begin();
  int ctr = 0;
  for ( ; ctr<output_count ; ++it) {
    for (int i=0 ; i<(*it).second && ctr<output_count ; ++i, ++ctr) {
      ostr << (*it).first << "\n";
    }
  }
}


// note: longest_substring is only available for string data (not integer data)
void bst_longest_substring(const std::map<std::string, int> &mp, std::ostream &ostr, int &output_count) {
  assert (mp.size() >= 2);
  // No need to sort for proper comparison
  std::string result;
  int max_substr_freq = 0;
  std::map<std::string, int>::const_iterator it = mp.begin();
  for ( ; it!=mp.end() ; ++it) {
    for (int j=0 ; j<(int)(*it).first.size() ; ++j) {
      for (int k=(j+1) ; k<=(int)(*it).first.size() ; ++k) {
        int substr_freq = 0;
        std::string substr = (*it).first.substr(j, k);
        if (substr.length()>1) {
          std::map<std::string, int>::const_iterator it2 = mp.begin();
          for ( ; it2!=mp.end() ; ++it2) {
            if ((*it2).first.find(substr)!=std::string::npos) {++substr_freq;}
          }
        }
        if (max_substr_freq<=substr_freq && result.length()<substr.length()) {
          result = substr;
          max_substr_freq = substr_freq;
        }
      }
    }
  }
  output_count = 1;
  ostr<<result<<std::endl;
}


void bst_test(const std::string &operation, const std::string &type,
              std::istream &istr, std::ostream &ostr,
              int &input_count, int &output_count, int optional_arg) {

  if (type == "string") {

    if (operation == "remove_duplicates") { bst_remove_duplicates<std::string> (istr,ostr,output_count, input_count); return;}

    // load the data into a list of strings
    std::map<std::string, int> mp;
    std::string s;
    input_count = 0;
    while (istr >> s) {
      ++mp[s];
      input_count++;
    }
    if      (operation == "sort")              { bst_sort              (mp,ostr,output_count); }
    else if (operation == "mode")              { bst_mode              (mp,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { bst_first_sorted      (mp,ostr,output_count,optional_arg); }
    else if (operation == "longest_substring") { bst_longest_substring (mp,ostr,output_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }

  else {
    assert (type == "integer");

    if (operation == "remove_duplicates") { bst_remove_duplicates<int> (istr,ostr,output_count, input_count);  return;}

    // load the data into a list of integers
    std::map<int, int> mp;
    int v;
    input_count = 0;
    while (istr >> v) {
      ++mp[v];
      input_count++;
    }
    if      (operation == "sort")              { bst_sort              (mp,ostr,output_count); }
    else if (operation == "mode")              { bst_mode              (mp,ostr,output_count); }
    else if (operation == "closest_pair")      { bst_closest_pair      (mp,ostr,output_count); }
    else if (operation == "first_sorted")      { bst_first_sorted      (mp,ostr,output_count,optional_arg); }
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
}
