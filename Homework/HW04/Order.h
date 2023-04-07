#include <iostream>
#include <string>
#include <list>



#ifndef Order_h_
#define Order_h_

class Order {
	public:
		// CONSTRUCTORS:
		Order();
		Order(int aid, int apromised_time, std::list<std::string> aorderLst);

		// ACCESSORS:
		int getID() const;
		int getPromTime() const;
		int getNumItems() const;
		std::list<std::string> getOrderLst() const;		


		// MODIFIERS:
		void expire();

	private:
		int id;
		int promised_time;
		std::list<std::string> orderLst;
};

std::ostream& operator<<(std::ostream& os, const Order& order);

#endif