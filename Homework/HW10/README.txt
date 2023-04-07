HOMEWORK 10:  PERFORMANCE & BIG O NOTATION


NAME:  Rueda, Maximillian


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

People:
- Chen, Ivan, '25
- Rajgopal, Jayaram, '25
- Jacobs, Jason, '25
- Oren, Itamar, '25
- Emil-Georgiev, Peter, '25
- He, Daniel, '25
- Mentor Theodore
- Mentor Ben
Websites:
- https://www.programiz.com/cpp-programming/priority-queue?msclkid=94ab174cc03911eca0984659ccb0ace5
- https://www.cplusplus.com/reference/unordered_map/unordered_map/
- https://www.geeksforgeeks.org/stringnpos-in-c-with-examples/?msclkid=04305b3dc1b211eca1118031a0928d38

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  26.25hrs.


COMPLEXITY ANALYSIS
n = number of elements in the input
f = requested number of values in output (first sorted only)
l = maximum length of any string element

Neatly fill in the table below with the Big O Notation for running time.
O NOTATION TABLE
------------------------------------------------------------------------------
| (TIME)   |          | remove   |          | closest  | first f  | longest  |
| (MEMORY) | sort     | dups     | mode     | pair     | sorted   | substr   |
------------------------------------------------------------------------------
|          |O(nlog(n))|  O(n^2)  |  O(n^2)  |  O(n^2)  |  O(f*n)  |l*logl*n^2|
| vector   |   O(n)   |   O(n)   |   O(n)   |   O(n)   |   O(n)   |   O(l)   |
------------------------------------------------------------------------------
|          |O(nlog(n))|  O(n^2)  |  O(n^2)  |  O(n^2)  |  O(f*n)  |l*logl*n^2|
| list     |   O(n)   |   O(n)   |   O(n)   |   O(n)   |   O(n)   |   O(n)   |
------------------------------------------------------------------------------
|          |O(nlog(n))|O(nlog(n))|O(nlog(n))|  O(n^2)  |O(f*nlogn)|l*logl*n^2|
| bst      |   O(n)   |   O(n)   |   O(n)   |   O(n)   |   O(n)   |   O(n)   |
------------------------------------------------------------------------------
|          |O(nlog(n))|    XX    |  O(n^2)  |O(nlog(n))|O(f*nlogn)|    XX    |
| pq       |   O(n)   |    XX    |   O(n)   |   O(n)   |   O(n)   |    XX    |
------------------------------------------------------------------------------
|          |    XX    |  O(n^2)  |  O(n^2)  |    XX    |    XX    |    XX    |
| hash     |    XX    |   O(n)   |   O(n)   |    XX    |    XX    |    XX    |
------------------------------------------------------------------------------



RESULTS
For each data type and each operation, run several sufficiently large
tests and collect the operation time output by the program. Organize
these timing measurements in your README.txt file and estimate the
coefficients for the dominant term of your Big ‘O’ Notation.
RESULTS TABLE:
------------------------------------------------------------------------------
|(OP. TIME)|          | remove   |          | closest  | first f  | longest  |
|(COEFFS.) | sort     | dups     | mode     | pair     | sorted   | substr   |
------------------------------------------------------------------------------
|          |   0.00   |   0.00   |   0.00   |   0.00   |   0.00   |   0.00   |
| vector   |    02    |    02    |    02    |    02    |    02    |    02    |
------------------------------------------------------------------------------
|          |   0.00   |   0.00   |   0.00   |   0.00   | 0.015625 |   0.00   |
| list     |    02    |    02    |    02    |    02    |    02    |    02    |
------------------------------------------------------------------------------
|          |   0.00   |   0.00   |   0.00   |   0.00   |   0.00   |   0.00   |
| bst      |    02    |    02    |    02    |    02    |    02    |    02    |
------------------------------------------------------------------------------
|          |   0.00   |    XX    |   0.00   |   0.00   |   0.00   |    XX    |
| pq       |    02    |    XX    |    02    |    02    |    02    |    XX    |
------------------------------------------------------------------------------
|          |    XX    |   0.00   | 0.015625 |    XX    |    XX    |    XX    |
| hash     |    XX    |    02    |    02    |    XX    |    XX    |    XX    |
------------------------------------------------------------------------------
*Note: See Comments to Grader for further explanation (why a majority of them are 0)
**Note: See bottom of README.txt for complete list of all commands used to test functions+structures


