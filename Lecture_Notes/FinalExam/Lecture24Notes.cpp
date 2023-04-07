//Lecture 24 - C++ Exceptions

//PREVIOUS LECTURE(S) REVIEW
/*
- Inheritance is a relationship among classes. Examples: bank accounts, polygons, stack & list
- Basic mechanisms of inheritance
- Types of inheritance
- Is-A, Has-A, As-A relationships among classes.
- Polymorphism
*/


//OVERVIEW
/*
- Error handling strategies
- Basic exception mechanisms: try/throw/catch
- Functions & exceptions, constructors & exceptions
- STL exceptions
- RAII “Resource Acquisition is Initialization”
- Structured Exception Handling in the Windows Operating System
- Google’s C++ Style Guide on Exceptions
- Some examples from today’s lecture are drawn from:
   - http://www.cplusplus.com/doc/tutorial/exceptions/
   - https://isocpp.org/wiki/faq/exceptions
*/


//24.1 Error Handling Strategy A: Optimism (a.k.a. Naivete or Denial)
/*
- Assume no errors: Command line arguments will always be proper, any specified files will always be available for read/write, data in 
   files will be formatted correctly, numerical calculations will not attempt to divide by zero, etc.:*/
double answer = numer / denom;
/*
- For small programs, for short term use, by single programmer, where input is well known+controlled, this may not be a disaster (and is
   often fastest to develop + thus a good choice)
- For large programs, this code will be challenging to maintain: can be difficult to pinpoint source of error. The symptom of problem
   (if noticed at all) may be many steps removed from source. The software system maintainer must be familiar with assumptions of code
   (which is difficult if there is a ton of code, the code was written some time ago, by someone else, or is not sufficiently commented,
   or all ofthe above!)
*/


//24.2 Error Handling Strategy B: Plan for the Worst Case (a.k.a. Paranoia)
/*
- Anticipate every mistake/source of error (or as many as you can think of): Write lots of if statements everywhere there may be issue.
   Write code for what to do instead, print out error messages, and/or exit when nothing seems reasonable*/
double answer;
// for some application specific epsilon (often not easy to specify)
double epsilon = 0.00001;
if (fabs(denom)<epsilon) {
   std::cerr<<"detected a divide by zero error"<<std::endl;
   // what to do now? (often there is no "right" thing to do)
   answer = 0;
}
else {answer = numer / denom;}
/*
- Error checking+handling generally requires a lot of programmer time to write all error code, which gets bulkier + harder to
   understand/maintain
- If nested function call might have a problem + error needs to be propagated back up to mus earlier function on the call stack, all
   functions in between must also test for error condition and pass error along. (Messy to code, and all that error checking has
   performance implications)
- Creating comprehensive test suite (yes, error checking/handling code must be tested too) that exercises all error cases is extremely
   time consuming, and some error situations are very difficult to produce
*/


//24.3 Error Handling Strategy C: If/When It Happens We’ll Fix It (a.k.a. Procrastination)
/*
- Again, anticipate everything that might go wrong + call assert in lots of places - can be somewhat less work than the previous option
   (we don’t need to decide what to do if error happens, program exits immediately):*/
double epsilon = 0.00001;
assert (fabs(denom) > epsilon && "!(fabs(denom)>epsilon)");
answer = numer / denom;
/*
- This can be great tool during software development process. Write code to test all (or most) assumptions in each function/code unit -
   Quickly get a prototype system up and running that works for the general, most common, non-error cases first
- If/when unexpected input/condition occurs, additional code can be written to more appropriately handle special cases/errors

- However, use of assertions generally frowned upon in real-world production code (users don’t like to receive seemingly arbitrary +
   total system failures, especially when they paid for software)

- Once you complete testing+debugging + are fairly confident that likely error cases are appropriately handled, then gcc compile flag
   -DNDEBUG flag can be used to remove all remaining assert statements before compiling the code (conveniently removing any performance
   overhead for assert checking)
*/


//24.4 Error Handling Strategy D: The Elegant Industrial-Strength Solution - 
/*
- Use EXCEPTIONS: Somewhat similar to Strategy B, but in practice, code written using exceptions results in more efficient code (and
   less overall code) that is less prone to programming mistakes:*/
double epsilon = 0.00001;
try {
   if (fabs(denom) < epsilon) {throw std::string("divide by zero");}
   double answer = numer / denom;
   /* do lots of other interesting work here with the answer! */
}
catch (std::string &error) {
   std::cerr << "detected a " << error << " error" << std::endl;
   /* what to do in the event of an error */
}


