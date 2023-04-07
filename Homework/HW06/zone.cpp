#include<iostream>
#include<string>
#include<vector>

#include "zone.h"
#include "coord.h"


// CONSTRUCTORS:
Zone::Zone() {
	zoneChar = ' ';
	area = 0;
}
Zone::Zone(char azoneChar, int aarea) {
	zoneChar = azoneChar;
	area = aarea;
}

// GETTERS:
char Zone::getChar() const {return zoneChar;}
int Zone::getArea() const {return area;}
std::vector<Coord> Zone::getCoords() const {return coordVec;}

// SETTERS:
void Zone::addCoord(unsigned int rVal, unsigned int cVal) {
	coordVec.push_back(Coord(rVal, cVal));
}

// OTHERS:
