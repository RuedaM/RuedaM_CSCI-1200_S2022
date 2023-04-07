//LECTURE 1 —  Introduction to C++, STL, & Strings
#include <iostream>



//1.0 Actually Compiling
/*
- To compile, type: g++ [filename].cpp
- To run and display results in the terminal, type: ./a.out
*/


//1.1 Transitioning from Python to C++
/*
- This semester we'll work in C++ and study low-level programming concepts, focusing on details including efficiency and memory usage
- Outside of this class, when working on large programming projects, you will find it is not uncommon to use a mix of programming
   languages and libraries. The individual advantages of Python and C++ (and Java, Perl, C, UNIX bash scripts, etc.) can be combined
   into an elegant (or terrifyingly complex) masterpiece.
*/


//1.2 Compiled Languages vs. Interpreted Languages
/*
- C/C++ is a compiled language, which means your code is processed (compiled & linked) to produce a low-level machine language
   executable that can be run on your specific hardware. You must re-compile & re-link after any edits any of the files - if you
   move your code to a different computer you will usually need to recompile
	- Generally the extra work of compilation produces an efficient and optimized code that will run fast
- In contrast, Python, Java, etc. are interpreted languages where you can make changes to your code and immediately run all or some
   of your code without waiting for compilation - however, interpreted programs will often run slower than a compiled program
- You will practice the cycle of coding & compilation & testing during Lab 1. You are encouraged to try out
   different development environments (code editor & compiler) and quickly settle on one that allows you to be
   most productive.
- As you see in today’s handout, C++ has more required punctuation than Python, and the syntax is more
   restrictive. The compiler will proofread your code in detail and complain about any mistakes you make. Even
   long-time C++ programmers make mistakes in syntax, and with practice you will become familiar with the
   compiler’s error messages and how to correct your code.
*/


//1.3 A Sample C++ Program: Find the Roots of a Quadratic Polynomial
#include <iostream> // library for reading & writing from the console/keyboard
#include <cmath> // library with the square root function & absolute value
#include <cstdlib> // library with the exit function

// Returns true if  candidate root is  a root of the polynomial (a*x*x + b*x + c = 0)
bool check_root(int a, int b, int c, float root) {
	// plug value into formula
	float check = a*root*root + b*root + c;
	// see if absolute value is zero (within small tolerance)
	if (fabs(check) > 0.0001) {
		std::cerr << "ERROR: " << root << " is not a root of this formula." << std::endl;
		return false;
	} else {
		return true;
	}
}

/* Use quadratic formula to find two real roots of polynomial. Returns true if  roots are real, false if they are imaginary. If
   roots are real, they are returned through reference parameters root_pos and root_neg. */
bool find_roots(int a, int b, int c, float &root_pos, float &root_neg) {
	// compute quantity under radical of quadratic formula
	int radical = b*b - 4*a*c;
	// if radical is negative, roots are imaginary
	if (radical < 0) {
		std::cerr << "ERROR: Imaginary roots" << std::endl;
	return false;
	}
	float sqrt_radical = sqrt(radical);
	// compute two roots
	root_pos = (-b + sqrt_radical) / float(2*a);
	root_neg = (-b - sqrt_radical) / float(2*a);
	return true;
	}

int main() {
	// Will loop until given a polynomial with real roots
	while (true) {
		std::cout << "Enter 3 integer coefficients to a quadratic function: a*x*x + b*x + c = 0" << std::endl;
		int my_a, my_b, my_c;
		std::cin >> my_a >> my_b >> my_c;
		// create place to store roots
		float root_1, root_2;
		bool success = find_roots(my_a,my_b,my_c, root_1,root_2);
		// If polynomial has imaginary roots, skip the rest of the loop and start over
		if (!success) continue;
		std::cout << "The roots are: " << root_1 << " and " << root_2 << std::endl;
		// Check our work...
		if (check_root(my_a,my_b,my_c, root_1) && check_root(my_a,my_b,my_c, root_2)) {
			// Verified roots, break out of the while loop
			break;
		} else {
			std::cerr << "ERROR: Unable to verify one or both roots." << std::endl;
			// if the program has an error, we choose to exit with a
			// non-zero error code
			exit(1);
		}
	}
	// by convention, main should return zero when the program finishes normally
	return 0;
}


//1.4 Some Basic C++ Syntax Crash Course in C++: Lesson #2 & #3
/*
- Comments: // for single line and [the symbols above+below] for multi-line
- #include: asks compiler for parts of the standard library and other code that we wish to use (e.g. the input/output stream function
   std::cout)
- int main(): necessary component of all C++ programs; it returns a value (integer in this case) and may have parameters
- Curly braces { }: indicate to C++ to treat everything between them as a unit - grouping
*/


//1.5 The C++ Standard Library, a.k.a. “STL”
/*
- The standard library std::___ contains types+functions that are important extensions to the core C++ language - We will use the
   standard library to such a great extent that it will feel like PART of the core language
- I/O streams are the first component of std:: that we see - std::cout (“console output”) and std::endl (“end line”) are defined in
   the standard library header file, iostream

- std::cin >> - Will receive any input typed into the terminal - stops receiving when the Enter button is pressed, storing the value
   in a variable
- std::cout << - Will print out any string or variabe to the terminal - when exporting text to someplace else, anything written as
   cout will show there
- std::err << - Will print out any string or variabe to the terminal - when exporting text to someplace else, these messages will not
   appear as they are error messages meant only for the terminal
*/


//1.6 A few notes on C++ vs. Java
/*
- In Java, everything is an object and everything “inherits” from java.lang.Object - In C++, functions can exist outside of classes - 
   In particular, the main function is never part of a class
- Source code file organization in C++ does not need to be related to class organization as it does in Java - On the other hand,
   creating one C++ class per file is the preferred organization, with the main function in a separate file on its own or with a few
   helper functions
*/


//1.7 Variables and Types
/*
- Variable: object with a name of the writer's choosing - a name is a C++ identifier such as “a”, “root_1”, or “success”
- An object is computer memory that has a type. A type (e.g., int, float, and bool) is a structure to memory and a set of operations
- For example: a float is an object, each float variable is assigned to 4 bytes of memory, and this memory is formatted according to
   IEEE floating point standards for what represents the exponent and mantissa. There are many operations defined on floats,
   including addition, subtraction, printing to the screen, etc.
	- Every veriable type can do different/similar things depending on the type of variable
- In C++ and Java, the programmer must always specify the data type when a new variable is declared. In contrast, the programmer
   doesn't specify the type of variables in Python and Perl: those are deduced automatically
*/


//1.8 Expressions, Assignments and Statements
/*
- Consider the following statement: root_pos = (-b + sqrt_radical) / float(2*a);
	- The calculation on the right hand side of the = is an expression - recall that in arithmetic expressions PEMDAS will always
	   apply
- The value of this expression is assigned to the memory location of the float variable root_pos
	- Note also that if all expression values are of type int, we need a cast from int to float to prevent truncation of integer
	   division
*/


//1.9 Conditionals and IF-statements
/*
The general form of an if-else statement is:
+++++
if (conditional-expression) {
	statement(s);
}
else if (conditional-expression) {
	statement(s);
}
else {
	statement(s);
}
+++++
- Most if-statements are delimited by curly brackets {} - however, single statements under if-statements can simply be added w/out {}
+++++
if (conditional-expression)
	one-statement;
++OR++
if (conditional-expression)	one-statement;
+++++
*/


//1.10 Functions and Arguments
/*
- Functions are used to:
	- Break code up into modules for ease of programming + testing + ease of reading by others (never, ever, under-estimate this!!!)
	- Create code that is reusable at several places in one program and/or by several programs
- Each function has a sequence of parameters and a return type:
+++++
[return-type] [function-name](parameter(s) separated by commas) {
	statement(s)
	return [return-type-varaible];
}
+++++
   The function prototype below has a return type of bool and five parameters:
   +++++
	bool check_root(int a, int b, int c, float root) {
		...statements...
		if (condition(s)) {
			return true;
		} else {
			return false;
		}
	}
   +++++
- When calling the function elsewhere (for example, if you want to call the function in the main code), the order in which the
   parameters are listed must match that of the function's "placeholder" parameters
*/


//1.11 Value Parameters and Reference Parameters
/*
- What’s with the & symbol on the 4th and 5th parameters in the find_roots function prototype?
+++++
bool find_roots(int a, int b, int c, float &root_pos, float &root_neg) {
	statement(s)
}
+++++
- Note that when we call this function, we haven’t yet stored anything in those two root variables
+++++
float root_1, root_2;	//Only declared, no value attached to it
bool success = find_roots(my_a,my_b,my_c, root_1,root_2);	//Used here
+++++
- The first three parameters to this function are referred to as VALUE PARAMETERS
	- These are essentially local variables (in the function) whose initial values are copies of the values of the corresponding
	   argument in the function call
	- Thus, the value of my_a from the main function is used to initialize a in function find_roots
	- When these main-function variables are changed in the called function, they don't affect the main-function variables
	- This is also known as "pass by copy/value"
- The final two parameters are referred to as REFERENCE PARAMETERS, as indicated by the & symbol before the variable name
	- Reference parameters are ALLIASES for their corresponding arguments - No new objects (copies of the variable) are created
	- When these main-function variables are changed in the called function, those changes ARE reflected for the main-function
	   variables
	- This is also known as "pass by reference"
- In general, the “Rules of Thumb” for using value and reference parameters:
	- When a function (e.g., check_root) needs to provide just one simple result, make that result the return value of the function
	   and pass other parameters by value
	- When a function needs to provide more than one result (e.g., find_roots, these results should be returned using multiple
	   reference parameters
- We’ll see more examples of the importance of value vs. reference parameters later on
- See th example below:
*/
int f1(int x, int & y) {
	x = 5;
	y = 7;

	return 0;
}

