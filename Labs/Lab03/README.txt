cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Labs/Lab03


POSSIBLE COMPILING LINES:
g++ -Wall -Wextra -g roads.cpp -o roads.out
g++ -Wall -Wextra -g roads.cpp -o roads.exe
g++ roads.cpp point.cpp line.cpp -o roads.out -Wall -Wextra -g
g++ roads.cpp point.cpp line.cpp -o roads.exe -Wall -Wextra -g

gdb roads.out
gdb roads.exe



POSSIBLE EXECUTION FLES:
./roads.out input_a.txt
./roads.out input_b.txt
./roads.out input_c.txt
./roads.out input_d.txt



FIX LOG:
- Commands added to compiling statement: -Wall -Wextra :to provide all warnings to the terminal
- Command added to compiling statement: -g :to provide possile suggestions for compiling errors
- Commands added to compiling statement: roads.cpp -o roads.out :to create an executable file based on the provided .cpp file; the -o is used to indicate that this is an object code


- added: #include <algorithm> :to utilize the sort() function; fixes compiling error
(Was that it?)
- added: #include "point.h" :to access the point.h and Point class
- added: Point() :as blank constructor to point.h
- added default constructors to point.cpp
- deleted function actions from point.h Lines 14-16; these should be put in point.cpp
- added: Point:: :prefix to point.cpp Lines 16-18 to access member variables



- roads.cpp:18:10: warning: reference to local variable ‘roads’ returned [-Wreturn-local-addr]
	- A reference to a local variable rather than a copy was returned, possibly changing a variable elsewhere
- roads.cpp:13:21: note: declared here // std::vector<Line> roads;
	- This i a follow-up note to the warning below, stating where this may be a source of error as well
- roads.cpp:32:21: warning: comparison of integer expressions of different signedness: ‘int’ and ‘std::vector<Line>::size_type’ {aka ‘long unsigned int’} [-Wsign-compare]
	- The ranges of signed and unsigned variable types are different: an unsigned int can reach a higher value than a signed int - this warning was made to make sure there is not an unfair comparison
- roads.cpp:39:10: warning: comparison of unsigned expression >= 0 is always true [-Wtype-limits]
	- The ranges of signed and unsigned variable types are different: an unsigned int can reach a higher value than a signed int - unsignd ints are never negative, so if th user wants to compare a negative they will have to change it