HOMEWORK 6: STAR BATTLE


NAME:  Rueda, Maximillian



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

People:
- Rajgopal, Jayaram, '25
- Chen, Ivan, '25
- He, Daniel, '25
- Jacobs, Brianna, '25
- 
- 
- 
Websites:
- https://www.youtube.com/watch?time_continue=27&v=_FwjPMgPCvg&feature=emb_logo
- https://careerkarma.com/blog/c-plus-plus-string-to-int/#:~:text=In%20C%2B%2B%20the%20stoi%20%28%29%20function%20is%20used,class%20is%20used%20to%20convert%20string%20to%20int.
- https://www.geeksforgeeks.org/how-to-declare-a-2d-array-dynamically-in-c-using-new-operator/
- 
- 
- 

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  27.5hrs.



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(running time order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of zones (z)? 
The average number of squares in a zone (t) 
The number of stars per zone(s)? 
etc.
---
By convention, sorting is O(nlog(n)), so zoneSort would also be O(nlog(n)).
Printing the board with print() would cost O(w*h) since we go through every row and column.



DESCRIPTION OF YOUR ADDTIONAL PUZZLES:
Briefly explain the design of the puzzles or dictionaries and what
makes them "interesting" test cases (or why they aren't interesting).
---
insert here


SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES AND 
ON YOUR ADDITIONAL PUZZLES:
# of solutions & approximate wall clock running time for different
puzzles / stars per zone for a single solution or all solutions. Be
specific about which puzzle/parameters you were timing.
---
custom1.txt, 1 star, single = ~2sec
custom1.txt, 1 star, all = ~2sec
custom1.txt, 2 star, single = 
custom1.txt, 2 star, all = 
custom1.txt, 3 star, single = 
custom1.txt, 3 star, all = 
custom2.txt, 1 star, single = ~3sec
custom2.txt, 1 star, all = ~5sec
custom2.txt, 2 star, single = 
custom2.txt, 2 star, all = 
custom2.txt, 3 star, single = 
custom2.txt, 3 star, all = 
custom3.txt, 1 star, single = ~2sec
custom3.txt, 1 star, all = ~2sec
custom3.txt, 2 star, single = 
custom3.txt, 2 star, all = 
custom3.txt, 3 star, single = 
custom3.txt, 3 star, all = 
sporcle1.txt, 1 star, single = 
sporcle1.txt, 1 star, all = 
sporcle1.txt, 2 star, single = 
sporcle1.txt, 2 star, all = 
sporcle1.txt, 3 star, single = 
sporcle1.txt, 3 star, all = 
twonot1.txt, 1 star, single = 
twonot1.txt, 1 star, all = 
twonot1.txt, 2 star, single = 
twonot1.txt, 2 star, all = 
twonot1.txt, 3 star, single = 
twonot1.txt, 3 star, all = 
twonot2.txt, 1 star, single = 
twonot2.txt, 1 star, all = 
twonot2.txt, 2 star, single = 
twonot2.txt, 2 star, all = 
twonot2.txt, 3 star, single = 
twonot2.txt, 3 star, all = 


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)






CODING NOTES:
create zone class with necessary varables
create coordinate class to organize "tuples"

~Creating a board~
(zone vector should be created outside and passed to reference)
establish OVERALL counter and ZONE counter
iterate through file - alphaneumerics
	if counter is 0: store value as rows
	if counter is 1: store value as cols AND
		build board: create array of arrays (size rows) filled w/ arrays (size cols)
	if counter is 2: store value as char to add
	if counter is 3: store value in zone size vector
	if counter is 4: store value as x-ccord
	if counter is 5: store value as y-coord AND
		set grid vector index as char to add
		increase zone counter by 1
		if zone counter equals last index of zone size vector
			reset counter to 2
		else
			reset counter to 4

~Recursion method~
Enter new zone
	Use zone's coord list and go in order of coords
		If star is not adjacent to existing star,
		If star is not in the same horizontal,
		If star is not in the same vertical,
			Place star and move into next zone (GO TO 87)
		else, go back and delete old star, move to next coord (GO TO 89)