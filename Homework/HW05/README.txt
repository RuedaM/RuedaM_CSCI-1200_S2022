HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  Rueda, Maximillian


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

People:
- Chen, Ivan, '25
- He, Daniel, '25
- Rajgopal, Jayaram, '25
- Oren, Itamar, '25
- Pile, Joshua, '25
- Fung, Benson, '25
Websites:
- 
- 
- 

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  30hrs.



TESTING & DEBUGGING STRATEGY:
My own testing code is quite simple while builidng up in complexity,
	going through all basic operations in all cases one at a time
	in detail
For debugging, a combination of cout statements and gdb and Dr. Memory
	were used for logic and memory errors respectively
Peers suggested certain test cases for a more well-rounded testing



ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case?

operator*() - O(1)
getOffset() - O(1)
operator++() - O(1)
operator==() - O(1)
operator!=() - O(1)
begin() - O(1)
end() - O(1)
front() - O(1)
back() - O(1)
size() - O(1)
print() - O(n^2) where n^2 is the sizes of each node's array
push_front() - O(n) where n is the size of the affected node
pop_front() - O(n + n) where both n's are the size of the affected node
push_back() - O(1)
pop_back() - O(1)
insert() - O(n + n) where n is the total length of the node array and n is the length of the array from the offset to the end of the array
erase() - O(n) where n is the length of the array from the offset to the end of the array
copy_list() - O(n + n^2) where n is the size of a node array and n^2 is the sizes of the arrays of each following node
destroy_list() - O(n) where n is the length of the list

UnrolledLL uses up more memory than  the dslist or the STL list since it holds larger data structures (arrays) rather than storing a
	single value in a node like what dslist and STL list do

In the worst case, the UnrolledLL will have a memory usage of O(n) where n is the number of full nodes/arrays in use

A case where UnrolledLL would be inefficient would be a case of sorting. For example, let's say hundreds of random ints were stored in
	the list. Sorting all of these values would not be the best. In this case, a vector with random-access indices would be better
The average number of elements would be very close to six if the whole list is full.


EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.



MISC. COMMENTS TO GRADER:  
For optimal viewing, please set indentation/tab width to 4 spaces