//24.5 Basic Exception Mechanisms: Throw
/*
- When you detect an error, throw an exception. Some examples:*/
throw 20;
throw std::string("hello");
throw Foo(2,5);
/*
- You can throw value of any type (e.g., int, std::string,  custom class instance, etc.)
- When throw statement triggered, rest of that block of code is abandoned
*/


//24.6 Basic Exception Mechanisms: Try/Catch
/*
- If you suspect that code fragment that is about to execute may throw exception + want to prevent program from crashing,  should wrap
   fragment within try/catch block:*/
try {
   /* the code that might throw */
}
catch (int x) {
   /* what to do if the throw happened
   (may use the variable x)
   */
}
/* the rest of the program */
/*
- Logic of try block may throw more than one type of exception
- Catch statement specifies what type of exception it catches (e.g., int, std::string, etc.)

- May use multiple catch blocks to catch different types of exceptions from same try block
- May use*/ catch (...) { /*...*/ } /*to catch all types of exceptions (but don’t get to use value that was thrown)
- If exception is thrown, program searches for closest enclosing try/catch block with appropriate type. That try/catch may be several
   functions away on call stack (might even be all the way back in main())

- If no appropriate catch statement found, program exits, th following may be given: e.g.:
terminate called after throwing an instance of 'bool'
Abort trap
/*


//24.7 Basic Exception Mechanisms: Functions
/*
- If function you are writing might throw exception, you can specify type of exception(s) in prototype:*/
int my_func(int a, int b) throw(double,bool) {
   if (a > b) {throw 20.3;}
   else {throw false;}
}

int main() {
   try {my_func(1,2);}
   catch (double x) {std::cout << " caught a double " << x << std::endl;}
   catch (...) {std::cout << " caught some other type " << std::endl;}
}
/*
- If you use throw syntax in prototype and function throws exception of type that you have not listed, program will terminate
   immediately (can’t be caught by any enclosing try statements)
- If you don’t use throw syntax in prototype, function may throw exception of any type that may be caught by appropriate try/catch block
*/


//24.8 Comparing Method B (explicit if tests) to Method D (exceptions)
/*
- Here’s code using exceptions to sort collection of lines by slope:*/
class Point {
   public:
      Point(double x_, double y_) : x(x_),y(y_) {}
      double x,y;
};
class Line {
   public:
      Line(const Point &a_, const Point &b_) : a(a_),b(b_) {}
      Point a,b;
};

double compute_slope(const Point &a, const Point &b) throw(int) {
   double rise = b.y - a.y;
   double run = b.x - a.x;
   double epsilon = 0.00001;
   if (fabs(run) < epsilon) throw -1; {return rise / run;}
}

double slope(const Line &ln) {return compute_slope(ln.a,ln.b);}

bool steeper_slope(const Line &m, const Line &n) {
   double slope_m = slope(m);
   double slope_n = slope(n);
   return slope_m > slope_n;
}

void organize(std::vector<Line> &lines) {
   std::sort(lines.begin(),lines.end(), steeper_slope);
}

int main () {
   std::vector<Line> lines;
   /* omitting code to initialize some data */
   try {
      organize(lines);
      /* omitting code to print out the results */
   }
   catch (int) {
      std::cout << "error: infinite slope" << std::endl;
   }
}
/*
- Specifically note behavior if one of the lines has infinite slope (vertical line)
- Note also how exception propagates out through several nested function calls

- Exercise: Rewrite code to have the same behavior BUT without exceptions - Try to preserve overall structure of the code as much as
   possible (Hmm...it’s messy)*/



//24.9 STL exception Class
/*
- STL provides base class std::exception through */#include <exception>/* - you can derive your own exception type from exception
   class overwrite what() member function:*/
class myexception: public std::exception {
   virtual const char* what() const throw() {
      return "My exception happened";
   }
};

int main () {
   myexception myex;
   try {throw myex;}
   catch (std::exception& e) {
      std::cout << e.what() << std::endl;
   }
   return 0;
}
/*
- STL library throws several different types of exceptions (all derived from STL exception class):
bad alloc thrown by new on allocation failure
bad cast thrown by dynamic cast (when casting to a reference variable rather than a pointer)
bad exception thrown when an exception type doesn’t match any catch
bad typeid thrown by typeid
ios base::failure thrown by functions in the iostream library
*/


//24.10 Exceptions & Constructors
/*
- Only way for constructor to fail is to throw exception
- Common reason that constructor must fail: failure to allocate memory: if system cannot allocate sufficient memory resources for
   object, bad alloc exception thrown:*/
