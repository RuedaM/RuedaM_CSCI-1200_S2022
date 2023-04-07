HOMEWORK 9: IMDB SEARCH


NAME:  Rueda, Maximillian


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

People:
- Chen, Ivan, '25
- Jacobs, Brianna, '25
- He, Daniel, '25
- Fung, Benson, '25
- Mentor Bao
- Mentor Liam
- TA Steven
Websites:
- https://www.tutorialspoint.com/cplusplus-program-to-generate-all-possible-combinations-out-of-a-b-c-d-e
- 
- 

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  21.5hrs.


HASH FUNCTION DESCRIPTION
The hash function I used was taken from class, which was taken from http://www.partow.net/programming/hashfunctions/
The hash function is a good general use function for rturning hash values from strings of various sizes
For every letter in the given string, an operation is done to a hard-coded hash integer to ensure that all strings passed through the
 function will be uniformly distributed as a large int value





MISC. COMMENTS TO GRADER:  
Using the same method of getting info from the hash table's lists (list of MOVIE_DATA*) in find() will return junk characters and
 apparently the memory location of the compiler (which I'm told should not be possible?) My data in the table is stored exactly as
 it shuld (I think), so I am confused as to why the same code in insert() does not work in find() (lok to Lines 95 and 107-108 in
 HW9_ds_hashset.h)





PROCESS:
PROVIDING INPUT:

STORING MOVIE DATA:
- Movies should be classes that have associated information


STORING ACTOR DATA:
- Can be stored in map (would e much easier, plus allowed by assignment)
- Iterate through file, every 1st word is key, every 2nd word is actual name - should be used for printing

GETTING QUERY KEY USING HASH FUNCTION:
- When searching for a movie, several strings will be given at a time. Using this info, we should return a list of movies
- Take all strings, combine them into a large string that will be put through the given hash function, which will retun a viable key
	- NOT ONLY THAT, BUT ALL POSSIBLE COMBOS OF ALL STRINGS MUST BE PUT IN AS SEPARATE KEYS: A, B, C -> A, B, C, AB, BC, AC, ABC
- Using newfound key(s), add to/call hash table. Since all variations of key combo are inputted, run time will remain O(1)

