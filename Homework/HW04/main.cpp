// ==================================================================
// Important Note: You are encouraged to read through this provided
//   code carefully and follow this structure.  You may modify the
//   file as needed to complete your implementation.
// ==================================================================

/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Homework/HW04
g++ -g -Wall -std=c++11 -o main.out *.cpp
./main.out
./main.out < input_medium.txt
./main.out < NEW.txt
~/DrMemory-Linux-2.4.0-2/bin64/drmemory -brief -- main.out
*/

#include <cassert>
#include <iostream>
#include <string>
#include <list>
#include <algorithm>

#include "Order.h"
#include "Item.h"


typedef std::list<Order> OrderList;
typedef std::list<Item> KitchenList;

//Needed for CanFillOrder()
typedef std::list <KitchenList::const_iterator> OrderFillList;
typedef std::list <KitchenList::const_iterator>::iterator OrdFlLstIterator;

typedef std::list<Order>::iterator orderLstIterator;
typedef std::list<Item>::iterator itemLstIterator;
typedef std::list<std::string>::const_iterator stringIterator;



//HELPER FUNCTIONS:
//CanFillOrder() - returns true if order can be fulfilled,
// and false otherwise. If true, then items_to_remove has
// iterators to kitchen_completed for all items that are
// used in the order
bool CanFillOrder(const Order &order,
                  const KitchenList &kitchen_completed,
                        OrderFillList &items_to_remove);

//AddItemSort() - whenever new item object is put into
// food_cooking, it is sorted based on time and then name
bool AddItemSort(const Item &item1, const Item &item2) {
  if (item1.getTime()<item2.getTime()) {return true;}
  else if (item1.getTime()==item2.getTime()) {
    if (item1.getName()<item2.getName()) {return true;}
    else {return false;}
  }
  else {return false;}
}

//ByTime() - one of two functions to sort orders - this
// function first sorts by time and then by ID
bool ByTime(const Order &order1, const Order &order2) {
  if (order1.getPromTime()<order2.getPromTime()) {return true;}
  else if (order1.getPromTime()==order2.getPromTime()) {
    if (order1.getID()<order2.getID()) {return true;}
    else {return false;}
  }
  else {return false;}
}

//ByID() - one of two functions to sort orders - this
// function simply sorts by ID since IDs are unique
bool ByID(const Order &order1, const Order &order2) {
  if (order1.getID()<order2.getID()) {return true;}
  else {return false;}
}





int main() {
  OrderList orders;                                                             // Lists that will containorder and item objects
  KitchenList food_cooking;
  KitchenList food_completed;

  std::string token;
  while (std::cin >> token) {                                                   // Will continually ask for input without stopping
    if (token == "add_order") {
      int id, promised_time, n_items = 0;
      std::string next_item;
      std::list<std::string> order_items;

      std::cin >> id >> promised_time >> n_items;
      assert(n_items > 0);

      for (int i = 0; i < n_items; i++) {
        std::cin >> next_item;
        order_items.push_back(next_item);
      }                                                                         // Above code previously implemented
      
      std::cout<<"Received new order #"<<id                                     // Output statement displaying user input
               <<" due in "<<promised_time
               <<" minute(s):"<<std::endl;
      stringIterator ao_itr = order_items.begin();                              // Iterator and while-loop to print each item in order
      while (ao_itr!=order_items.end()) {
        std::cout<<"  "<<(*ao_itr)<<std::endl;
        ao_itr++;
      }

      orders.push_back(Order(id, promised_time, order_items));                  // Order object created and added to list of orders
      orders.sort(ByTime);                                                      // Orders then sorted


    } else if (token == "add_item") {
      int cook_time = -1;
      std::string name;
      std::cin >> cook_time >> name;
      assert(cook_time >= 0);                                                   // Above code previously implemented

      std::cout<<"Cooking new "                                                 // Output statement displaying user input
               <<name<<" with "
               <<cook_time<<" minute(s) left."
               <<std::endl;
      food_cooking.push_back(Item(name, cook_time));                            // Item object created and added to list of orders
      food_cooking.sort(AddItemSort);                                           // Orders then sorted


    } else if (token == "print_orders_by_time") {
      orders.sort(ByTime);                                                      // Orders sorted by time to print properly
      std::cout<<"Printing "<<orders.size()
               <<" order(s) by promised time remaining:"
               <<std::endl;
      orderLstIterator pobt_itr = orders.begin();                               // Iterator and while-loop to go through all orders
      while (pobt_itr!=orders.end()) {
        std::cout<<"  #"<<(*pobt_itr).getID()
                 <<" ("<<(*pobt_itr).getPromTime()<<" minute(s) left):"
                 <<std::endl;
        const std::list<std::string> miniLst = (*pobt_itr).getOrderLst();       // Every order's item list stored in variable to iterate
        stringIterator mini_itr = miniLst.begin();                              // Iterator and while-loop to show all items in order
        while (mini_itr!=miniLst.end()) {
          std::cout<<"    "<<(*mini_itr)<<std::endl;
          mini_itr++;
        }
        pobt_itr++;
      }
    

    } else if (token == "print_orders_by_id") {
      orders.sort(ByID);                                                        // Orders sorted by ID to print properly
      std::cout<<"Printing "<<orders.size()
               <<" order(s) by ID:"<<std::endl;
      orderLstIterator pobi_itr = orders.begin();                               // Iterator and while-loop to go through all orders
      while (pobi_itr!=orders.end()) {
        std::cout<<"  #"<<(*pobi_itr).getID()
                 <<" ("<<(*pobi_itr).getPromTime()
                 <<" minute(s) left):"<<std::endl;
        const std::list<std::string> miniLst = (*pobi_itr).getOrderLst();       // Every order's item list stored in variable to iterate
        stringIterator mini_itr = miniLst.begin();                              // Iterator and while-loop to show all items in order
        while (mini_itr!=miniLst.end()) {
          std::cout<<"    "<<(*mini_itr)<<std::endl;
          mini_itr++;
        }
        pobi_itr++;
      }
    

    } else if (token == "print_kitchen_is_cooking") {
      food_cooking.sort(AddItemSort);
      std::cout<<"Printing "<<food_cooking.size()
               <<" items being cooked:"<<std::endl;
      itemLstIterator pkic_itr = food_cooking.begin();                          // Iterator and while-loop to go through cooking items
      while (pkic_itr!=food_cooking.end()) {
        std::cout<<"  "<<(*pkic_itr).getName()
                 <<" ("<<(*pkic_itr).getTime()
                 <<" minute(s) left)"<<std::endl;
        pkic_itr++;
      }


    } else if (token == "print_kitchen_has_completed") {
      std::cout<<"Printing "<<food_completed.size()
               <<" completely cooked items:"<<std::endl;
      itemLstIterator pkhc_itr = food_completed.begin();                        // Iterator and while-loop to go through completed items
      while (pkhc_itr!=food_completed.end()) {
        std::cout<<"  "<<(*pkhc_itr).getName()<<std::endl;
        pkhc_itr++;
      }


    } else if (token == "run_for_time") {
      int run_time = 0;
      std::cin >> run_time;
      assert(run_time >= 0);                                                    // Above code previously implemented

      std::cout<<"===Starting run of "<<run_time<<" minute(s)==="<<std::endl;
      OrderFillList items_to_remove;                                            // OrderFillList list declared for later use
      
      for (int i=0 ; i<=run_time ; ++i) {                                       // For however long run_time is...
        
        itemLstIterator itItr = food_cooking.begin();                             // Iterator and while-loop to go through cooking items
        while (itItr!=food_cooking.end()) {
          if ((*itItr).getTime()==0) {                                              // If done cooking...
            std::cout<<"Finished cooking "<<(*itItr).getName()<<std::endl;
            food_completed.push_back((*itItr));                                       // Item obj pushed into completed food list
            itItr = food_cooking.erase((itItr));                                      // Item removed from cooking food list
          }
          else {(*itItr).cook(); itItr++;}                                          // If not done, cook food for 1 minute
        }
        
        orders.sort(ByTime);                                                      // All Order objs sorted by time
        orderLstIterator ordItr = orders.begin();                                 // Iterator and while-loop to go through orders
        while (ordItr!=orders.end()) {
          if (CanFillOrder((*ordItr), food_completed, items_to_remove)) {           // If order can be filled based on CanFillOrder()...
            std::cout<<"Filled order #"<<(*ordItr).getID()<<std::endl;
            OrdFlLstIterator oflItr = items_to_remove.begin();                        // Newly filled list of iterators looped through
            while (oflItr!=items_to_remove.end()) {
              std::cout<<"Removed a "<<(*(*oflItr)).getName()
                       <<" from completed items."<<std::endl;
              food_completed.erase((*oflItr));                                          // Delete Item objs that iterators point to
              oflItr++;
            }
            ordItr = orders.erase((ordItr));                                          // Delete order from list of orders
          }
          else {                                                                    // Else if order can't be fulfilled...
            if ((*ordItr).getPromTime()==0) {                                         // If order is due can can't be fulfilled...
              std::cout<<"Order # "<<(*ordItr).getID()
                       <<" expired."<<std::endl;
              ordItr = orders.erase((ordItr));                                          // Remove order from list
            }
            else {(*ordItr).expire(); ordItr++;}                                      // If order not due yet, let time expire for 1 min.
          }
        }
      }
      std::cout<<"===Run for specified time is complete==="<<std::endl;

    
    } else if (token == "run_until_next") {
      std::cout << "Running until next event." << std::endl;
      unsigned int timePassed = 0;                                              // int counter to keep track of time
      OrderFillList items_to_remove;                                            // OrderFillList list declared for later use

      bool bfFlag = false;                                                      // "Flag" to signal different output at end of loop
      // for (int special=0 ; special<50 ; special++)
      while (true) {                                                            // Will run infinitely until 1 event occurs 
        
        if (food_cooking.size()==0 && orders.size()==0) {break;}                  // If there is nothing to do, break completely

        itemLstIterator itItr = food_cooking.begin();                             // Iterator and while-loop to go through cooking items
        while (itItr!=food_cooking.end()) {
          if ((*itItr).getTime()==0) {                                              // If done cooking...
            std::cout<<"Finished cooking "<<(*itItr).getName()<<std::endl;
            food_completed.push_back((*itItr));                                       // Item obj pushed into completed food list
            itItr = food_cooking.erase((itItr));                                      // Item removed from cooking food list
            bfFlag = true; break;                                                     // Event has occured - switch flag and break
          }
          else {(*itItr).cook(); itItr++;}                                          // If not done, cook food for 1 minute
        }
        if (bfFlag) {break;}                                                      // If event occured, break from while-loop

        orders.sort(ByTime);                                                      // All Order objs sorted by time
        orderLstIterator ordItr = orders.begin();                                 // Iterator and while-loop to go through orders
        while (ordItr!=orders.end()) {
          if (CanFillOrder((*ordItr), food_completed, items_to_remove)) {           // If order can be filled based on CanFillOrder()...
            std::cout<<"Filled order #"<<(*ordItr).getID()<<std::endl;
            OrdFlLstIterator oflItr = items_to_remove.begin();                        // Newly filled list of iterators looped through
            while (oflItr!=items_to_remove.end()) {
              std::cout<<"Removed a "<<(*(*oflItr)).getName()
                       <<" from completed items."<<std::endl;
              food_completed.erase((*oflItr));                                          // Delete Item objs that iterators point to
              oflItr++;
            }
            ordItr = orders.erase((ordItr));                                          // Delete order from list of orders
            bfFlag = true; break;                                                     // Event has occured - switch flag and break
          }
          else {                                                                    // Else if order can't be fulfilled...
            if ((*ordItr).getPromTime()==0) {                                         // If order is due can can't be fulfilled...
              std::cout<<"Order # "<<(*ordItr).getID()
                       <<" expired."<<std::endl;
              ordItr = orders.erase((ordItr));                                          // Remove order from list
              bfFlag = true; break;                                                     // Event has occured - switch flag and break
            }
            else {(*ordItr).expire(); ordItr++;}                                      // If order not due yet, let time expire for 1 min.
          }
        }
        if (bfFlag) {break;}                                                      // If event occured, break from while-loop
        
        timePassed+=1;                                                            // If no event has occured, increase time passed by 1
      }
      if (!bfFlag) {std::cout<<"No events waiting to process."<<std::endl;}       // Output statement based on if flag was switched
      else {std::cout<<timePassed<<" minute(s) have passed."<<std::endl;}
    }
  }

  return 0;
}





