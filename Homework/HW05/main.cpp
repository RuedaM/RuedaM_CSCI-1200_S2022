/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Homework/HW05
g++ -g -Wall -std=c++11 -o main.out *.cpp
./main.out
~/DrMemory-Linux-2.4.0-2/bin64/drmemory -brief -- main.out
*/


//
// NOTE: YOUR FINAL SUBMITTED VERSION SHOULD ONLY CONTAIN 
//       CHANGES TO MoreTests()
//

#include <iostream>
#include <cmath>
#include <cassert>
#include <list>

#include "unrolled.h"

// ===================================================================
// This function compares an unrolled linked list to an STL list.  It
// returns true iff the lists are the same size, and contain the same
// elements in the same order.
template <class T>
bool SAME(UnrolledLL<T>& a, std::list<T> &b) { 
  if (a.size() != b.size()) return false;
  typename UnrolledLL<T>::iterator a_iter = a.begin();
  typename std::list<T>::iterator b_iter = b.begin();
  while (a_iter != a.end() && b_iter != b.end()) {
    if (*a_iter != *b_iter) return false;
    a_iter++;
    b_iter++;
  }
  assert (a_iter == a.end() && b_iter == b.end()); 
  return true;
}


// ===================================================================
void BasicTests();
void MoreTests();

int main() {
  BasicTests();
  MoreTests();
  std::cout << "Finished MoreTests()" << std::endl;
}


// ===================================================================
// NOTE: Your internal data structure may be different (& thus print
// differently), depending on how you implement your internal member
// functions.  That's ok!
void BasicTests() {

  // make two matching list of integers, one using an unrolled list,
  // one using an STL list.  They should stay the "SAME" throughout
  // these tests.
  UnrolledLL<int> a;
  std::list<int> b;
  for (int i = 10; i < 30; ++i) {
    a.push_back(i);
    b.push_back(i);
  }  

  // iterate through the integers and print them out
  std::cout << "the integers from 10->29" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    std::cout << " " << *itr;
  }
  std::cout << std::endl << std::endl;
  assert (SAME(a,b));

  // use the output operator to print the underlying representation
  std::cout << "initial" << std::endl;
  a.print(std::cout);
  std::cout << std::endl;

  // testing some basic functions in the class
  std::cout << "some editing with pop & push" << std::endl;
  assert (a.size() == 20);
  assert (a.front() == 10);
  assert (a.back() == 29);
  a.pop_front(); 
  b.pop_front();
  assert (a.size() == 19);
  assert (a.front() == 11);
  a.pop_back();
  b.pop_back();
  assert (a.size() == 18);
  assert (a.back() == 28);
  a.print(std::cout);
  std::cout << std::endl;
  assert (SAME(a,b));

  // more editing
  std::cout << "more editing with pop & push" << std::endl;
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  a.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  b.pop_front();
  a.print(std::cout);
  a.pop_back();
  b.pop_back();
  a.print(std::cout);
  assert (a.size() == 12);
  assert (a.front() == 16);
  assert (a.back() == 27);
  a.push_front(90);
  a.push_front(91);
  a.push_front(92);
  a.push_front(93);
  b.push_front(90);
  b.push_front(91);
  b.push_front(92);
  b.push_front(93);
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 16);
  assert (a.front() == 93);
  assert (SAME(a,b));

  // erase the multiples of 3
  std::cout <<"erase the multiples of 3" << std::endl;
  UnrolledLL<int>::iterator a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter % 3 == 0) {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
  }
  std::list<int>::iterator b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter % 3 == 0) {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 10);
  assert (SAME(a,b));

  // inserting elements
  std::cout << "do some inserts" << std::endl;
  // insert some stuff
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26) {
      itr = a.insert(itr,77);
      itr++;
    } 
  }
  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++) {
    if (*itr == 92 || *itr == 16 || *itr == 19 || *itr == 26) {
      itr = b.insert(itr,77);
      itr++;
    } 
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 14);
  assert (SAME(a,b));
  
  // overflowing an insert
  std::cout << "insert that overflows the node" << std::endl;
  for (UnrolledLL<int>::iterator itr = a.begin(); itr != a.end(); itr++) {
    if (*itr == 17) {
      itr = a.insert(itr,88);
      itr++;
    } 
  }
  for (std::list<int>::iterator itr = b.begin(); itr != b.end(); itr++) {
    if (*itr == 17) {
      itr = b.insert(itr,88);
      itr++;
    } 
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 15);
  assert (SAME(a,b));

  // more erasing
  std::cout << "erasing that removes a node" << std::endl;
  a_iter = a.begin();
  while (a_iter != a.end()) {
    if (*a_iter == 77 || *a_iter == 16 || *a_iter == 88) {
      a_iter = a.erase(a_iter);
    } else {
      a_iter++;
    }
  }
  b_iter = b.begin();
  while (b_iter != b.end()) {
    if (*b_iter == 77 || *b_iter == 16 || *b_iter == 88) {
      b_iter = b.erase(b_iter);
    } else {
      b_iter++;
    }
  }
  a.print(std::cout);
  std::cout << std::endl;
  assert (a.size() == 9);
  assert (SAME(a,b));

}


