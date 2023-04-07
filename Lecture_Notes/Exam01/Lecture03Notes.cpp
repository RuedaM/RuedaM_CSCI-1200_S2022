//Lecture 3 — Classes I
#include <iostream>



//PREVIOUS LECTURE REVIEW
/*
- Vectors are dynamically-sized arrays
- Vectors, strings and other containers should be:
	- passed by reference when they are to be changed, and
	- passed by constant reference when they aren’t
   If you forget the & and pass by value, the object will be copied which is expensive for containers with lots of elements
   Note: This is unlike arrays, which are not copied when passed by value
- Vectors can “contain” any type of objects, including strings and other vectors
*/


//OVERVIEW
/*
- Classes in C++; Types and defining new types; Example: A Date class;
- Class declaration: member variables and member functions; Using the class member functions;
- Member function implementation; Class scope; Classes vs. structs; Designing classes;
- Defining a custom sort of class instances
*/


//3.1 Types and Defining New Types
/*
- What is a type?
	- It is a structuring of memory plus a set of operations that can be applied to that structured memory
	- Every C++ object has a type (e.g., integers, doubles, strings, and vectors, etc., including custom types)
	- The type tells us what the data means and what operations can be performed on the data
- The basic ideas behind classes are DATA ABSTRACTION and ENCAPSULATION:
	- In many cases when we are using a class, we don’t know (don’t need to know) exactly how that memory is structured. Instead,
	   what we really think about what operations are available
	- Data abstraction hides details that don’t matter from the end user and identifies details that do matter
	- The user sees only the interface to the object: the collection of externally-visible data and operations
	- Encapsulation is the packing of data and functions into a single component - an object's attributes are stored in one place
- Information hiding
	- Users have access to interface, but not implementation
	- No data item should be available any more than absolutely necessary
- To clarify, let’s focus on strings and vectors. These are classes. We’ll outline what we know about them:
	- The structure of memory within each class object
	- The set of operations defined
- We are now ready to start defining our own new types using classes
*/


//3.2 Example: A Date Class
/*
- Many programs require information about dates.
- Information stored about the date includes the month, the day and the year.
- Operations on the date include recording it, printing it, asking if two dates are equal, flipping over to the next day
   (incrementing), etc.
*/


//3.3 C++ Classes
/*
- A C++ class consists of:
	- a collection of MEMBER VARIABLES, usually private
	- a collection of MEMBER FUNCTIONS, usually public - they operate on these variables
- public member functions can be accessed directly from outside the class,
- private member functions and member variables can only be accessed indirectly from outside the class, through public member
   functions
- We will look at the example of the Date class declaration
*/


//3.4 Using C++ classes
/*
• We have been using C++ classes (from the standard library) already this semester, so studying how the Date
class is used is straightforward:
*/
// Program: date_main.cpp
// Purpose: Demonstrate use of the Date class.

#include <iostream>
#include "date.h"

int main() {
	std::cout << "Please enter today's date.\n"
	<< "Provide the month, day and year: ";
	int month, day, year;
	std::cin >> month >> day >> year;
	Date today(month, day, year);
	
	//Let's show what happens if we try to use today.month (private member variable)
	Date tomorrow(today.getMonth(), today.getDay(), today.getYear());
	tomorrow.increment();
	
	std::cout << "Tomorrow is ";
	tomorrow.print();
	std::cout << std::endl;
	
	Date Sallys_Birthday(9,29,1995);
	if (sameDay(tomorrow, Sallys_Birthday)) {
		std::cout << "Hey, tomorrow is Sally's birthday!\n";
	}
	
	std::cout << "The last day in this month is " << today.lastDayInMonth() << std::endl;
	return 0;
}
/*
- This is a good example of data abstraction: there is no mention of a Date class but based on what's written you can figure it out
- Important: Each object we create of type Date has its own distinct member variables.
- Calling class member functions for class objects uses the “dot” notation. For example, tomorrow.increment();
- Note: We don’t need to know the implementation details of the class member functions in order to understand this example - This
   is an important feature of object oriented programming and class design
*/