RESULTS TABLE, MORE COMPREHENSIVE: (from Submitty with added Coefficients of domonant O Notation terms)
Data Structure      Operation         Test Specifications		   Oper. Time     Coeff.
=========================================================================================
vector              sort                10,000 length 5 strings     0.0079 sec     02
vector              sort                50,000 length 5 strings     0.0440 sec     02
vector              sort               100,000 length 5 strings     0.0800 sec     02
vector              sort               500,000 length 5 strings     0.3960 sec     02
vector              remove_dups          5,000 length 3 strings     0.2067 sec     02
vector              remove_dups         10,000 length 3 strings     0.7720 sec     02
vector              remove_dups         20,000 length 3 strings     2.5280 sec     02
vector              remove_dups         50,000 length 3 strings    10.4638 sec     02
vector              mode                10,000 length 4 strings     0.0120 sec     02
vector              mode                50,000 length 4 strings     0.0400 sec     02
vector              mode               100,000 length 4 strings     0.0676 sec     02
vector              mode               500,000 length 4 strings     0.3560 sec     02
vector              closest_pair        10,000 8 digit integers     0.0120 sec     02
vector              closest_pair        50,000 8 digit integers     0.0350 sec     02
vector              closest_pair       100,000 8 digit integers     0.0640 sec     02
vector              closest_pair       500,000 8 digit integers     0.3200 sec     02
vector              first 50 sorted    10,0000 length 4 strings     0.0149 sec     02
vector              first 50 sorted    20,0000 length 4 strings     0.0400 sec     02
vector              first 50 sorted    50,0000 length 4 strings     0.0753 sec     02
vector              first 50 sorted   100,0000 length 4 strings     0.3600 sec     02
vector              longest_substring     500 length 20 strings     0.8472 sec     02
vector              longest_substring   1,000 length 20 strings     3.5752 sec     02
vector              longest_substring   2,000 length 20 strings    15.5797 sec     02
vector              longest_substring   3,000 length 20 strings    NOT IMPLEMENTED 
  
linked list         sort                10,000 length 5 strings     0.0160 sec     02
linked list         sort                50,000 length 5 strings     0.0635 sec     02
linked list         sort               100,000 length 5 strings     0.1200 sec     02
linked list         sort               500,000 length 5 strings     0.7520 sec     02
linked list         remove_dups          5,000 length 3 strings     0.3880 sec     02
linked list         remove_dups         10,000 length 3 strings     1.3160 sec     02
linked list         remove_dups         20,000 length 3 strings     4.3518 sec     02
linked list         remove_dups         50,000 length 3 strings    17.9598 sec     02
linked list         mode                10,000 length 4 strings     0.0160 sec     02
linked list         mode                50,000 length 4 strings     0.0600 sec     02
linked list         mode               100,000 length 4 strings     0.1160 sec     02
linked list         mode               500,000 length 4 strings     0.7474 sec     02
linked list         closest_pair        10,000 8 digit integers     0.0159 sec     02
linked list         closest_pair        50,000 8 digit integers     0.0633 sec     02
linked list         closest_pair       100,000 8 digit integers     0.1120 sec     02
linked list         closest_pair       500,000 8 digit integers     0.5833 sec     02
linked list         first 50 sorted    10,0000 length 4 strings     0.0160 sec     02
linked list         first 50 sorted    20,0000 length 4 strings     0.0640 sec     02
linked list         first 50 sorted    50,0000 length 4 strings     0.1194 sec     02
linked list         first 50 sorted   100,0000 length 4 strings     0.6712 sec     02
linked list         longest_substring     500 length 20 strings     1.4614 sec     02
linked list         longest_substring   1,000 length 20 strings     6.0040 sec     02
linked list         longest_substring   2,000 length 20 strings    24.5917 sec     02
linked list         longest_substring   3,000 length 20 strings    NOT IMPLEMENTED 
  