// ===================================================================
void MoreTests() {

  std::cout<<"TEST 1 - BASIC OPERATIONS:";
  std::cout<<" CREATION, PUSHING POPPING, AND SIZE"<<std::endl;
  std::cout<<std::endl;
  
  UnrolledLL<int> a;
  std::cout<<"~created new list: a"<<std::endl;
  a.print(std::cout);

  //BACK OPERATIONS
  a.push_back(1); a.push_back(3); a.push_back(5);
  std::cout<<"~single-node push_back()'s called:"<<std::endl;
  a.print(std::cout);
  
  a.pop_back();
  std::cout<<"~single-node pop_back() called:"<<std::endl;
  a.print(std::cout);
  
  a.push_back(5); a.push_back(7); a.push_back(9); a.push_back(11);
  std::cout<<"~single-node push_back() to fill node:"<<std::endl;
  a.print(std::cout);
  
  a.push_back(13); a.push_back(15);
  std::cout<<"~multi-node push_back() to start next node:"<<std::endl;
  a.print(std::cout);
  
  a.pop_back();
  std::cout<<"~multi-node pop_back() to delete from next node:"<<std::endl;
  a.print(std::cout);
  
  a.pop_back();
  std::cout<<"~multi-node pop_back() to empty next node:"<<std::endl;
  a.print(std::cout);
  
  std::cout<<std::endl;

  UnrolledLL<int> b;
  std::cout<<"~created new list: b"<<std::endl;
  a.print(std::cout);

  //FRONT OPERATIONS
  b.push_front(1111); b.push_front(99); b.push_front(77);
  std::cout<<"~push_front()'s called:"<<std::endl;
  b.print(std::cout);

  b.pop_front();
  std::cout<<"~pop_front() called:"<<std::endl;
  b.print(std::cout);

  b.push_front(77); b.push_front(55); b.push_front(33); b.push_front(11);
  std::cout<<"~single-node push_front()'s to fill node:"<<std::endl;
  b.print(std::cout);

  b.push_front(1515); b.push_front(1313);
  std::cout<<"~multi-node push_front()'s to start next node:"<<std::endl;
  b.print(std::cout);

  b.pop_front();
  std::cout<<"~multi-node pop_front() to delete from next node:"<<std::endl;
  b.print(std::cout);
  
  b.pop_front();
  std::cout<<"~multi-node pop_front() to empty next node:"<<std::endl;
  b.print(std::cout);

  std::cout<<std::endl;

  std::cout<<"~affirming sizes of previous 2 lists:"<<std::endl;
  std::cout<<"Size of list a: "<<a.size()<<std::endl;
  std::cout<<"Size of list b: "<<b.size()<<std::endl;


  std::cout<<std::endl<<std::endl;


  std::cout<<"TEST 2 - INTERMEDIATE OPERATIONS:";
  std::cout<<" ASSIGNMENT, FRONT+BACK, BEGINNING+END,";
  std::cout<<" AND ITERATOR USAGE"<<std::endl;

  std::cout<<"a:"<<std::endl; a.print(std::cout);
  std::cout<<"b:"<<std::endl; b.print(std::cout);
  b = a;
  std::cout<<"~assignment operator called - b will be a copy of a"<<std::endl;
  std::cout<<"a:"<<std::endl;
  a.print(std::cout);
  std::cout<<"b:"<<std::endl;
  b.print(std::cout);
  
  std::cout<<std::endl;

  UnrolledLL<float> c;
  std::cout<<"~created new list: c"<<std::endl;
  c.print(std::cout);
  for (float i=0.1 ; i<0.9 ; i+=0.1) {c.push_back(i);}
  std::cout<<"~values added to list:"<<std::endl;
  c.print(std::cout);
  
  std::cout<<"front() of above list: "<<c.front()<<std::endl;
  std::cout<<"back() of above list: "<<c.back()<<std::endl;

  std::cout<<std::endl;

  std::cout<<"Boolean result of c.begin()==c.end(): "
           <<(c.begin()==c.end())<<" (0=false ; 1=true)"
           <<std::endl;

  std::cout<<std::endl;

  std::cout<<"~begin(), end(), operator*(), and operator!=() ";
  std::cout<<"used to iterate through list contents:"<<std::endl;
  for (UnrolledLL<float>::iterator itr = c.begin() ; itr!=c.end() ; itr++) {
    std::cout<<" "<<*itr;
  }
  std::cout<<std::endl;
  std::cout<<"~finished iterating"<<std::endl;


  std::cout<<std::endl<<std::endl;


  std::cout<<"TEST 3 - ADVANCED OPERATIONS:";
  std::cout<<" CASES OF ERASE AND INSERT"<<std::endl;

  UnrolledLL<float> d;
  std::cout<<"~created new list: d"<<std::endl;
  d.print(std::cout);
  for (float i=0.01 ; i<=0.2 ; i+=0.01) {d.push_back(i);}
  std::cout<<"~values added to list:"<<std::endl;
  d.print(std::cout);

  // for (UnrolledLL<float>::iterator testitr = d.begin() ; testitr!=d.end() ; testitr++) {
  //   std::cout<<" "<<*testitr<<" "<<typeid(*testitr).name();
  // }
  // std::cout<<std::endl;

  std::cout<<"~attempting to erase 0.02:"<<std::endl;
  UnrolledLL<float>::iterator itr = d.begin();
  for (unsigned int i=0 ; i<d.size() ; i++) {
    if (*itr==float(0.02)) {itr = d.erase(itr);}
    itr++;
  }  
  d.print(std::cout);

  std::cout<<"~attempting to erase all middle node data";
  std::cout<<" (single-elem. head_ deleted too):"<<std::endl;
  UnrolledLL<float>::iterator itr2 = d.begin();
  for (unsigned int i=0 ; i<d.size() ; i++) {
    if (i>=5 && i<=10) {
      itr2 = d.erase(itr2);
      continue;
    }
    itr2++;
  }  
  d.print(std::cout);

  std::cout<<"~attempting to erase all head_ data";
  std::cout<<" (single-elem. head_ deleted too):"<<std::endl;
  UnrolledLL<float>::iterator itr3 = d.begin();
  for (unsigned int i=0 ; i<5 ; i++) {
    itr3 = d.erase(itr3);
    itr3++;
  } 
  d.print(std::cout);

  std::cout<<std::endl;

  UnrolledLL<int> e;
  std::cout<<"~created new list:"<<std::endl;
  e.print(std::cout);
  for (int i=1 ; i<=19 ; i+=1) {e.push_back(i);}
  std::cout<<"~values added to list:"<<std::endl;
  e.print(std::cout);

  std::cout<<"~attempting to erase all even numbers:"<<std::endl;
  UnrolledLL<int>::iterator itr4 = e.begin();
  for ( ; itr4!=e.end() ; itr4++) {
    //std::cout<<"entered for: "<<*itr4<<std::endl;
    //std::cout<<"*itr4%2==0: "<<(*itr4%2==0)<<std::endl;
    if (*itr4%2==0) {
      itr4 = e.erase(itr4);
      continue;
    }
  } 
  e.print(std::cout);

  std::cout<<std::endl;

  /*
  std::cout<<"Attempting to erase 0.19 (single-elem. tail_):"<<std::endl;
  UnrolledLL<float>::iterator itr4 = d.begin();
  for (unsigned int i=0 ; i<d.size() ; i++) {
    std::cout<<"entered: "<<*itr4<<" "<<i<<std::endl;
    if (i==12) {
      std::cout<<"entered if"<<std::endl;
      itr4 = d.erase(itr4);
      continue;
    }
    itr4++;
  }
  std::cout<<"erased"<<std::endl;  
  d.print(std::cout);
  
  std::cout<<std::endl;
  */

  std::cout<<"~attempting to insert 22 between numbers:"<<std::endl;
  for (UnrolledLL<int>::iterator itr5 = e.begin() ; itr5 != e.end() ; itr5++, itr5++) {
    itr5 = e.insert(itr5,22);
  }
  e.print(std::cout);

  

}
