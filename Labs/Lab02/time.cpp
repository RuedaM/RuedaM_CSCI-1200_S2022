/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Labs/Lab02

g++ -c main.cpp -Wall -Wextra
g++ -c time.cpp -Wall -Wextra
*/



#include <iostream>
#include "time.h"  //importing the Time class located in time.h


Time::Time() { //default constructor - what does it do?
	hour = 0;
	minute = 0;
	second = 0;
}
Time::Time(int aHour, int aMinute, int aSecond) { // construct from hour, minute, second
	hour = aHour;
	minute = aMinute;
	second = aSecond;
}


// GETTERS - getting/returning info from a Time class object
int Time::getHour() const {
	return hour;
}
int Time::getMinute() const {
	return minute;
}
int Time::getSecond() const {
	return second;
}


// SETTERS - setting new values in a Time class object
void Time::setHour(int h) {
	hour = h;
}
void Time::setMinute(int m) {
	minute = m;
}
void Time::setSecond(int s) {
	second = s;
}


// OTHERS - various other functions attached to a Time class object
void Time::PrintAMPM() const {
	if (hour <= 11) {
		std::cout << hour << ":" << std::setfill('0') << std::setw(2) << minute << ":" << std::setfill('0') << std::setw(2) << second << "AM" << std::endl;
	}
	else if (hour == 12) {
		std::cout << hour << ":" << std::setfill('0') << std::setw(2) << minute << ":" << std::setfill('0') << std::setw(2) << second << "PM" << std::endl;
	}
	else {
		std::cout << (hour-12) << ":" << std::setfill('0') << std::setw(2) << minute << ":" << std::setfill('0') << std::setw(2) << second << "PM" << std::endl;
	}
}

bool IsEarlierThan(const Time& t1, const Time& t2) {
	if (t1.getHour() <= t2.getHour()) {
		if (t1.getMinute() <= t2.getMinute()) {
			if (t1.getSecond() < t2.getSecond()) {
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}
//return true if t1 is earlier, false otherwise