int main2() {
	int a = 1;
	int b = 2;
	f1(a,b);

	std::cout << a << " and " << b << std::endl;

	return 0;
}


//1.12 for- & while-loops
/*
- Here is the basic form of a for-loop:
+++++
for (expr1; expr2; expr3) {
	statement;
}
+++++
	- expr1 is the initial expression executed at the start before the loop iterations begin;
	- expr2 is the test applied before the beginning of each loop iteration, the loop ends when this expression evaluates to false
	   or 0;
	- expr3 is evaluated at the very end of each iteration;
	- statement is the “loop body”
- similar to if-statements, single-line statements do not need curly braces {}
- Here is the basic form of a while-loop:
+++++
while (expr) {
	statement;
}
+++++
	- expr is checked before entering the loop and after each iteration - If expr ever evaluates to false, the loop is finished
	- Although not common but sometimes useful, you can always make an infinite loop with the syntax: while (true) { }

- coninue - when included in a loop, it will automatically skip ahead to the top of the loop again and run
- break - when included in a loop, the "code cursor" will break off from the loop and run the next line of code past the loop
	- This is useful when dealing with inifinite loops to break away from them
- exit() - no matter where in th program you are, it will terminate the whole program - this is essentially stating that "main() has
   returned something and will end"
*/


//1.13 C-style Arrays / Vectors
/*
- An array is a fixed-length, consecutive sequence of objects all of the same type - The following declares an array with space for
   15 double values (Note the spots in the array are currently uninitialized)
+++++
double a[15];
+++++
- The values are accessed through subscripting operations - The following code assigns the value 3.14159 to location i=5 of the
   array - here, i is the subscript or index
+++++
int i = 5;
a[i] = 3.14159;
+++++
- In C/C++/most other languages, array indexing starts at 0
- Arrays are of a FIXED size, and each array knows NOTHING about its own size (not smart like Python (can easily change array/list
   length)) - The programmer must keep track of the size of each array
	- (Note: C++ STL has generalization of C-style arrays called VECTORS which don't have these restrictions. More on this later)
*/


//1.14 Python Strings vs. C chars vs. C-style Strings vs. C++ STL Strings
/*
- Strings in Python are immutable: there is no difference between a string and a char in Python - 'a' and "a" are both strings in
   Python, not individual characters
	- In C++ & Java, single quotes create a character type (exactly one character) and double quotes create a string of 0, 1, 2, or
	   more characters
- A “C-style” string is an array of chars that ends with the special char ’\0’. C-style strings (char* or char[]) can be edited,
   and there are a number of helper functions to help with common operations. However...
	- The “C++-style” STL string type has a wider array of operations and functions, which are more convenient and more powerful
*/


//1.15 About STL String Objects
/*
- A string is an object type defined in the standard library to contain a sequence of characters.
- The string type, like all types (including int, double, char, float), defines an interface, which includes
construction (initialization), operations, functions (methods), and even other types(!).
• When an object is created, a special function is run called a “constructor”, whose job it is to initialize the
object. There are several ways of constructing string objects:
– By default to create an empty string: std::string my_string_var;
– With a specified number of instances of a single char: std::string my_string_var2(10, ' ');
– From another string: std::string my_string_var3(my_string_var2);
• The notation my_string_var.size() is a call to a function size that is defined as a member function
of the string class. There is an equivalent member function called length.
5
• Input to string objects through streams (e.g. reading from the keyboard or a file) includes the following steps:
1. The computer inputs and discards white-space characters, one at a time, until a non-white-space character
is found.
2. A sequence of non-white-space characters is input and stored in the string. This overwrites anything that
was already in the string.
3. Reading stops either at the end of the input or upon reaching the next white-space character (without
reading it in).
• The (overloaded) operator ’+’ is defined on strings. It concatenates two strings to create a third string, without
changing either of the original two strings.
• The assignment operation ’=’ on strings overwrites the current contents of the string.
• The individual characters of a string can be accessed using the subscript operator [] (similar to arrays).
– Subscript 0 corresponds to the first character.
– For example, given std::string a = "Susan"; Then a[0] == 'S' and a[1] == 'u' and a[4] == 'n'.
• Strings define a special type string::size_type, which is the type returned by the string function size()
(and length()).
– The :: notation means that size type is defined within the scope of the string type.
– string::size_type is generally equivalent to unsigned int.
– You may see have compiler warnings and potential compatibility problems if you compare an int variable
to a.size().
*/