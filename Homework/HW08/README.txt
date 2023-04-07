HOMEWORK 8: ROPES


NAME:  Rueda, Maximillian


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

People:
- Chen, Ivan, '25
- He, Daniel, '25
- Jacobs, Brianna, '25
- Rajgopal, Jayaram, '25
- Oren, Itamar, '25
- ALAC Mentor
Websites:
- 
- 
- 

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  30.25hrs.

BALANCED/WORST CASE RUNNIG TIME ANALYSIS:
n = characters in the string of the current Rope (*this)
m = characters in the string of the Rope passed in (for functions that take
    a second rope)
v = longest "value" of a leaf
p = longest path from root to a leaf
Using these variables, state and explain the big-O running time of each 
of the following operations two ways: 1) with a balanced Rope, 2) with an 
extremely unbalanced Rope. Explain what you considered an extremely 
unbalanced rope for the string "Hello my name is Simon".

Copy Constructor:
Balanced: O(log(n)) - must iterate through every node to fully copy
Unbalanced: O(log(p)) - must iterate down long, single path

Construct from Node*:
Balanced: O(log(n)) - must iterate through every node to fully copy and assign
Unbalanced: O(log(p)) - must iterate down long, single path

Index:
Balanced: O(1) - simply going down pointers ang getting an index
Unbalanced: O(v+p) - not only go down whole long path but also must iterate through very long string in leaf

Report:
Balanced: O(n) - must iterate through certain range of characters in string
Unbalanced: O(v+p) - longest string must be indexed and must travel longest path again

iterator operator++:
Balanced: O(log(n)) - navigating entire tree up and down, so log(n) by convention
Unbalanced: O(log(p)) - navigating entire long chain up and down, so log(p)

Split:
Balanced: O(n) - regular ability to concat even-sized strings
Unbalanced: O(log(p)+p) - must go down logest string to copy and concat

Concat:
Balanced: O(1) - simply combining ropes by reassigning pointers
Unbalanced: O(log(m+p)) - must combine longest possible path and smallest possible path to form new rope


TESTING & DEBUGGING STRATEGY: 
Briefly describe the tests in your StudentTests() function.
How did you test the "corner cases" of your implementation?
Print statements throughout and use of gdb


MISC. COMMENTS TO GRADER:  
Split is very close to working, but memory issue - I have commented it out to gain autograder points

