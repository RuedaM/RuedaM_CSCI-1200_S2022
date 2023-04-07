#include <iostream>
#include <string>
#include <list>

#include "Order.h"



// CONSTRUCTORS:
Order::Order() {
	id = 0;
	promised_time = 0;
	orderLst.push_back("NULL");
}

Order::Order(int aid, int apromised_time, std::list<std::string> aorderLst) {
	id = aid;
	promised_time = apromised_time;
	orderLst = aorderLst;
}



// GETTERS:
int Order::getID() const {return id;}

int Order::getPromTime() const {return promised_time;}

int Order::getNumItems() const {return orderLst.size();}

std::list<std::string> Order::getOrderLst() const {return orderLst;}



// SETTERS:
void Order::expire() {promised_time-=1;}



// OTHERS:
/*
std::ostream& operator<<(std::ostream& os, const Order& order) {
	std::list<std::string>::iterator itr = order.getOrderLst().begin();
	while (itr!=order.getOrderLst().end()) {
		os<<(*itr)<<" ";
		itr++;
	}
	os<<std::endl;
	return os;
}
*/