//Lecture 14 – Operators & Friends

//PREVIOUS LECTURE(S) REVIEW
/*
- How to design and implement algorithms using three steps or stages:
   1. Generating and Evaluating Ideas
   2. Mapping Ideas into Code
   3. Getting the Details Right
- Lots of Examples
*/


//OVERVIEW
/*
- Operators as non-member functions, as member functions, and as friend functions
- Homework 6 preview
*/


//14.1 Complex Numbers — A Brief Review
/*
- Complex numbers take the form z = a+bi, where i = √(−1) and a and b are real; a is called the real part, b is called the imaginary part
- If w = c+di, then:
	- w+z = (a+c) + (b+d)i,
	- w−z = (a−c) + (b−d)i, and
	- w*z = (ac−bd) + (ad+bc)i
- The magnitude of a complex number is √(a^2 + b^2)
*/


//14.2 Complex Class declaration (complex.h)
class Complex {
	public:
		// CONSTRUCTORS:
		Complex(double x=0, double y=0) : real_(x), imag_(y) {} // default constructor
		Complex(Complex const& old) : real_(old.real_), imag_(old.imag_) {} // copy constructor

		// GETTERS:
		double Real() const { return real_; }
		double Imaginary() const { return imag_; }
		double Magnitude() const { return sqrt(real_*real_ + imag_*imag_); }

		// SETTERS:
		void SetReal(double x) { real_ = x; }
		void SetImaginary(double y) { imag_ = y; }
		
		// OTHERS:
		Complex& operator= (Complex const& rhs); // Assignment operator
		Complex operator+ (Complex const& rhs) const; // binary operator+ will add values
		Complex operator- () const; // unary operator- negates a complex number

		//in-/output stream operators can't be member functions but can be friends/non-member
		// functions if work can be accomplished through public interface to class
		friend istream& operator>> (istream& istr, Complex& c);
	
	private:
	double real_, imag_;
};

Complex operator- (Complex const& left, Complex const& right); // non-member function
ostream& operator<< (ostream& ostr, Complex const& c); // non-member function


//14.3 Implementation of Complex Class (complex.cpp)
// Assignment operator
Complex& Complex::operator= (Complex const& rhs) {
	real_ = rhs.real_;
	imag_ = rhs.imag_;
	return *this;
}

// Addition operator as a member function
Complex Complex::operator+ (Complex const& rhs) const {
	double re = real_ + rhs.real_;
	double im = imag_ + rhs.imag_;
	return Complex(re, im); // Note: not returned by reference - new value, so return copy
}

// Subtraction operator as a non-member function.
Complex operator- (Complex const& lhs, Complex const& rhs) {
	return Complex(lhs.Real()-rhs.Real(), lhs.Imaginary()-rhs.Imaginary());
}

// Unary negation operator. Note that there are no arguments.
Complex Complex::operator- () const {
	return Complex(-real_, -imag_);
}

// Input stream operator as a friend function
istream& operator>> (istream & istr, Complex & c) {
	istr >> c.real_ >> c.imag_;
	return istr;
}

// Output stream operator as an ordinary non-member function
ostream& operator<< (ostream & ostr, Complex const& c) {
	if (c.Imaginary() < 0) {ostr<<c.Real()<<" - "<<(-c.Imaginary())<<" i ";}
	else {ostr<<c.Real()<<" + "<<c.Imaginary()<<" i ";}
	return ostr;
}


//14.4 Operators as Non-Member Functions and as Member Functions
/*
- We've already written our own operators, especially operator<, to sort objects stored in STL containers and to create our own keys for
   maps

- We can write them as non-member functions (e.g., operator-): when implemented as a non-member function, the expression:*/ z-w /*is
   translated by the compiler into the function call:*/ operator-(z, w) /*- this is "a function that can be performed on this object type"
- We can also write them as member functions (e.g., operator+): when implemented as a member function, the expression:*/ z+w /*is
   translated into:*/ z.operator+(w) /*- this is "a member function/method that an object can do" - this shows that operator+ is a member
   function of z, since z appears on the left-hand side of the operator (Observe that the function has only one argument)

There are several important properties of the implementation of an operator as a member function:
	- It is within the scope of class Complex, so private member variables can be accessed directly
	- The member variables of z, whose member function is actually called, are referenced by directly by name
	- The member variables of w are accessed through the parameter rhs
	- The member function is const, which means that z will not (and cannot) be changed by the function
	   (Also, w will not be changed since the argument is also marked const)

- Both operator+ and operator- return Complex objects, so both must call Complex constructors to create these objects - calling
   constructors for Complex objects inside functions, especially member functions that work on Complex objects, seems somewhat
   counter-intuitive at first, but it is common practice!
*/