bool CanFillOrder(const Order &order, const KitchenList &kitchen_completed,     // Below code previously implemented...
                  OrderFillList &items_to_remove) {
  items_to_remove.clear(); //We will use this to return iterators in kitchen_completed

  //Simple solution is nested for loop, but I can do better with sorting...

  std::list <std::string> order_items = order.getOrderLst();  // CHANGE FROM getItems() TO getOrderLst()
  order_items.sort();

  std::list<std::string>::const_iterator item_it;
  std::string prev_item = "";
  KitchenList::const_iterator kitchen_it;

  for (item_it = order_items.begin(); item_it != order_items.end(); item_it++) {
    bool found = false;

    /*Start back at beginnging of list if we're looking for something else
     *Thanks to sorting the order_items list copy, we know we're done with
       whatever kind of item prev_item was!*/
    if (prev_item != *item_it) {
      kitchen_it = kitchen_completed.begin();
      prev_item = *item_it;
    }

    /*Resume search wherever we left off last time (or beginning if it's a
    new kind of item*/
    for (; !found && kitchen_it != kitchen_completed.end(); kitchen_it++) {
      if (kitchen_it->getName() == *item_it) {
        items_to_remove.push_back(kitchen_it);
        found = true;
      }
    }

    //If we failed to satisfy an element of the order, no point continuing the search
    if (!found) {
      break;
    }
  }

  //If we couldn't fulfill the order, return an empty list
  if (items_to_remove.size() != order_items.size()) {
    items_to_remove.clear();
    return false;
  }

  return true;
}