#include <iostream>
#include <string>
#include <list>

#include "Item.h"



// CONSTRUCTORS:
Item::Item() {
	name = "NULL";
	cook_time = 0;
}
Item::Item(std::string aname, int acook_time) {
	name = aname;
	cook_time = acook_time;
}



// GETTERS:
std::string Item::getName() const {return name;}

int Item::getTime() const {return cook_time;}



// SETTERS:
void Item::cook() {cook_time-=1;}



// OTHERS: