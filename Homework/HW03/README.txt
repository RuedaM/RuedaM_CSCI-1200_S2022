HOMEWORK 3: CONNECT FOUR


NAME: Rueda, Maximillian


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

People:
- Rajgopal, Jayaram, '25
- Paul, Nathan, '25
- Chen, Ivan, '25
- Oren, Itamar, '25
- Fausto, Tony, '25
- Hoang, Yen, '25
- Emil-Georgiev, Peter, '25
- Thomas, Abin, '25
Websites:
- https://www.youtube.com/watch?v=YpNCBw-cPWw
- 
- 

Remember: Your implementation for this assignment must be done on your
own, as described in the "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  36.25hrs.

ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

insert (excluding checking for connected four)
O(n + n^2 + n)
- n is length of new larger array temp_m_data
- n^2 is length of original array m_data AND the lengths of each column
- n is length of original array m_data

insert (including checking for connected four)
O(n + n^2 + n + n^2 + n)
- n is length of new larger array temp_m_data
- n^2 is length of original array m_data AND the lengths of each column
- n is length of original array m_data
- n^2 is length of array m_data AND the lengths of each column
- n is length of array m_data

numTokensInColum
O(1)

numTokensInRow
O(n)
- n is length of array m_data

numColumns
O(1)

numRows
O(n)
- n is length of array m_data

print
O(n)
- n is length of array m_data

clear
O(n^2)
- n^2 is number of rows AND the length of array m_data


TESTING & DEBUGGING STRATEGY: 
Most of my debugging comes from outputting to the console and manually checking the values of variables or seeing
 if code reaches a certain place with some cout output flag.

For memory debugging, I used Dr. Memory to keep track of memory leaks in the heap, being sure to include -g in the
 compilation line to know where in th code possible memory leaks may be.

 I tried testing the extremes by adding tokens to the farthest right possible and adding on top of the same column
  All other tests are clearly defined in connect_four_main.cpp


MISC. COMMENTS TO GRADER:

