HOMEWORK 4: Pizza Event SimulaTOr (PESto)


NAME:  Rueda, Maximillian


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

People:
- Rajgopal, Jayaram, '25
- Paul, Nathan, '25
- Chen, Ivan, '25
- Oren, Itamar, '25
- Emil-Georgiev, Peter, '25
- Thomas, Abin, '25
- Fung, Benson, '25
Websites:
- https://www.youtube.com/watch?v=HKfj0l7ndbc
- https://www.geeksforgeeks.org/nested-list-in-c-stl/
- https://www.geeksforgeeks.org/delete-elements-c-stl-list/#:~:text=Delete%20elements%20in%20C%2B%2B%20STL%20list%201%20Using,of%20the%20value%20passed%20in%20its%20arguments.%20

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  22.75hrs.

ORDER NOTATION:
For each function, using the variables:

  c = number of items still being cooked
  d = number of items completely cooked, but not yet added to an order
  m = number of different item names available
  o = number of orders that have not been filled and are not expired
  p = min number of items per order
  q = max number of items per order

Include a short description of your order notation analysis.

add_order:
O(x + q)
- x = num of items added to Order obj.

add_item:
O(1)
- No loops

print_orders_by_time:
O(o + q)
- Loop through Order objs. and all items within the orders

print_orders_by_id:
O(o + q)
- Loop through Order objs. and all items within the orders

print_kitchen_is_cooking:
O(c)
- Loop through all incomplete Item objs.

print_kitchen_has_completed:
O(d)
- Loop through all complete Item objs.

run_until_next:
O(x + c + q + q)
- x = run time prescribed by user
 - 2nd q = items to fill order

run_for_time:
O(x + c + p + q)
- x = run time until event happens
- q = items to fill order



MISC. COMMENTS TO GRADER:  
Optional, please be concise!






