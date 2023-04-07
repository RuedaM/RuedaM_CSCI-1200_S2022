/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Homework/HW10
*/

#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <list>


// defined in performance.cpp
void usage();


template <class T>
void list_sort(std::list<T> &lst, std::ostream &ostr, int &output_count) {
  // use the list sort
  lst.sort();
  output_count = lst.size();
  typename std::list<T>::iterator it = lst.begin();
  for ( ; it!=lst.end() ; ++it)
    ostr << (*it) << "\n";
}


template <class T>
void list_remove_duplicates(const std::list<T> &lst, std::ostream &ostr, int &output_count) {
  // don't reorder the elements, just do all pairwise comparisons
  output_count = 0;
  typename std::list<T>::const_iterator it = lst.begin();
  for ( ; it!=lst.end() ; ++it) {
    bool dup = false;
    typename std::list<T>::const_iterator it2 = lst.begin();
    for ( ; it2!=it ; ++it2) {
      if ((*it2)==(*it)) {
        dup = true;
        break;
      }
    }
    // if it has not already been added to the output list
    if (!dup) {
      ostr << (*it) << "\n";
      output_count++;
    }
  }
}


template <class T>
void list_mode(std::list<T> &lst, std::ostream &ostr, int &output_count) {
  // use the list sort
  lst.sort();
  int current_count = 1;
  T mode;
  int mode_count = 0;
  // keep track of two iterators into the structure
  typename std::list<T>::iterator current = lst.begin(); ++current;
  typename std::list<T>::iterator previous = lst.begin();
  for ( ; current!=lst.end() ; ++current, ++previous) {
    if ((*current)==(*previous)) {
      // if they are the same element increment the count
      current_count++;
    } else if (current_count>=mode_count) {
      // found a new mode!
      mode = *previous;
      mode_count = current_count;
      current_count = 1;
    } else {
      current_count = 1;
    }
  }
  if (current_count >= mode_count) {
    // last entry is a new mode!
    mode = *previous;
    mode_count = current_count;
  }
  // save the mode to the output vector
  output_count = 1;
  ostr << mode << "\n";
}


// note: closest_pair is only available for integer data (not string data)
void list_closest_pair(std::list<int> &lst, std::ostream &ostr, int &output_count) {
  assert (lst.size() >= 2);
  // use the list sort
  lst.sort();
  output_count = 2;
  std::list<int>::iterator best_ptr = lst.end();
  std::list<int>::iterator best_ptr2 = lst.end();
  int best;
  // the two elements with closest value must be next to each other in sorted order
  std::list<int>::iterator first = lst.begin(); ++first;
  std::list<int>::iterator second = lst.begin();
  for ( ; first!=lst.end(); ++first, ++second) {
    int diff = (*first)-(*second);
    if (best_ptr==lst.end() || diff<best) {
      best = diff;
      best_ptr = first;
      best_ptr2 = second;
    }
  }
  // print the two elements
  output_count = 2;
  ostr << (*best_ptr2) << "\n";
  ostr << (*best_ptr) << "\n";
}


template <class T>
void list_first_sorted(std::list<T> &lst, std::ostream &ostr, int &output_count, int optional_arg) {
  assert (optional_arg >= 1);
  assert ((int)lst.size() >= optional_arg);
  // use the list sort
  lst.sort();
  output_count = optional_arg;
  typename std::list<T>::iterator it = lst.begin();
  for (int ctr=0; ctr<optional_arg ; ++it, ++ctr) {
    ostr << (*it) << "\n";
  }
}


// note: longest_substring is only available for string data (not integer data)
void list_longest_substring(std::list<std::string> &lst, std::ostream &ostr, int &output_count) {
  assert (lst.size() >= 2);
  // use the list sort
  lst.sort();
  std::string result;
  int max_substr_freq = 0;
  // Iterate through every word in list
  std::list<std::string>::const_iterator it = lst.begin();
  for ( ; it!=lst.end() ; ++it) {
    // Create substrings with two for-loops
    for (int j=0 ; j<(int)(*it).size() ; ++j) {
      for (int k=(j+1) ; k<=(int)(*it).size() ; ++k) {
        int substr_freq = 0;
        std::string substr = (*it).substr(j, k);
        if (substr.length()>1) {
          // Check if substring exists in any element in list
          std::list<std::string>::const_iterator it2 = lst.begin();
          for ( ; it2!=lst.end() ; ++it2) {
            if ((*it2).find(substr)!=std::string::npos) {++substr_freq;}
            // Note: std::sring::npos is like list.end() - basically NULL for strings
          }
        }
        // If subsring appears more frequently + is longer, make it the new result
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


void list_test(const std::string &operation, const std::string &type,
                 std::istream &istr, std::ostream &ostr,
                 int &input_count, int &output_count, int optional_arg) {

  if (type == "string") {
    // load the data into a list of strings
    std::list<std::string> lst;
    std::string s;
    input_count = 0;
    while (istr >> s) {
      lst.push_back(s);
      input_count++;
    }
    if      (operation == "sort")              { list_sort              (lst,ostr,output_count); }
    else if (operation == "remove_duplicates") { list_remove_duplicates (lst,ostr,output_count); }
    else if (operation == "mode")              { list_mode              (lst,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { list_first_sorted      (lst,ostr,output_count,optional_arg); }
    else if (operation == "longest_substring") { list_longest_substring (lst,ostr,output_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }

  else {
    assert (type == "integer");
    // load the data into a list of integers
    std::list<int> lst;
    int v;
    input_count = 0;
    while (istr >> v) {
      lst.push_back(v);
      input_count++;
    }
    if      (operation == "sort")              { list_sort              (lst,ostr,output_count); }
    else if (operation == "remove_duplicates") { list_remove_duplicates (lst,ostr,output_count); }
    else if (operation == "mode")              { list_mode              (lst,ostr,output_count); }
    else if (operation == "closest_pair")      { list_closest_pair      (lst,ostr,output_count); }
    else if (operation == "first_sorted")      { list_first_sorted      (lst,ostr,output_count,optional_arg); }
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
}
