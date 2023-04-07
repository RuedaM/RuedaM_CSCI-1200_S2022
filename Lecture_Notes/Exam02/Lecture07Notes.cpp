//Lecture 7 - Order Notation (Performance Analysis) & Basic Recursion


//OVERVIEW
/*
- Algorithm Analysis, Formal Definition of Order Notation
- Simple recursion, Visualization of recursion, Iteration vs. Recursion
- “Rules” for writing recursive functions, Lots of examples!
*/


//7.1 Algorithm Analysis
/*
Why should we bother? We want to:
- do better than just implementing and testing every idea we have
- know why one algorithm is better than another
- know the best way we can do something (This is often quite hard)

How do we do it? There are several options, including:
- Don’t do any analysis; just use the first algorithm you can think of that works
	- (WRONG - Could be missing out on more optimal way)
- Implement and time algorithms to choose the best
	- (GOOD - Most surefire way to test optimization, but not the most effective/fast)
- Analyze algorithms by counting operations while assigning different weights to different types of operations based on how long each
   takes
	- (GOOD - Accounts for everything and tests all possbilities, very comprehensive, but perhaps too much so - too complicated)
- Analyze algorithms by assuming each operation requires the same amount of time. Count the total number of operations, and then multiply
   this count by the average cost of an operation
	- (CORRECT - A good generalization, but not great for specific operations, but the best way)
*/


//7.2 Exercise: Counting Example
/*
- Suppose arr is an array of several n doubles - here is a simple fragment of code to sum of the values in the array:
*/
double sum = 0;
for (int i=0; i<n; ++i)
	sum += arr[i];
/*
- What is the total number of operations performed in executing this fragment? Come up with a function describing the number of operations
   in terms of n
ANSWER:
The the function will run n amount of times: O(n)
Yes, there are other small operations (initialization, adding to the counter, etc.), but these won't matter if n can reach infinitely high
With that said, we can ignore these little additions and focus on the size of n
*/


//7.3 Exercise: Which Algorithm is Best?
/*
A venture capitalist is trying to decide which of 3 startup companies to invest in and has asked for your help. Here’s the timing data for
 their prototype software on some different size test cases:
	n 		foo-a 		foo-b 		foo-c
	10 	10 u-sec 	5 u-sec 		1 u-sec
	20 	13 u-sec 	10 u-sec 	8 u-sec
	30 	15 u-sec 	15 u-sec 	27 u-sec
	100 	20 u-sec 	50 u-sec 	1000 u-sec
	1000 	? 				? 				?
Which company has the “best” algorithm?
ANSWER:
A will most likely be the best choice since it takes less time to process all kind of n's (genrally, compared to the others)
Yes, the tim to process 10's is larger in A, but it takes far less time to process 1000's in A
*/


//7.4 Order Notation Definition
/*
In this course, we will focus on the INTUITION OF ORDER NOTATION - this topic will be covered again in more depth in later CS courses

- Definition: Algorithm A is order f(n), denoted as O(f(n)), if constants k and n0 exist such that A requires no more than
   k ∗ f(n) time units (operations) to solve a problem of size n ≥ n0
	- For example, algorithms requiring 3n+2, 5n−3, and 14+17n operations are all O(n)
	- This is because we can select values for k and n0 such that the definition above holds (What values?)
	- Likewise, algorithms requiring (n^2)/10+15n−3 and 10000+35(n^2) are all O(n^2)

- Intuitively, we determine the order by finding the asymptotically dominant term (function of n) + throwing out the leading constant -
   this term could involve logarithmic/exponential functions of n
	- Implications for analysis:
		- We don’t need to worry about small differences in the numbers of operations or different costs of different types of operations
		- We don’t produce an actual time: we just obtain a rough count of the number of operations - this count is used for comparison
		   purposes only
- In practice, this makes analysis relatively simple, quick, and (sometimes unfortunately) rough
*/


//7.5 Common Orders of Magnitude
/*
(From top to bottom, from lower to higher precedence)
- O(1)								CONSTANT - The number of operations independent of the size of the problem (e.g. compute quadratic root)
- O(log(n))							LOGARITHMIC (e.g. dictionary lookup, binary search)
- O(n)								LINEAR (e.g. sum up a list)
- O(n*log(n))						(e.g. sorting)
- O(n^2), O(n^3),...,O(n^k)	POLYNOMIAL (e.g. find closest pair of points)
- O(2^n), O(k^n)					EXPONENTIAL (e.g. Fibonacci sequence, playing chess)
*/