binary search tree  sort                10,000 length 5 strings     0.0160 sec     02
binary search tree  sort                50,000 length 5 strings     0.0600 sec     02
binary search tree  sort               100,000 length 5 strings     0.1200 sec     02
binary search tree  sort               500,000 length 5 strings     0.8173 sec     02
binary search tree  remove_dups          5,000 length 3 strings     0.0190 sec     02
binary search tree  remove_dups         10,000 length 3 strings     0.0200 sec     02
binary search tree  remove_dups         20,000 length 3 strings     0.0320 sec     02
binary search tree  remove_dups         50,000 length 3 strings     0.0600 sec     02
binary search tree  mode                10,000 length 4 strings     0.0160 sec     02
binary search tree  mode                50,000 length 4 strings     0.0560 sec     02
binary search tree  mode               100,000 length 4 strings     0.1240 sec     02
binary search tree  mode               500,000 length 4 strings     0.5710 sec     02
binary search tree  closest_pair        10,000 8 digit integers     0.0160 sec     02
binary search tree  closest_pair        50,000 8 digit integers     0.0474 sec     02
binary search tree  closest_pair       100,000 8 digit integers     0.1040 sec     02
binary search tree  closest_pair       500,000 8 digit integers     0.6436 sec     02
binary search tree  first 50 sorted    10,0000 length 4 strings     0.0160 sec     02
binary search tree  first 50 sorted    20,0000 length 4 strings     0.0592 sec     02
binary search tree  first 50 sorted    50,0000 length 4 strings     0.1240 sec     02
binary search tree  first 50 sorted   100,0000 length 4 strings     0.6280 sec     02
binary search tree  longest_substring     500 length 20 strings     1.8920 sec     02
binary search tree  longest_substring   1,000 length 20 strings     7.9478 sec     02
binary search tree  longest_substring   2,000 length 20 strings    NOT IMPLEMENTED 
binary search tree  longest_substring   3,000 length 20 strings    NOT IMPLEMENTED 
  
priority queue      sort                10,000 length 5 strings     0.0200 sec     02
priority queue      sort                50,000 length 5 strings     0.0720 sec     02
priority queue      sort               100,000 length 5 strings     0.1480 sec     02
priority queue      sort               500,000 length 5 strings     0.8080 sec     02
priority queue      remove_dups          5,000 length 3 strings    NOT IMPLEMENTED 
priority queue      remove_dups         10,000 length 3 strings    NOT IMPLEMENTED 
priority queue      remove_dups         20,000 length 3 strings    NOT IMPLEMENTED 
priority queue      remove_dups         50,000 length 3 strings    NOT IMPLEMENTED 
priority queue      mode                10,000 length 4 strings     0.0194 sec     02
priority queue      mode                50,000 length 4 strings     0.0520 sec     02
priority queue      mode               100,000 length 4 strings     0.1040 sec     02
priority queue      mode               500,000 length 4 strings     0.5320 sec     02
priority queue      closest_pair        10,000 8 digit integers     0.0191 sec     02
priority queue      closest_pair        50,000 8 digit integers     0.0588 sec     02
priority queue      closest_pair       100,000 8 digit integers     0.1154 sec     02
priority queue      closest_pair       500,000 8 digit integers     0.6000 sec     02
priority queue      first 50 sorted    10,0000 length 4 strings     0.0096 sec     02
priority queue      first 50 sorted    20,0000 length 4 strings     0.0280 sec     02
priority queue      first 50 sorted    50,0000 length 4 strings     0.0512 sec     02
priority queue      first 50 sorted   100,0000 length 4 strings     0.2000 sec     02
priority queue      longest_substring     500 length 20 strings    NOT IMPLEMENTED 
priority queue      longest_substring   1,000 length 20 strings    NOT IMPLEMENTED 
priority queue      longest_substring   2,000 length 20 strings    NOT IMPLEMENTED 
priority queue      longest_substring   3,000 length 20 strings    NOT IMPLEMENTED 
  