//3.5 Exercise
/*
Add code to date_main.cpp to read in another date, check if it is a leap-year, and check if it is equal to tomorrow
 Output appropriate messages based on the results of the checks
*/


//3.6 Class Declaration (date.h) & Implementation (date.cpp)
/*
A class implementation usually consists of 2 files. First we’ll look at the header file date.h:
*/
// File: date.h
// Purpose: Header file with declaration of the Date class, including member functions and private member variables.

class Date {
public:
	// CONSTRUCTORS - 
	Date();
	Date(int aMonth, int aDay, int aYear);
	
	// ACCESSORS - taking in values to be stored in the class
	int getDay() const;
	int getMonth() const;
	int getYear() const;
	
	// MODIFIERS - change member variables within th class
	void setDay(int aDay);
	void setMonth(int aMonth);
	void setYear(int aYear);
	void increment();
	
	// other member functions that operate on date objects
	bool isEqual(const Date& date2) const; // same day, month, & year?
	bool isLeapYear() const;
	int lastDayInMonth() const;
	bool isLastDayInMonth() const;
	void print() const; // output as month/day/year

private: // REPRESENTATION (member variables)
	int day;
	int month;
	int year;
};
// prototypes for other functions that operate on class objects are often
// included in the header file, but outside of the class declaration bool sameDay(const Date &date1, const Date &date2);
    // same day & month?

/*
And here is the other part of the class implementation, the implementation file date.cpp
Notice that any time a Date class function is used, Date:: preceeds it - this is to show it's from the Date class
*/
// File: date.cpp
// Purpose: Implementation file for the Date class.

#include <iostream>
#include "date.h"  //importing the class Date located in the date.h file

// array to figure out the number of days, it's used by the auxiliary function daysInMonth
const int DaysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date() { //default constructor - what does it do?
	day = 1;
	month = 1;
	year = 1900;
}

Date::Date(int aMonth, int aDay, int aYear) { // construct from month, day, & year
	month = aMonth;
	day = aDay;
	year = aYear;
}

// GETTERS - getting/returning info from the Date class object
int Date::getDay() const {
	return day;
}
int Date::getMonth() const {
	return month;
}
int Date::getYear() const {
	return year;
}

// SETTERS - setting new values in a Date class object
void Date::setDay(int d) {
	day = d;
}
void Date::setMonth(int m) {
	month = m;
}
void Date::setYear(int y) {
	year = y;
}
void Date::increment() {
	if (!isLastDayInMonth()) {
		day++;
	} else {
		day = 1;
		if (month == 12) { // December
			month = 1;
			year++;
		} else {
			month++;
		}
	}
}

bool Date::isEqual(const Date& date2) const {
	return day == date2.day && month == date2.month && year == date2.year;
}

bool Date::isLeapYear() const {
	return (year%4 ==0 && year % 100 != 0) || year%400 == 0;
}


int Date::lastDayInMonth() const {
	if (month == 2 && isLeapYear())
		return 29;
	else
		return DaysInMonth[ month ];
}

bool Date::isLastDayInMonth() const {
	return day == lastDayInMonth(); // uses member function
}

void Date::print() const {
	std::cout << month << "/" << day << "/" << year;
}

bool sameDay(const Date& date1, const Date& date2) {
	return date1.getDay() == date2.getDay() && date1.getMonth() == date2.getMonth();
}


//3.7 Class scope notation
/*
- Date:: indicates that what follows is within the scope of the class.
- Within class scope, the member functions and member variables are accessible without the name of the object.
*/


//3.8 Constructors
/*
These are special functions that initialize the values of the member variables. You have already used constructors for string+vector
 objects
- The syntax of the call to the constructor mixes variable definitions and function calls. (See date main.cpp)
- “Default constructors” have no arguments
- Multiple constructors are allowed, just like multiple functions with the same name are allowed. The compiler determines which one
   to call based on the types of the arguments (just like any other function call)
- When a new object is created, EXACTLY one constructor for the object is called
*/


