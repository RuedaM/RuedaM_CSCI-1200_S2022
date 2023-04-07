#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;



class Course {
public:
	// CONSTRUCTORS - build the class object, includes default
	Course();
	Course(const string aCRN, const string adept,
		   const string aCC, const string aname,
		   const char aday, const string atimeStart,
		   const string atimeEnd, const string aroom);
	
	// ACCESSORS - taking in values to be stored in the class
	string getCRN() const;
	string getdept() const;
	string getCC() const;
	string getname() const;
	string getday() const;
	string gettimeStart() const;
	string gettimeEnd() const;
	string getroom() const;
	
	// MODIFIERS - change member variables within the class
	int dayCompare() const;
	int timeStartCompare() const;

	// OTHERS - other member functions that operate on date objects
	//


private: // REPRESENTATION (member variables)
	string CRN;
	string dept;
	string CC;
	string name;
	char day;
	string timeStart;
	string timeEnd;
	string room;
};