//14.5 Assignment Operators
/*
- The assignment operator:*/ z1=z2; /*becomes a function call:*/ z1.operator=(z2);
   /*And cascaded assignments like:*/ z1=z2=z3; /*are really:*/ z1=(z2=z3); /*which becomes:*/ z1.operator=(z2.operator=(z3));
   /*Studying these helps to explain how to write the assignment operator, which is usually a member function

- The argument (operator's right side) is passed by const-ref: its values are used to change the contents of the left side of the operator
   which is the object whose member function is called - a reference to this object is returned, allowing a subsequent call to operator=,
   which is z1’s operator= in the example above
   The identifier this is reserved as a pointer inside class scope to the object whose member function is called
   Therefore, *this is a reference to this object

- The fact that operator= returns a reference allows us to write code of the form: (z1=z2).real();
*/


//14.6 Exercise
/*
- Write an operator+= as a member function of the Complex class. To do so, you must combine what you learned about operator= and operator+
  In particular, the new operator must return a reference, *this
*/
Complex& Complex::operator+=(const Complex& rhs) {
	real_ = real_ + rhs.real_;
	imag_ = imag_ + rhs.imag_;
	return *this;
}


//14.7 Returning Objects vs. Returning References to Objects
/*
- In operator+ and operator-, we create new Complex objects and simply return the new objectof type Complex (goes for both functions)
   Technically, we don’t return the new object (which is stored only locally and will disappear once the scope of the function is exited);
   instead we create a copy of the object and return the copy - this automatic copying happens outside of the scope of the function, so it
   is safe to access outside of the function.
   (Note: It’s important that the copy constructor is correctly implemented! Good compilers can minimize the amount of redundant copying
   without introducing semantic errors)

- When you change an existing object inside an operator and need to return that object, you must return a reference to that object - this
   is why the return types of operator= and operator+= are both Complex&: to avoid creation of a new object

- A common error made by beginners (and some non-beginners) is attempting to return a reference to a locally created object! This results
   in someone having a pointer to stale memory: the pointer may behave correctly for a short while... until the memory under the pointer
   is allocated and used by someone else
*/


//14.8 Friend Classes vs. Friend Functions
/*
- In the example below, the Foo class has designated the Bar class to be a friend; this must be done in the public area of the
   declaration of Foo:*/
class Foo {
	public:
		friend class Bar;
		...
};
/*
   This allows member functions in class Bar to access all of the private member functions and variables of a Foo object as though they
   were public (but not vice versa)
   (Note: Foo is giving friendship (access to its private contents) rather than Bar claiming it: what could go wrong if we allowed
   friendships to be claimed?)
   ANSWER: 
*/


//14.9 Stream Operators as Friend Functions
/*
- operator>> and operator<< are defined for the Complex class - these are binary operators
   The compiler translates:*/ cout<<z3 /*into:*/ operator<<(cout, z3)
   /*Consecutive calls to operator<<, such as:*/ cout<<"z3 = "<<z3<<endl; /*are translated into:*/ ((cout<<"z3=")<<z3)<<endl;
   /*Each application of the operator returns an ostream object so that the next application can occur

- If we wanted to make one of these stream operators a regular member function, it would have to be a member function of the ostream class
   because this is the first argument (left operand). We cannot make it a member function of the Complex class - this is why stream
   operators are never member functions

- Stream operators are either ordinary non-member functions (if the operators can do their work through the public class interface) or
   friend functions (if they need non public access)
*/


//14.10 Summary of Operator Overloading in C++
/*
- Unary operators that can be overloaded:
+, -, *, &, ~, !, ++, --, ->, and ->*

- Binary operators that can be overloaded:
+, -, *, /, %, ^, &, |, <<, >>, +=, -=, *=, /=, %=, ^=, &=, |=, <<=, >>=, <, <=, >, >=, ==, !=, &&, ||, ,, [], (), new, new[], delete, delete[]

- There are only a few operators that can not be overloaded: ., .*, ?:, and ::

- We can’t create new operators and we can’t change the number of arguments (except for the function call operator, which has a variable
   number of arguments)
- There are three different ways to overload an operator - when there is a choice, we recommend trying to write operators in this order:
	- Non-member function
	- Member function
	- Friend function
- The most important rule for clean class design involving operators is to NEVER CHANGE INTUITIVE MEANING of an operator. The whole point
   of operators is lost if you do. One (bad) example would be defining the increment operator on a Complex number
*/


//14.11 Extra Practice
/*
- Implement the following operators for the Complex class (or explain why they can't/shouldn't be implemented).
   Think about whether they should be non-member, member, or friend:
operator*
operator==
operator!=
operator<
*/