//3.9 Member Functions
/*
Member functions are like ordinary functions except:
- They can access and modify the object’s member variables.
- They can call the other member functions without using an object name.
- Their syntax is slightly different because they are defined within class scope.

For the Date class:
- The set and get functions access and change a day, month or year.
- The increment member function uses another member function, isLastDayInMonth.
- isEqual accepts a second Date object and then accesses its values directly using the dot notation. Since we are inside class Date
   scope, this is allowed. The name of the second object, date2, is required to indicate that we are interested in its member
   variables
- lastDayInMonth uses the const array defined at the start of the .cpp file.

More on member functions:
- When the member variables are private, the only means of accessing them and changing them from outside the class is through member
   functions
- If member variables are made public, they can be accessed directly. This is usually considered bad style and should not be used in
   this course
- Functions that are not members of the Date class must interact with Date objects through the class public members (a.k.a., the
   “public interface” declared for the class). One example is the function sameDay which accepts two Date objects and compares them
   by accessing their day and month values through their public member functions
*/


//3.10 Header Files (.h) and Implementation Files (.cpp)
/*
The code for the Date example is in three files:
- The header file, date.h, contains the class declaration
- The implementation file, date.cpp, contains the member function definitions. Note that date.h is #include’ed
- date main.cpp contains the code outside the class. Again date.h again is #include’ed
- Different organizations of the code are possible, but not preferable. In fact, we could have put all of the code from the 3 files
   into a single file main.cpp. In this case, we would not have to compile two separate files
- In many large projects, programmers establish follow a convention with two files per class, one header file and one implementation
   file. This makes the code more manageable and is recommended in this course
- The files date.cpp and date main.cpp are compiled separately and then linked to form the executable program. (You’ll see this
   tomorrow in lab)

First, we compile each source code .cpp file (which incorporate the .h file) and produce date.o and date main.o:
+++++
g++ -c -Wall date.cpp
g++ -c -Wall date main.cpp
+++++
Then, we create the executable date.out:
+++++
g++ -o date.out date.o date main.o
+++++
Alternatively, we can do this all on one line (what we usually do for small programs in this course):
+++++
g++ -Wall -o date.out date.cpp date main.cpp
+++++
*/


//3.11 Constant member functions
/*
Member functions that do not change the member variables should be declared const
- For example: bool Date::isEqual(const Date &date2) const;
- This must appear consistently in both the member function declaration in the class declaration (in the .h file) and in the member
   function definition (in the .cpp file)
- const objects (usually passed into a function as parameters) can ONLY use const member functions.
   (Remember: you should only pass objects by value under special circumstances. In general, pass all objects by reference so they
   aren’t copied, and by const reference if you don’t want/need them to change)
- While you are learning, you will probably make mistakes in determining which member functions should or should not be const. Be
   prepared for compiler warnings and errors, and read them carefully
*/


//3.12 Exercise
/*
Add a member function to the Date class to add a given number of days to the Date object. The number should be
the only argument and it should be an unsigned int. Should this function be const?
*/


//3.13 Classes vs. structs
/*
- Technically, a struct is a class where the default protection is public, not private
	- As mentioned above, when a member variable is public it can be accessed and changed directly using the dot notation:
	   tomorrow.day = 52; We can see immediately why this is dangerous (and an example of bad programming style) because a day of
	   52 is invalid!
- The usual practice of using struct is all public members and no member functions
*/


//3.14 C++ vs. Java Classes
/*
- In C++, classes have sections labeled public and private, but there can be multiple public and private sections. In Java, each
   individual item is tagged public or private
- Class declarations and class definitions are separated in C++, whereas they are together in Java
- In C++ there is a semi-colon at the very end of the class declaration (after the closing curled bracket })
*/


