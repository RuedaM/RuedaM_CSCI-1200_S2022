/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Homework/HW10
*/

#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>

// typedef std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string> > PQ_Str_Type;
// typedef std::priority_queue<std::string, std::vector<int>, std::greater<int> > PQ_Int_Type;
// typedef typename std::priority_queue<std::string, std::vector<T>, std::greater<T> > PQ_T_Type;


// defined in performance.cpp
void usage();


template <class T>
void queue_sort(std::priority_queue<std::string, std::vector<T>, std::greater<T> > pq, std::ostream &ostr, int &output_count) {
  // A PQ is already sorted, no need for more operations
  output_count = pq.size();
  for (int i=0 ; i<output_count; ++i) {
    ostr << pq.top() << "\n";
    pq.pop();
  }
}


template <class T>
void queue_mode(std::priority_queue<std::string, std::vector<T>, std::greater<T> > pq,
                std::ostream &ostr, int &output_count) {
  // A PQ is already sorted, no need for more operations
  int current_count = 1;
  T mode;
  int mode_count = 0;
  // keep track of two values in the structure
  T previous = pq.top();
  pq.pop();
  T current = pq.top();
  for (int i=0 ; i<(int)pq.size() ; ++i) {
    if (current==previous) {
      // if they are the same element increment the count
      current_count++;
    }
    else if (current_count>=mode_count) {
      // found a new mode!
      mode = previous;
      mode_count = current_count;
      current_count = 1;
    }
    else {
      current_count = 1;
    }
    previous = pq.top();
    pq.pop();
    current = pq.top();
  }
  if (current_count >= mode_count) {
    // last entry is a new mode!
    mode = previous;
    mode_count = current_count;
  }
  // save the mode to the output vector
  output_count = 1;
  ostr << mode << "\n";
}


// note: closest_pair is only available for integer data (not string data)
void queue_closest_pair(std::priority_queue<std::string, std::vector<int>, std::greater<int> > pq,
                        std::ostream &ostr, int &output_count) {
  assert (pq.size() >= 2);
  // A PQ is already sorted, no need for more operations
  output_count = 2;
  int best = 1000, final_previous, final_current, limit = pq.size();
  int previous = pq.top(); pq.pop();
  int current = pq.top();
  // the two elements with closest value must be next to each other in sorted order
  for (int i=0; i<limit; ++i) {
    if (current==previous) {
      previous = pq.top(); pq.pop();
      current = pq.top();
      continue;
    }
    int diff = current-previous;
    if (diff<=best) {
      best = diff;
      final_previous = previous;
      final_current = current;
    }
    previous = pq.top(); pq.pop();
    current = pq.top();
  }
  // print the two elements
  output_count = 2;
  ostr << final_previous << "\n";
  ostr << final_current << "\n";
}


template <class T>
void queue_first_sorted(std::priority_queue<std::string, std::vector<T>, std::greater<T> > pq,
                        std::ostream &ostr, int &output_count, int optional_arg) {
  assert (optional_arg >= 1);
  assert ((int)pq.size() >= optional_arg);
  // A PQ is already sorted, no need for more operations
  output_count = optional_arg;
  for (int i=0 ; i<output_count ; ++i) {
    ostr << pq.top() << "\n";
    pq.pop();
  }
}


void priority_queue_test(const std::string &operation, const std::string &type,
                         std::istream &istr, std::ostream &ostr,
                         int &input_count, int &output_count, int optional_arg) {

  // HINT: For the string element type, declare your priority_queue like this:
  // std::priority_queue<std::string,std::vector<std::string> > pq;
  // (this will make a "max" priority queue, with big values at the top)
  // OR
  // std::priority_queue<std::string,std::vector<std::string>, std::greater<std::string> > pq;
  // (this will make a "min" priority queue, with big values at the bottom)

  if (type == "string") {

    // load the data into a vector of strings
    std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string> > pq;
    std::string s;
    input_count = 0;
    while (istr >> s) {
      pq.push(s);
      input_count++;
    }
    if      (operation == "sort")              { queue_sort              (pq,ostr,output_count); }
    else if (operation == "mode")              { queue_mode              (pq,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { queue_first_sorted      (pq,ostr,output_count,optional_arg); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }

  else {
    assert (type == "integer");

    // load the data into a vector of integers
    std::priority_queue<std::string, std::vector<int>, std::greater<int> > pq;
    int v;
    input_count = 0;
    while (istr >> v) {
      pq.push(v);
      input_count++;
    }
    if      (operation == "sort")              { queue_sort              (pq,ostr,output_count); }
    else if (operation == "mode")              { queue_mode              (pq,ostr,output_count); }
    else if (operation == "closest_pair")      { queue_closest_pair      (pq,ostr,output_count); }
    else if (operation == "first_sorted")      { queue_first_sorted      (pq,ostr,output_count,optional_arg); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
}