try {int* myarray= new int[1000];}
catch (std::exception& e) {
   std::cout << "Standard exception: " << e.what() << std::endl;
}
/*
- It can also be useful to have constructor for custom class throw descriptive exception if arguments are invalid in some way
*/


//24.11 Resource Acquisition Is Initialization (RAII)
/*
- Because exceptions might happen at any time, and thus cause program to abandon partially executed function/block of code, it may not
   be appropriate to rely on*/ delete /*call that happens later on in block of code

- RAII describes programming strategy to ensure proper deallocation of memory despite occurrence of exceptions: Goal is to ensure that
   resources are released before exceptions are allowed to propagate
- Variables allocated on stack (not dynamically-allocated using*/ new /*) guaranteed to be properly destructed when variable goes out of
   scope (e.g., when exception is thrown + partially executed block of code/function is abandoned)
- Special care must be taken for dynamically-allocated variables (+ other resources: open files, mutexes, etc.) to ensure that code is
   exception-safe
*/


//24.12 Structured Exception Handing (SEH) in the Windows Operating System
/*
- Windows Operating System has special language support called Structured Exception Handing (SEH) to handle hardware exceptions - some
   examples of hardware exceptions include divide by zero and segmentation faults (there are others)

- In Unix/Linux/Mac OSX these hardware exceptions are instead dealt with using signal handlers; unfortunately, writing error-handling
   code using signal handlers incurs larger performance hit (due to setjmp) + design of error-handling code is less elegant than usual
   C++ exception system because signal handlers are global entities
*/


//24.13 Google’s C++ Style Guide on Exceptions
/*
(https://google.github.io/styleguide/cppguide.html#Exceptions)

Pros:
- Exceptions allow higher levels of an application to decide how to handle “can’t happen” failures in deeply nested functions, without
   the obscuring and error-prone bookkeeping of error codes.
- Exceptions are used by most other modern languages. Using them in C++ would make it more consistent with Python, Java, and the C++
   that others are familiar with.
- Some third-party C++ libraries use exceptions, and turning them off internally makes it harder to integrate with those libraries.
- Exceptions are the only way for a constructor to fail. We can simulate this with a factory function or an Init() method, but these
   require heap allocation or a new “invalid” state, respectively.
- Exceptions are really handy in testing frameworks.

Cons:
- When you add a throw statement to an existing function, you must examine all of its transitive callers. Either they must make at least
   the basic exception safety guarantee, or they must never catch the exception and be happy with the program terminating as a result.
   For instance, if f() calls g() calls h(), and h throws an exception that f catches, g has to be careful or it may not clean up
   properly.
- More generally, exceptions make the control flow of programs difficult to evaluate by looking at code: functions may return in places
   you don’t expect. This causes maintainability and debugging difficulties. You can minimize this cost via some rules on how and where
   exceptions can be used, but at the cost of more that a developer needs to know and understand.
- Exception safety requires both RAII and different coding practices. Lots of supporting machinery is needed to make writing correct
   exception-safe code easy. Further, to avoid requiring readers to understand the entire call graph, exception-safe code must isolate
   logic that writes to persistent state into a “commit” phase. This will have both benefits and costs (perhaps where you’re forced to
   obfuscate code to isolate the commit). Allowing exceptions would force us to always pay those costs even when they’re not worth it.
- Turning on exceptions adds data to each binary produced, increasing compile time (probably slightly) and possibly increasing address
   space pressure.
- The availability of exceptions may encourage developers to throw them when they are not appropriate or recover from them when it’s not
   safe to do so. For example, invalid user input should not cause exceptions to be thrown. We would need to make the style guide even
   longer to document these restrictions!

Decision:
On their face, the benefits of using exceptions outweigh the costs, especially in new projects. However, for existing code, the
 introduction of exceptions has implications on all dependent code. If exceptions can be propagated beyond a new project, it also
 becomes problematic to integrate the new project into existing exception-free code. Because most existing C++ code at Google is not
 prepared to deal with exceptions, it is comparatively difficult to adopt new code that generates exceptions.

Given that Google’s existing code is not exception-tolerant, the costs of using exceptions are somewhat greater than the costs in a new
 project. The conversion process would be slow and error-prone. We don’t believe that the available alternatives to exceptions, such as
 error codes and assertions, introduce a significant burden.

Our advice against using exceptions is not predicated on philosophical or moral grounds, but practical ones. Because we’d like to use
 our open-source projects at Google and it’s difficult to do so if those projects use exceptions, we need to advise against exceptions
 in Google open-source projects as well. Things would probably be different if we had to do it all over again from scratch.

There is an exception to this rule (no pun intended) for Windows code.
*/