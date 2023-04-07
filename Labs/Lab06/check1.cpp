/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Labs/Lab06
g++ -g -Wall -std=c++11 check1.cpp -o check1.out
./check1.out
~/DrMemory-Linux-2.4.0-2/bin64/drmemory -brief -- check1.out
*/

#include <iostream>
#include <string>


// Note: It's ok that all the member variables are public for this
// tiny class.  We'll build up to a more robust and complete linked
// list implementation in lecture 10.
template <class T>
class Node {
public:
  T value;
  Node<T> *ptr;
};



template <class T>
void print(Node<T> *data, const std::string &label) {
  std::cout << label;
  Node<T> *tmp = data;
  while (tmp != NULL) {
    std::cout << " " << tmp->value;
    tmp = tmp->ptr;
  }
  std::cout << std::endl;
}



template <class T>
void reverse(Node<T>* &input) { // input = head ptr to list
  Node<T>* itrP = NULL;
  Node<T>* itrC = input;
  Node<T>* itrN = input->ptr;

  while (itrN!=NULL) {
    itrC->ptr = itrP;
    itrP = itrC;
    itrC = itrN;
    itrN = itrN->ptr;
    input = itrC;
  }
  itrC->ptr = itrP;
}




int main() {

  // manually create a linked list of notes with 4 elements
  Node<int>* my_list = new Node<int>; 
  my_list->value = 1; 
  my_list->ptr = new Node<int>;
  my_list->ptr->value = 2;
  my_list->ptr->ptr = new Node<int>;
  my_list->ptr->ptr->value = 3;
  my_list->ptr->ptr->ptr = new Node<int>;
  my_list->ptr->ptr->ptr->value = 4;
  my_list->ptr->ptr->ptr->ptr = NULL;

  
  print(my_list,"my_list before");
  reverse(my_list);
  print(my_list,"my_list after ");


  // Note: We are not deleting any of the Nodes we created...  so this
  // program has memory leaks!  More on this in Checkpoint 2!

}

// ===========================================================================
