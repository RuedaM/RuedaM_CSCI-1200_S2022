#include<iostream>
#include<string>
#include<vector>

#include "coord.h"


#ifndef Zone_h_
#define Zone_h_


class Zone {
	public:
		// CONSTRUCTORS:
		Zone();
		Zone(char azoneChar, int aarea);

		// ACCESSORS:
		char getChar() const;
		int getArea() const;
		std::vector<Coord> getCoords() const;

		// MODIFIERS:
		void addCoord(unsigned int rVal, unsigned int cVal);

	private:
		char zoneChar;
		int area;
		std::vector<Coord> coordVec;
};

#endif