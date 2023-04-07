//Lecture 22 – C++ Inheritance and Polymorphism

//OVERVIEW
/*
- Inheritance is a relationship among classes. Examples: bank accounts, polygons, stack & list
- Basic mechanisms of inheritance
- Types of inheritance
- Is-A, Has-A, As-A relationships among classes
- Polymorphism
*/


//22.1 Motivating Example: Bank Accounts
/*
- Consider different types of bank accounts:
   - Savings accounts
   - Checking accounts
   - Time withdrawal accounts (like savings accounts, except only interest earned can be withdrawn)
- If you were designing C++ classes to represent each, what member functions might be repeated among them? What member functions would be
   unique?
- To avoid repeating common member functions+variables, we will create class hierarchy, where common members are placed in a base class +
   specialized members are placed in derived classes
*/


//22.2 Accounts Hierarchy
/*
- Account = BASE CLASS of hierarchy
- SavingsAccount = DERIVED CLASS from Account; SavingsAccount has INHERITED member variables+functions + ordinarily-defined member
   variables+functions = "SavingsAccout is a [kind of] Account"
- Member variable "balance" in base class Account is PROTECTED, which means:
   - "balance" NOT publicly accessible outside class, but is accessible in derived classes (think "a more public private variable")
   - if "balance" declared as private, SavingsAccount member functions could not access it

- When using objects of type SavingsAccount, inherited+derived members treated exactly same + are indistinguishable from each other
- CheckingAccount = also derived class from Account
- TimeAccount derived from SavingsAccount: SavingsAccount = base class, Account = INDIRECT base class
*/


//22.3 Exercise: Draw the Accounts Class Hierarchy
#include <iostream>
#include <cassert>

// Note we've inlined all the functions (even though some are > 1 line of code)
class Account {
   public:
      Account(double bal = 0.0) : balance(bal) {}
      void deposit(double amt) { balance += amt; }
      double get_balance() const { return balance; }
   protected:
      double balance; // account balance
};
class SavingsAccount : public Account {
   public:
      SavingsAccount(double bal = 0.0, double pct = 5.0) : Account(bal), rate(pct/100.0) {}
      double compound() { // computes and deposits interest
         double interest = balance * rate;
         balance += interest;
         return interest;
      }
      double withdraw(double amt) { // if overdraft ==> return 0, else return amount
         if (amt > balance) { return 0.0; }
         else {
            balance -= amt;
            return amt;
         }
      }
   protected:
      double rate; // periodic interest rate
};
class CheckingAccount : public Account {
   public:
      CheckingAccount(double bal = 0.0, double lim = 500.0, double chg = 0.5) : Account(bal), limit(lim), charge(chg) {}
      double cash_check(double amt) {
         assert (amt > 0);
         if (balance < limit && (amt + charge <= balance)) {
            balance -= amt + charge;
            return amt + charge;
         } else if (balance >= limit && amt <= balance) {
            balance -= amt;
            return amt;
         } else { return 0.0; }
      }
   protected:
      double limit; // lower limit for free checking
      double charge; // per check charge
};
class TimeAccount : public SavingsAccount {
   public:
      TimeAccount(double bal = 0.0, double pct = 5.0) : SavingsAccount(bal, pct), funds_avail(0.0) {}
      // redefines 2 member functions from SavingsAccount
      double compound() {
         double interest = SavingsAccount::compound();
         funds_avail += interest;
         return interest;
      }
      double withdraw(double amt) {
         if (amt <= funds_avail) {
            funds_avail -= amt;
            balance -= amt;
            return amt;
         } else { return 0.0; }
      }
      double get_avail() const { return funds_avail; };
   protected:
      double funds_avail; // amount available for withdrawal
};


Account a(100); //<---one balance member, not related to c1
CheckingAccount c1(100, 366, 0.4); //c1 has it's own CheckingAccount + Account objects <---one balance member


//22.4 Constructors and Destructors
/*
- Constructors of derived class call base class constructor immediately before doing ANYTHING else
   - The only thing you can control is which constructor is called + its passed arguments
   - When a TimeAccount is created, 3 constructors called: Account constructor, SavingsAccount constructor, and TimeAccount constructor

- Reverse is true for destructors: derived class destructors do their jobs first, then base class destructors called at end automatically
   - (Note: destructors for classes w/ derived classes must be marked VIRTUAL for chain of calls to happen)
*/