//3.15 C++ vs. Python Classes
/*
- Python classes have a single constructor, init
- Python is dynamically typed - class attributes such as members are defined by assignment
- Python classes do not have private members - privacy is enforced by convention
- Python methods have an explicit self.[variable-name] reference variable
*/


//3.16 Designing and implementing classes
/*
Good software design requires a lot of practice, but here are some ideas to start from:
- Begin by outlining what the class objects should be able to do. This gives a start on the member functions
- Outline what data each object keeps track of, and what member variables are needed for this storage
- Write a draft class declaration in a .h file
- Write code that uses the member functions (e.g., the main function). Revise the class .h file as necessary
- Write the class .cpp file that implements the member functions
In general, don’t be afraid of major rewrites if you find a class isn’t working correctly or isn’t as easy to use as you intended - 
 This happens frequently in practice!
*/


//3.17 Exercise
/*
What happens if the user inputs 2 30 2012 into the program? How would you modify the Date class to make sure
illegal dates are not created?
*/


//3.18 Providing Comparison Functions to Sort
/*
- If we make an STL vector of Date objects, can we sort them? Yes! How?
+++++
std::vector<Date> dates;
dates.push_back(Date(tomorrow));
dates.push_back(Sallys_Birthday);
dates.push_back(Date(10,26,1985));
+++++
- If we used:
+++++
std::sort(dates.begin(), dates.end());
+++++
 the sort function would try to use the < operator on Date objects to sort the dates, just as it uses the < operator on ints or
 floats; however, this doesn’t work because there is no such operator on Date objects

- Fortunately, the sort function can be called with a third argument, a comparison function. E.g.,:
+++++
sort(dates.begin(), dates.end(), earlier_date);
+++++
 Where earlier_date is a helper function we define in date.h and date.cpp that takes two const references to Date objects and
 returns true if and only if the first argument should be considered “less” than the second in the sorted order
+++++
bool earlier_date (const Date& a, const Date& b) {
	if (a.getYear() < b.getYear() ||
	(a.getYear() == b.getYear() && a.getMonth() < b.getMonth()) ||
	(a.getYear() == b.getYear() && a.getMonth() == b.getMonth() && a.getDay() < b.getDay()))
		return true;
	else
		return false;
}
+++++
• That’s great! But wait, how does sort work with STL strings?
*/


//3.19 Operator Overloading
/*
- A second option for sorting is to define a function that creates a < operator for Date objects! At first, this seems a bit weird,
   but it is extremely useful
- Let’s start with syntax. The expressions a < b and x + y are really function calls! Syntactically, they are equivalent to
   operator< (a, b) and operator+ (x, y) respectively.
- When we want to write our own operators, we write them as functions with these weird names.
- For example, if we write:
+++++
bool operator< (const Date& a, const Date& b) {
	return (a.getYear() < b.getYear()
		 || (a.getYear() == b.getYear() && a.getMonth() < b.getMonth())
		 || (a.getYear() == b.getYear() && a.getMonth() == b.getMonth() && a.getDay() < b.getDay()));
}
+++++
 then the statement sort(dates.begin(), dates.end()); will sort Date objects into chronological order
- Really, the only weird thing about operators is their syntax
- We will have many opportunities to write operators throughout this course. Sometimes these will be made class member functions,
   but more on this in a later lecture
*/


//3.20 A Word of Caution about Operators
/*
- Operators should only be defined if their meaning is intuitively clear
- Sorting Date objects makes sense because arguably chronological is the only natural, universally agreed-upon way to do this
- Similarly, sorting STL string objects makes sense because alphabetical is the accepted order. So yes, the STL string class has
   overloaded operator<, and that’s why sorting them works like magic
- In contrast, if we defined a Person class (storing their name, address, social security number, favorite color, etc.), we probably
   wouldn’t agree on how to sort a vector of people. Should it be by name? Or by age? Or by height? Or by income?
   Instead, it would be better to have comparison helper functions that can be used as needed
   (E.g., alpha_by_name, youngest_first, tallest_first, etc.)
*/