hash table          sort                10,000 length 5 strings    NOT IMPLEMENTED 
hash table          sort                50,000 length 5 strings    NOT IMPLEMENTED 
hash table          sort               100,000 length 5 strings    NOT IMPLEMENTED 
hash table          sort               500,000 length 5 strings    NOT IMPLEMENTED 
hash table          remove_dups          5,000 length 3 strings     0.0160 sec     02
hash table          remove_dups         10,000 length 3 strings     0.0152 sec     02
hash table          remove_dups         20,000 length 3 strings     0.0234 sec     02
hash table          remove_dups         50,000 length 3 strings     0.0320 sec     02
hash table          mode                10,000 length 4 strings     0.0150 sec     02
hash table          mode                50,000 length 4 strings     0.0320 sec     02
hash table          mode               100,000 length 4 strings     0.0600 sec     02
hash table          mode               500,000 length 4 strings     0.2800 sec     02
hash table          closest_pair        10,000 8 digit integers    NOT IMPLEMENTED
hash table          closest_pair        50,000 8 digit integers    NOT IMPLEMENTED
hash table          closest_pair       100,000 8 digit integers    NOT IMPLEMENTED
hash table          closest_pair       500,000 8 digit integers    NOT IMPLEMENTED
hash table          first 50 sorted    10,0000 length 4 strings    NOT IMPLEMENTED
hash table          first 50 sorted    20,0000 length 4 strings    NOT IMPLEMENTED
hash table          first 50 sorted    50,0000 length 4 strings    NOT IMPLEMENTED
hash table          first 50 sorted   100,0000 length 4 strings    NOT IMPLEMENTED
hash table          longest_substring     500 length 20 strings    NOT IMPLEMENTED
hash table          longest_substring   1,000 length 20 strings    NOT IMPLEMENTED
hash table          longest_substring   2,000 length 20 strings    NOT IMPLEMENTED
hash table          longest_substring   3,000 length 20 strings    NOT IMPLEMENTED



DISCUSSION
Do these measurements and the overall performance match your predicted
Big ‘O‘ Notation for the data type and operation? Did you update your
initial answers for the Big ‘O‘ Notation of any cell in the table?

Compare the relative coefficients for different data types that have
the same Big ‘O’ Notation for a specific operation. Do these match
your intuition? Are you surprised by any of the results? Will these
results impact your data structure choices for future programming
projects?

Use well-written, complete sentences.  Approximately 250-500 words.  

//
I was correct on some of the entries, but very off for ome others.
For example, I correctly assumed O Notations for both vector and list as they are the easiest to understand and work with.
However, I severely underestimated the runtimes of BSTs, PQs, and HTs.
It had comepletely slipped my mind that since values are sorted, insertion would cost nlog(n).
I also did not expect how taxing finding the longest substring would be, finding that I had to change my prediction of n*l to l*logl*n^2.

Deliberating which structures were feasible for which function was also quite the challege.
Oftentimes in this class I find tasks to be very complicated to the point of claiming them to be impossible; however, there was always a way to do it.
Now, where there is a possiblity of something not working, I found myself pouring over looking for an answer that was not there.

Loking at my older table of predicted O Notations, I predicted that the majoriy, if not all of them, would have coefficients of 1 or 2.
After building them, I fould that ALL O Notations of dominant terms have coefficients of 2.
This seems weird to me, each function for each structure having the same coefficients, but I believe my answers are justified given my code.

These results will surely help in future projects.
From the information I've collected, vectors seem to be the most useful.
Lists are great for quick edits to the front and back as well has keeping lots of (mainly) static data, but iterating through them is time-consuming.
BSTs are good for organizing data, but it has the same problem of iteration as lists.
Priority queues have even more limited use, as you cannot edit or access any values except the first and last.
Hash Tables are great for quick access but not at all for iteration or indexing.
Vectors seem to be able to do everything: indexing, random access, sorting to a specific algorithm, and good runtime.
Hash tables may be comparable or even faster, but vectors are more versatile.