//22.5 Overriding Member Functions in Derived Classes
/*
- Derived class can redefine member functions in base class - function prototype must be identical; even using const can be different
   (otherwise both functions will be accessible)
- For example, see TimeAccount::compound and TimeAccount::withdraw

- Once function is redefined, no longer possible to call base class function unless explicitly called (e.g. call to
   SavingsAccount::compound inside of TimeAccount::compound)
*/


//22.6 Public, Private and Protected Inheritance
/*
- Notice Line 52:*/ class Savings_Account : public Account {/*
   - This specifies that member functions+variables from Account don't change their public, protected or private status in SavingsAccount
      - This is called PUBLIC INHERITANCE
- PROTECTED and PRIVATE inheritance are other options:
   - Protected inheritance - public members become protected, other members unchanged
   - Private inheritance - all members become private
*/


//22.7 Stack Inheriting from List
/*
- For another example of inheritance, let’s re-implement stack class as derived class of std::list:*/
template <class T>
class stack : private std::list<T> {
   public:
      stack() {}
      stack(stack<T> const& other) : std::list<T>(other) {}
      ~stack() {}

      void push(T const& value) { this->push_back(value); }
      void pop() { this->pop_back(); }
      T const& top() const { return this->back(); }
      int size() { return std::list<T>::size(); }
      bool empty() { return std::list<T>::empty(); }
};
/*
- Private inheritance hides std::list<T> member functions from outside world; however, these member functions = still available to member
   functions of stack<T> class
- (Note: no member variables defined — only member variables needed are in list class)

- When stack member function uses same name as base class (list) member function, name of base class followed by :: must be provided to
   indicate that base class member function should be used
- Copy constructor just uses copy constructor of base class without any special designation because stack object = list object as well
*/


//22.8 Is-A, Has-A, and As-A Relationships Among Classes
/*
- When trying to determine relationships btwn (hypothetical) classes C1 and C2, try to think of logical relationship btwn them that can be
   written:
   - C1 is a C2,
   - C1 has a C2, or
   - C1 is implemented as a C2

- If writing “C1 is-a C2” is best (e.g. “a savings account is an account”), then C1 should be derived class (a subclass) of C2
- If writing “C1 has-a C2” is best (e.g. “a cylinder has a circle as its base”), then class C1 should have member variable of type C2
- In the case of “C1 is implemented as-a C2” (e.g. “the stack is implemented as a list”), then C1 should be derived from C2 but w/ private
   inheritance (least common case by far, don't fret)
*/


//22.9 Exercise: 2D Geometric Primitives
/*
- Create class hierarchy of geometric objects, such as: triangle, isosceles triangle, right triangle, quadrilateral, square, rhombus,
   kite, trapezoid, circle, ellipse, etc. How should this hierarchy be arranged? What member variables+functions should be in each class?

Shapes Class Heirarchy:
            Ellipse     Polygon        Circle
                        /     \
                  Triangle    Quadrilateral
                                    |
                              Parallelogram
                                 /     \
                           Rhombus     Rectangle
                                 \     /
                                 Square
Now we have this diamond shape: one class has to parents - this is 
*/


//22.10 Note: Multiple Inheritance
/*
- When sketching class hierarchy for geometric objects, you may have wanted to specify relationships that were more complex...in
   particular, some objects may wish to inherit from more than one base class
- This is called MULTIPLE INHERITANCE, which can make many implementation details significantly more hairy - different languages offer
   different variations of multiple inheritance:

(refer to notes hand-out for diagrams)

an instance of class C
Normally, inheritance just adds layers, like an onion or Russian nesting doll
In each layer, we store member variables for that class

an instance of class F
With multiple inheritance, this could lead to duplicate copies of member variables for classes A and B
DO NOT DO THIS

an instance of class F
Instead, we INHERIT VIRTUALLY, which requires separate construction of parts of diagram that's marked "virtual"
This ensures we have single unambiguous copy of member variable data for A & B

an instance of class G
Note that even if a class does not itself use multiple inheritance, it may still have virtual inheritance on its path + require separate
 construction
*/


//22.11 Introduction to Polymorphism
/*
- Let’s consider a small class hierarchy version of polygonal objects:*/
class Polygon {
   public:
      Polygon() {}
      virtual ~Polygon() {}
      int NumVerts() { return verts.size(); }
      virtual double Area() = 0;
      virtual bool IsSquare() { return false; }
   
   protected:
      vector<Point> verts;
};
class Triangle : public Polygon {
   public:
      Triangle(Point pts[3]) {
         for (int i = 0; i < 3; i++) { verts.push_back(pts[i]); }
      }
      double Area();
};
class Quadrilateral : public Polygon {
   public:
      Quadrilateral(Point pts[4]) {
         for (int i = 0; i < 4; i++) { verts.push_back(pts[i]); }
      }
      double Area();
      double LongerDiagonal();
      bool IsSquare() { return (SidesEqual() && AnglesEqual()); }
   private:
      bool SidesEqual();
      bool AnglesEqual();
};
/*
- Functions that are common, or at least have common interface, are in Polygon
- Some of these functions = marked "VIRTUAL": when they are redefined by derived class, this new definition will be used, even for
   pointers to base class objects
- Some of these virtual functions, those whose declarations are followed by*/ = 0 /*are PURE VIRTUAL, which means they must be redefined
   in some derived class
   - Any class w/ pure virtual functions called “abstract”.
   - Objects of abstract types may not be created — only pointers to these objects may be created
- Functions specific to particular object type are declared in derived class prototype
*/


//22.12 A Polymorphic List of Polygon Objects
/*
- Now, instead of two separate lists of polygon objects, we can create one “POLYMORPHIC” list:*/
std::list<Polygon*> polygons;
/*
- Objects are constructed using new and inserted into the list:*/
Polygon *p_ptr = new Triangle( /*...*/ );
polygons.push_back(p_ptr);

p_ptr = new Quadrilateral( /*...*/ );
polygons.push_back(p_ptr);

Triangle *t_ptr = new Triangle( /*...*/ );
polygons.push_back(t_ptr);
/*
   (Note: We’ve used same pointer variable (p_ptr) to point to objects of two different types
*/


//22.13 Accessing Objects Through a Polymorphic List of Pointers
/*
- Let’s sum the areas of all the polygons:*/
double area = 0;
for (std::list<Polygon*>::iterator i = polygons.begin(); i!=polygons.end(); ++i) { area += (*i)->Area(); }
/*
- Which Area function is called?
ANSWER: If *i points to Triangle object, then function defined in Triangle class would be called.

- If *i points to a Quadrilateral object then Quadrilateral::Area will be called

- Here’s code to count the number of squares in the list:*/
int count = 0;
for (std::list<Polygon*>::iterator i = polygons.begin(); i!=polygons.end(); ++i) { count += (*i)->IsSquare(); }
/*
- If Polygon::IsSquare had not been declared virtual, then function defined in Polygon would always be called!
   - In general, given a pointer to type T, we start at T and look “up” the hierarchy for closest function definition (this can be done at
      compile time) - if that function has been declared virtual, we will start this search instead at actual type of object (this
      requires additional work at runtime) in case it has been redefined in some derived class of type T

- To use function in Quadrilateral that isn't declared in Polygon, must CAST” pointer; pointer *q will be NULL if *i not Quadrilateral
   object*/
for (std::list<Polygon*>::iterator i = polygons.begin(); i!=polygons.end(); ++i) {
   Quadrilateral *q = dynamic_cast<Quadrilateral*> (*i);
   if (q) { std::cout << "diagonal: " << q->LongerDiagonal() << std::endl; }
}


//22.14 Exercise
/*
- What is the output of the following program?*/
class Base {
   public:
      Base() {}
      virtual void A() { std::cout << "Base A "; }
      void B() { std::cout << "Base B "; }
};
class One : public Base {
   public:
      One() {}
      void A() { std::cout << "One A "; }
      void B() { std::cout << "One B "; }
};
class Two : public Base {
   public:
      Two() {}
      void A() { std::cout << "Two A "; }
      void B() { std::cout << "Two B "; }
};

int main() {
   Base* a[3];
   a[0] = new Base;
   a[1] = new One;
   a[2] = new Two;
   for (unsigned int i=0; i<3; ++i) {
      a[i]->A();
      a[i]->B();
   }
   std::cout << std::endl;
   return 0;
}
/*
ANSWER:

*/