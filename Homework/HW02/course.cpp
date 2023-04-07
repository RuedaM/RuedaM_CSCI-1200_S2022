#include <iostream>
#include <string>

#include "course.h"  //importing Course class in course.h

using namespace std; // no need to add "std::" prefix to every std function



Course::Course() { //default constructor - when no values are inputted, these will be used
	CRN = "000000";
	dept = "DEPT_NULL";
	CC = "NULL-00";
	name = "NAME_NULL";
	day = 'N';
	timeStart = "00:00AM";
	timeEnd = "00:00AM";
	room = "ROOM_NULL";
}
Course::Course(string aCRN, string adept, string aCC, string aname,
		       char aday, string atimeStart, string atimeEnd, string aroom) { // construct from user-input details
	CRN = aCRN;
	dept = adept;
	CC = aCC;
	name = aname;
	day = aday;
	timeStart = atimeStart;
	timeEnd = atimeEnd;
	room = aroom;
}


// GETTERS - getting/returning info from a Time class object
string Course::getCRN() const {
	return CRN;
}
string Course::getdept() const {
	return dept;
}
string Course::getCC() const {
	return CC;
}
string Course::getname() const {
	return name;
}
string Course::getday() const {
	if (day=='M') {return "Monday";}
else if (day=='T') {return "Tuesday";}
else if (day=='W') {return "Wednesday";}
else if (day=='R') {return "Thursday";}
else if (day=='F') {return "Friday";}
else {return "NULL";}
}
int Course::dayCompare() const {
	if (day=='M') {return 1;}
 else if (day=='T') {return 2;}
else if (day=='W') {return 3;}
else if (day=='R') {return 4;}
else if (day=='F') {return 5;}
else {return 0;}
}
string Course::gettimeStart() const {
	return timeStart;
}
int Course::timeStartCompare() const {
	string tSCopy = timeStart;
	int compTime = stoi( tSCopy.erase(2,1).erase(4,2) );
	if ((timeStart.substr(5, 1) == "P") && !((compTime == 1200) || (compTime == 1230))) {compTime += 1200;}
	return compTime;
}
string Course::gettimeEnd() const {
	return timeEnd;
}
string Course::getroom() const {
	return room;
}


// SETTERS - setting new values in a Time class object
//


// OTHERS - various other functions attached to a Time class object
//