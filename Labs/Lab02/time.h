#include <iomanip>

class Time {
public:
	// CONSTRUCTORS - 
	Time();
	Time(int aHour, int aMinute, int aSecond);
	
	// ACCESSORS - taking in values to be stored in the class
	int getHour() const;
	int getMinute() const;
	int getSecond() const;
	
	// MODIFIERS - change member variables within the class
	void setHour(int aHour);
	void setMinute(int aMinute);
	void setSecond(int aSecond);
	
	// other member functions that operate on date objects
	void PrintAMPM() const;


private: // REPRESENTATION (member variables)
	int hour;
	int minute;
	int second;
};

bool IsEarlierThan(const Time& t1, const Time& t2);