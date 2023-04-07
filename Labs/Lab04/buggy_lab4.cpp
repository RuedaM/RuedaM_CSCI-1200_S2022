/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Labs/Lab04
~/DrMemory-Linux-2.4.0-2/bin64/drmemory -brief -- [.out file]
*/

#include <iostream>
#include <fstream>

#define MAX_ARRAY_SIZE 50



/** IMPORTANT: SOLUTIONS THAT DO NOT FOLLOW BELOW INSTRUCTIONS WILL RECEIVE NO CREDIT
 * Do not add or modify code in this file UNLESS ASKED TO! 
 * You are NOT allowed to declare new variables; use the ones already declared.
 * You are NOT allowed to create new helper functions or modify checkCorrectSmallest()
**/



/** DO NOT MODIFY THIS FUNCTION! **/
int checkCorrectSmallest(int* smallestNum, const std::string& filename) {
    if (filename == "first.txt" || filename == "middle.txt") {
        if (*smallestNum != 1) {return -1;}
    }

    else if (filename == "last.txt") {
        if (*smallestNum != 22) {return -1;}
    }

    return 1;
}

/** A function that will identify the mean and smallest number
  * in a set of data provided that there are at most 50 numbers 
  * in the file.
  *
  * @param filename: The name of a file that contains a list of numbers.
  *
  * Task: Add or modify code in the appropriate sections to fix memory and logic errors
  * without using data structures (such as an array or vector) and without using any
  * additional memory on the stack.
**/

void identifyMeanAndMin(const std::string& filename) {
   int* numElements;
   int* sum;
   int* smallestNum;
   float* avg;

   /** PART 1: ADD CODE BELOW **/
   numElements = new int;               // Pointed all pointers to ints/floats in the heap so that they have somewhere to go
   sum = new int;
   smallestNum = new int;
   avg = new float;
   /** PART 1: ADD CODE ABOVE **/

   *numElements = 0;
   *sum = 0;

   int readInt;
   int* intArray = new int[MAX_ARRAY_SIZE];
   std::ifstream input(filename);

   while (input >> readInt) {
       *(intArray + *numElements) = readInt;    // "The value of readInt will be stored in intArray at numElements index"
       *numElements += 1;
   }

   std::cout << "Printing the contents of the array in reverse order:  ";

   /** PART 2: MODIFY CODE BELOW **/

   for (int i = *numElements-1; i > -1; i--) {                                  // changed counter so that it counts only as many numbers as there are
       // If we're at the beginning of the for loop, initalize *smallestNum         // also changed looping boolean
       // Else, compare *smallestNum to current element in the for loop
       if (i+1 == *numElements) {                                               // changed to i+1 since i counts index
           *smallestNum = *(intArray + i);                                          // als changed equivalence: numElements is the most # of elements
       }

       else {
           if (*smallestNum > *(intArray + i)) {
               *smallestNum = *(intArray + i);
	   	   }
       }

   /** PART 2: MODIFY CODE ABOVE **/

       *sum += *(intArray + i);
       std::cout << *(intArray + i) << " ";
   }
 
   std::cout << std::endl;
   if (checkCorrectSmallest(smallestNum, filename) == -1) {
       std::cout << "ERROR: incorrect value for smallest number" << std::endl;
       return;
   }

   *avg = *sum / float(*numElements);
   std::cout << "The average for the set of numbers in " << filename << " is "
	     << *avg << " and the smallest number is " << *smallestNum
	     << std::endl;

   /** PART 3: ADD AND/OR MODIFY CODE BELOW **/

   delete [] intArray;                              // added square brackets since it's an array
   delete numElements;                              // deleted other pointers which deletes dynamic memory variables
   delete sum;
   delete smallestNum;
   delete avg;

   /** PART 3: ADD AND/OR MODIFY CODE ABOVE **/
}

int main() {
   identifyMeanAndMin("first.txt");
   std::cout << std::endl;

   identifyMeanAndMin("middle.txt");
   std::cout << std::endl;

   identifyMeanAndMin("last.txt");
   return 0;
}


/*

1. How does the output from your memory debugger differ when you compile your program with the -g
flag compared to when you leave it out?
ANSWER:
Without -g, Dr Memory will nt be able to give line number information and cannot pinpoint where in the file memory is leaking

2. How would you rewrite the for loop in part 2 to use the bracket [] operator instead of pointer syntax?
ANSWER:
for (int i = *numElements-1; i > -1; i--) {                                  // changed counter so that it counts only as many numbers as there are
       // If we're at the beginning of the for loop, initalize *smallestNum         // also changed looping boolean
       // Else, compare *smallestNum to current element in the for loop
       if (i+1 == *numElements) {                                               // changed to i+1 since i counts index
           *smallestNum = intArray[i];                                          // als changed equivalence: numElements is the most # of elements
       }

       else {
           if (*smallestNum > intArray[i]) {
               *smallestNum = intArray[i]);

3. For DrMemory users, you would’ve encountered all of these errors in parts 1, 2, or 3 of Checkpoint 2:
UNITIALIZED READ
UNADDRESSABLE ACCESS
INVALID HEAP ARGUMENT
LEAK
What do you think each of these errors mean?
ANSWER:
Uninitialized Read: A memory address exists, but there is no value within it
Unaddressable Access: Tryig to read a memory address that has not been allocated
Invalid Heap Argument: The heap memory address is invalid - may not exist/incorrect address
Leak: There is a possible leak, most likely due to a pointer mismatch that leaves a heap variable not attached to a pointer

*/