MISC. COMMENTS TO GRADER:  
My computer is not properly showing the operation time.
   Instead of giving a usable double, all of my functions, except for two, come up as 0.
   I am told that this is a problem due to my computer since the time library may be
    connected to my computer's time settings.
   The two functions that work come up as 0.015625, which is a reasonable number, so I am
    confused as to why my output is majority 0's.
   I have opted to copy operation time values from my Submitty submission.





**COMMANDS (for convenience):
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Homework/HW10
clang++ -g -Wall -Wextra performance*.cpp -o perf.out
./perf.out vector sort string < small_string_input.txt
./perf.out vector sort integer < small_integer_input.txt
./perf.out vector remove_duplicates string < small_string_input.txt
./perf.out vector remove_duplicates integer < small_integer_input.txt
./perf.out vector mode string < small_string_input.txt
./perf.out vector mode integer < small_integer_input.txt
./perf.out vector first_sorted string 3 < small_string_input.txt
./perf.out vector first_sorted integer 3 < small_integer_input.txt
./perf.out vector longest_substring string < small_string_input.txt
./perf.out vector closest_pair integer < small_integer_input.txt
./perf.out list sort string < small_string_input.txt
./perf.out list sort integer < small_integer_input.txt
./perf.out list remove_duplicates string < small_string_input.txt
./perf.out list remove_duplicates integer < small_integer_input.txt
./perf.out list mode string < small_string_input.txt
./perf.out list mode integer < small_integer_input.txt
./perf.out list first_sorted string 3 < small_string_input.txt
./perf.out list first_sorted integer 3 < small_integer_input.txt
./perf.out list longest_substring string < small_string_input.txt
./perf.out list closest_pair integer < small_integer_input.txt
./perf.out bst sort string < small_string_input.txt
./perf.out bst sort integer < small_integer_input.txt
./perf.out bst remove_duplicates string < small_string_input.txt
./perf.out bst remove_duplicates integer < small_integer_input.txt
./perf.out bst mode string < small_string_input.txt
./perf.out bst mode integer < small_integer_input.txt
./perf.out bst first_sorted string 3 < small_string_input.txt
./perf.out bst first_sorted integer 3 < small_integer_input.txt
./perf.out bst longest_substring string < small_string_input.txt
./perf.out bst closest_pair integer < small_integer_input.txt
./perf.out priority_queue sort string < small_string_input.txt
./perf.out priority_queue sort integer < small_integer_input.txt
./perf.out priority_queue mode string < small_string_input.txt
./perf.out priority_queue mode integer < small_integer_input.txt
./perf.out priority_queue first_sorted string 3 < small_string_input.txt
./perf.out priority_queue first_sorted integer 3 < small_integer_input.txt
./perf.out priority_queue closest_pair integer < small_integer_input.txt
./perf.out hash_table remove_duplicates string < small_string_input.txt
./perf.out hash_table remove_duplicates integer < small_integer_input.txt
./perf.out hash_table mode string < small_string_input.txt
./perf.out hash_table mode integer < small_integer_input.txt


GIVEN COMMANDS:
clang++ -g -Wall -Wextra performance*.cpp -o perf.out
./perf.out vector mode string < small_string_input.txt
./perf.out vector remove_duplicates string < small_string_input.txt > my_out.txt
diff my_out.txt small_string_output_remove_duplicates.txt
./perf.out vector closest_pair integer < small_integer_output_remove_duplicates.txt
./perf.out vector first_sorted string 3 < small_string_input.txt
./perf.out vector longest_substring string < small_string_output_remove_duplicates.txt
./perf.out vector sort string < medium_string_input.txt > vec_out.txt 2> vec_stats.txt
./perf.out list sort string < medium_string_input.txt > list_out.txt 2> list_stats.txt
diff vec_out.txt list_out.txt
Generating Random Output:
clang++ -g -Wall -Wextra generate_input.cpp -o generate_input.out
./generate.out string 10000 5 5 > medium_string_input.txt
./generate.out integer 10000 3 5 > medium_integer_input.txt
Memory Usage:
clang runstats.c -o runstats.out
./runstats.out ./perf.out vector sort string < medium_string_input.txt > my_out.txt