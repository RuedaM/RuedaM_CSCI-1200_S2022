#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;

public:
  priority_queue() {}

  priority_queue( std::vector<T> const& values )
  {
    for (int i=0 ; i<values.size() ; ++i) {push(values[i]);}
  }

  const T& top() const 
  {
    assert( !m_heap.empty() );
    return m_heap[0];
  }

  void push( const T& entry )
  {
    // COMPLETE IMPLEMENTATION
    m_heap.push_back(entry);
    // Loop through the heap starting from the back (percolate_up?)
    /*
    // IS ACTUALLY RUN TIME O(n)
    for (int i=m_heap.size()-1 ; i>=0; --i) {
        // Check if index
        // The following gets the parent node
        // Check to make sure we don't access value that doesn't exist if vector too small
        if (((i-1)/2)>=0) {
            // If heap smaller than parent node, swap child + parent value
            if (m_heap[i]<m_heap[(i-1)/2]) {
                std::swap(m_heap[i], m_heap[(i-1)/2]);
            }
        }
    }
    */
    int i=0;
    while (((i-1)/2)>=0) {
      if (m_heap[i] < m_heap[(i-1)/2]) {
         std::swap(m_heap[i], m_heap[(i-1)/2]); // value and other non-pointer member vars
         ++i;
      }
      else {break;}
    }

    // Run Time: O(log(n)) - must go through every level of "tree," so log(n) for "tree" navigation
  }

  void pop() 
  {
    assert( !m_heap.empty() );

    // Delete last "leaf" node
    m_heap[0] = m_heap[m_heap.size()-1];
    m_heap.resize(m_heap.size() - 1);

    // Start at root - set the parent and child = 0
    int parent = 0, child = 0; 
    // Implementing percolate down, we want to start from the top of the tree and go the tree
    while (((2*parent)+1)<m_heap.size()) {
      // Choose child to compare against
      // Least vlaue is set that as child 
      // right_child<heap_size && right_child_value<left_child_value 
      if (((2*parent)+2)<m_heap.size() && m_heap[(2*parent)+2]<m_heap[(2*parent)+1]) {
          // Child = right_child
          child = (2*parent)+2;
      } else {
          // Child = left_child
          child = (2*parent)+1;
      }
      // If child value is less than the parent value
      if (m_heap[child] < m_heap[parent]) {
          // Swap their positions 
          std::swap(m_heap[child],  m_heap[parent]);
          parent = child; 
      }
      else {break;}
    }
  }

  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }


  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap()
  {
    return this->check_heap( this->m_heap );
  }

  //  Check an external vector to see that the heap property is realized.
  bool check_heap( const std::vector<T>& heap )
  {
    // Set bools to check if right/left children are valid
    for(int i=0 ; i<heap.size() ; ++i) {
        // Check every left child existance + if less than parent
        if (((2*i)+1)<heap.size()) {
            if (heap[(2*i)+1]<heap[i]) { // (heap[i] is parent)
                return false;
            }
        } 
        // Check right child existance + if less than parent
        if (((2*i)+2)<heap.size()) {
            if (heap[(2*i)+2]<heap[i]) {
                return false;  
            }
        }
    }
    return true;

    // Run Time: O(n) - must check everything in vector
  }

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap( std::ostream & ostr )
  {
    for ( unsigned int i=0; i<m_heap.size(); ++i )
      ostr << i << ": " << m_heap[i] << std::endl;
  }
  
};


template <class T>
void heap_sort(std::vector<T>& v)
{
  int heap_size = 0;
  // Using Percolate up, reverse order of current vector 
  while (heap_size!=v.size()) {
      if (heap_size!=0) {
          int current = heap_size;
          // Swap values
          while (current!=0) {
              // First, find parent position
              int parent = (current-1)/2;
              // If value of parent less than that of current position...
              if(v[parent]<v[current]) {
                  // Swap values (result in max heap?)
                  T tmp = v[parent];
                  v[parent] = v[current];
                  v[current] = tmp; 
              }
              current = parent; 
          }
      }
      heap_size++; 
  }
  
  // In-place sorting 
  int vec_size = v.size();
  while ((vec_size-1)>=0) {
    // Swap the ith element with the vec_size - 1th element 
    T tmp = v[vec_size-1];
    v[vec_size-1] = v[0];
    v[0] = tmp;
    --vec_size; 

    // Using percolate down, sort everything in order (least-->greatest)
    int parent = 0, child = 0;
    while (((2*parent)+1)<vec_size) {
      if (((2*parent)+2)<vec_size && v[(2*parent)+2]>v[(2*parent)+1]) {
        child = (2*parent)+2;
      }
      else {child = (2*parent)+1;}

      if (v[child]>v[parent]) {
          std::swap(v[child], v[parent]);
          parent = child;
      }
      else {break;}
    }
  }

  // Run Time: O(nlog(n))
}

#endif