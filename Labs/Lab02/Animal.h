#include <string>

class Animal {
public:
	// CONSTRUCTORS - 
	Animal(std::string aName);
	
	// ACCESSORS - showing/displaying values stored in the class object
	std::string getName() const;
	int getWeight() const;
	bool isVeg() const;
	bool isMeat() const;
	bool isOmn() const;
	bool isLand() const;
	bool isSea() const;
	bool isAmph() const; 
	
	// MODIFIERS - change member variables within the class object
	void setName(std::string& aName);
	void setWeight(int aWeight);
	void setVeg(bool aVegTF);
	void setMeat(bool aMeatTF);
	void setLand(bool aLandTF);
	void setSea(bool aSeaTF);
	
	// other member functions that operate on date objects
	/*
	*/


private: // REPRESENTATION (member variables)
	std::string name;
	int weight;
	bool veg;
	bool meat;
	bool land;
	bool sea;

};