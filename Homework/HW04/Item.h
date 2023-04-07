#include <iostream>
#include <string>
#include <list>



#ifndef Item_h_
#define Item_h_

class Item {
	public:
		// CONSTRUCTORS:
		Item();
		Item(std::string aname, int acook_time);

		// ACCESSORS:
		std::string getName() const;
		int getTime() const;

		// MODIFIERS:
		void cook();

	private:
		std::string name;
		int cook_time;
};

#endif