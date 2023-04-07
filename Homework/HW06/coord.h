#include<iostream>

#ifndef Coord_h_
#define Coord_h_


class Coord {
public:
    // CONSTRUCTORS:
    Coord() : r(0), c(0) {}
    Coord(const unsigned int& rIn, const unsigned int& cIn) : r(rIn), c(cIn) {}

    // REPRESENTATION VARIABLES:
    unsigned int r, c;
};

/*
std::ostream& operator<<(std::ostream& os, const Coord& coord) {
    os<<"("<<coord.c<<","<<coord.r<<")"; return os;
}
*/

#endif