//7.6 Exercise: A Slightly Harder Example
/*
- Here’s an algorithm to determine if the value stored in variable x is also in an array called foo.
   Can you analyze it? What did you do about the if statement? What did you assume about where the value stored in x occurs in the array
   (if at all)?
*/
int loc=0;
bool found = false;
while (!found && loc < n) {
	if (x == foo[loc])
		found = true;
	else
		loc++;
}
if (found) cout << "It is there!\n";
/*
ANSWER:

*/


//7.7 Best-Case, Average-Case and Worst-Case Analysis
/*
- For a given fixed size array, we might want to know:
	- The fewest number of operations (best case) that might occur
	- The average number of operations (average case) that will occur
	- The maximum number of operations (worst case) that can occur
- The last is the most common - the first is rarely used
- On the previous algorithm, the best case is O(1), but the average case and worst case are both O(n)
*/


//7.8 Approaching An Analysis Problem
/*
- Decide the important variable (or variables) that determine the “size” of the problem. For arrays and other “container classes,” this
   will generally be the number of values stored
- Decide what to count: the order notation helps us here
	- If each loop iteration does a fixed (or bounded) amount of work, then we only need to count the number of loop iterations
	- We might also count specific operations - for example, in the previous exercise, we could count the number of comparisons
- Do the count and use order notation to describe the result
*/


//7.9 Exercise: Order Notation
/*
For each version below, give an order notation estimate of the number of operations as a function of n:
*/
//1.
int count=0;
for (int i=0; i<n; ++i)
	for (int j=0; j<n; ++j)
		++count;
//ANSWER: O(n^2)
//

//2.
int count=0;
for (int i=0; i<n; ++i)
	++count;
for (int j=0; j<n; ++j)
	++count;
//ANSWER: O(n)
//Two separate loops not linked, so it would technically be 2n - but we ignore coefficients, so it would be simply n

//3.
int count=0;
for (int i=0; i<n; ++i)
	for (int j=i; j<n; ++j)
		++count;
//ANSWER: O(x^2)
//This would come up to ((n^2)/2)+(n/2) whihc would simplify to n^2 to get rid of coefficients


//7.10 Recursive Definitions of Factorials and Integer Exponentiation
/*

*/


//7.11 Recursive C++ Functions
/*
C++, like other modern programming languages, allows functions to call themselves; this gives a direct method of implementing RECURSIVE
 functions - here are the recursive implementations of factorial and integer power:
*/
int fact(int n) {
	if (n == 0) {
		return 1;
	} else {
		int result = fact(n-1);
		return n * result;
	}
}

int intpow(int n, int p) {
	if (p == 0) {
		return 1;
	} else {
		return n * intpow( n, p-1 );
	}
}


//7.12 The Mechanism of Recursive Function Calls
/*
- For each recursive call (or any function call), a program creates an ACTIVATION RECORD to keep track of:
	- COMPLETELY SEPARATE INSTANCES of the parameters and local variables for the newly-called function
	- The location in the calling function code to return to when the newly-called function is complete (Who asked for this function to
	   be called? Who wants the answer?)
	- Which activation record to return to when the function is done. For recursive functions this can be confusing since there are
	   multiple activation records waiting for an answer from the same function

- This is illustrated in the following diagram of the call fact(4). Each box is an activation record, the solid lines indicate the
   function calls, and the dashed lines indicate the returns. Inside of each box we list the parameters and local variables and make notes
   about the computation
- This chain of activation records is stored in a special part of program memory called THE STACK
*/


//7.13 Iteration vs. Recursion
/*
- Each of the above functions could also have been written using a for or while loop, i.e. iteratively - for example, here is an iterative
   version of factorial:
*/
int ifact(int n) {
	int result = 1;
	for (int i=1; i<=n; ++i)
		result = result * i;
	return result;
}
/*
- Often writing recursive functions is more natural than writing iterative functions, especially for a first draft of a problem
   implementation
- You should learn how to recognize whether an implementation is recursive or iterative, and practice rewriting one version as the other
   (Note: We’ll see that not all recursive functions can be easily rewritten in iterative form!)
- Note: The order notation for the number of operations for the recursive and iterative versions of an algorithm is usually the same;
   however in C, C++, Java, and some other languages, iterative functions are generally faster than their corresponding recursive
   functions - this is due to the overhead of the function call MECHANISM - Compiler optimizations will sometimes (but not always!) reduce
   the performance hit by automatically eliminating the recursive function calls. This is called TAIL CALL OPTIMIZATION
*/


//7.14 Exercises
/*
1. Draw a picture to illustrate the activation records for the function call
*/
cout << intpow(4, 4) << endl;
/*
2. Write an iterative version of intpow
3. What is the order notation for the two versions of intpow?
*/


//7.15 Rules for Writing Recursive Functions
/*
Here is an outline of five steps that are useful in writing and debugging recursive functions:
 (Note: You don’t have to do them in exactly this order...)

1. Handle the base case(s)
2. Define the problem solution in terms of smaller instances of the problem. Use wishful thinking, i.e., if someone else solves the
   problem of fact(4) I can extend that solution to solve fact(5). This defines the necessary recursive calls - it's also the hardest part
3. Figure out what work needs to be done before making the recursive call(s)
4. Figure out what work needs to be done after the recursive call(s) complete(s) to finish the computation (What are you going to do with
	the result of the recursive call?)
5. Assume the recursive calls work correctly, but make sure they are progressing toward the base case(s)!
*/


//7.16 Location of the Recursive Call — Example: Printing the Contents of a Vector
/*
- Here is a function to print the contents of a vector:
   (Actually, it’s two functions: a driver function, and a true recursive function - it's common to have a driver function that just
	   initializes the first recursive function call)
*/
void print_vec(std::vector<int>& v, unsigned int i) {
	if (i < v.size()) {
		cout << i << ": " << v[i] << endl;
	print_vec(v, i+1);
	}
}

void print_vec(std::vector<int>& v) {
	print_vec(v, 0);
	}
	• What will this print when called in the following code?
	int main() {
	std::vector<int> a;
	a.push_back(3); a.push_back(5); a.push_back(11); a.push_back(17);
	print_vec(a);
}
/*
- How can you change the second print_vec function as little as possible so that this code prints the contents of the vector in reverse
   order?
*/


//7.17 Fibonacci Optimization: Order Notation of Time vs. Space
/*
1. Write a simple recursive version of Fibonacci that is a direct translation of the mathematical definition of the Fibonacci sequence:*/
unsigned int fib(unsigned n) {
	if (n==0) {return int 0;}
	else if (n==1) {return 1;}
	else {return fib(n-1) + fib(n-2);}
}

/*
2. Write an iterative version of Fibonacci that uses a vector to improve the running time of the function*/
#include<vector>
unsigned int fib_iterative(unsigned int n) {
	std::vector<unsigned int> v(n+1, 0);

	// Base cases
	v[0]=1; v[1]=1;

	for (unsigned int i=2, i<=n ; ++i) {
		v[i] = v[i-1] - v[i-2];		//Fill in ih Fibonacci number
	}

	return v[n];
}

/*
3. What is the order notation of the running time for each version?
ANSWER:
Recursive: O(2^n) for the two times the same function is called
Iterative: O(n) for the one time you are looping through values


4. What is the order notation of the memory usage for each version?
ANSWER:
Recursive: O(1) since we aren't storing anything in the stack
Iterative: O(n) since we are storing values in a vector on the stacks
*/


//7.18 Binary Search
/*
- Suppose you have a std::vector<T> v (for a placeholder type T), sorted so that: v[0] <= v[1] <= v[2] <= ...
- Now suppose that you want to find if a particular value x is in the vector somewhere - how can you do this without looking at every
   value in the vector?
- The solution is a recursive algorithm called binary search, based on the idea of checking the middle item of the search interval within
   the vector and then looking either in the lower half or the upper half of the vector, depending on the result of the comparison
*/
template <class T>
bool binsearch(const std::vector<T> &v, int low, int high, const T &x) {
	if (high == low) return x == v[low];
	int mid = (low+high) / 2;
	if (x <= v[mid])
		return binsearch(v, low, mid, x);
	else
		return binsearch(v, mid+1, high, x);
}

template <class T>
bool binsearch(const std::vector<T> &v, const T &x) {
	return binsearch(v, 0, v.size()-1, x);
}



//7.19 Exercises
/*
1. Write a non-recursive version of binary search.
2. If we replaced the if-else structure inside the recursive binsearch function (above) with:
*/
if ( x < v[mid] )
	return binsearch( v, low, mid-1, x );
else
	return binsearch( v, mid, high, x );
/*
   would the function still work correctly?
*/