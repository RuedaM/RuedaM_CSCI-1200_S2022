#include<iostream>
#include<string>


#ifndef Superhero_h_
#define Superhero_h_

class Superhero {
	public:
		// CONSTRUCTORS:
		Superhero();
		Superhero(std::string aname, std::string aidentity, std::string apower);

		// ACCESSORS:
		std::string getName() const;
		std::string getTrueIdentity() const;
		std::string getPower() const;
		bool isGood() const;


		// MODIFIERS:
		void operator-();

		// OTHERS:
		bool operator>(const Superhero& sh);
		bool operator==(const std::string& guess);
		bool operator!=(const std::string& guess);

	private:
		std::string name, identity, power;
		bool alignment;
};

std::ostream& operator<<(std::ostream& os, const Superhero& sh);


#endif