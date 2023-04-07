HOMEWORK 7: WORD FREQUENCY MAPS


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
- Thomas, Abin, '25
- 
Websites:
- https://www.cplusplus.com/reference/cstdlib/rand/
- 
- 

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  28.5hrs



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

n = total number of words in the sample text file
m = number of unique words in the file
w = width of the sequencing window
p = average number of words observed to follow a particular word
x = the number of words that should be generated

How much memory will the map data structure require, in terms of n, m,
w, p, x (order notation for memory use)?
---
Memory: O(m * w * p)
Explanation:
For every uniquue word, there is an average next word associated with it;
For every next word, there woulfd also be an associated next word;
This is measured by the width of the sequencing window, the reading frame

What is the order notation for performance (running time) of each of
the commands?
---
Load: O(n * log(m) * n)
Explanation:
Load only calls the function LoadSampleText();
To parse, we need to see every word in the file (n);
Each word is added to the map (log(m));
The function call ReadNextWord() iterates through each letter of each word in file (n);

Print: O(w+p * )
Explanation:
Worst case: reading frame 3, 2 words given;
To display every word andcorresponding possible "next words", visit every word at all depths (w+p)


Generate: O(w+p * x)
Explanation:
Worst case: reading frame 3, 2 words given
To find every next possible word, visit every word at all depths (w+p)
Repeat for as many times as viwer needs (x)

Quit: O(1)
Explanation:
Only one operation, immediate operation


EXTRA CREDIT
Parsing & using punctuation data, implementation supports *any*
window size, new test cases (describe & summarize performance, but
don't include large datasets with submission).



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)




NOTES:
store as many words in list as needed, add words to needed map, edit vecotr for next read

~LOADING A FILE
if reading frame is 2 words:
    while words to read:
        store first word in variable: curr
        if next word exists:
            store next word in variable: next
        else:
            add curr to map
        if curr not in map:
            create pair: curr/mini-map
            in mini-map, create pair: next/1
        else if curr in map:
            if next not in mini-map:
                create pair: next/1
            else if next in mini-map:
                in mini-map, add 1 to value of next

else if reading fame is 3 words:
    while words to read:
        store all words in vector

    for vector words (except last two):
        store first word in variable: curr
        store next word in variable: next
        store last word in variable: next2
        if curr not in map:
            create pair: curr/mini-map
            in mini-map, create pair: next/minimap2
            in mini-map2, create pair: next2/1
        else if curr in map:
            if next not in mini-map:
                in mini-map, create pair: next/minimap2
                in mini-map2, create pair: next2/1
            else if next in mini-map:
                if next2 not in mini-map2:
                    in mini-map2, create pair: next2/1
                else if next2 in mini-map2:
                    in mini-map2, add 1 to value of next2

~PRINTING