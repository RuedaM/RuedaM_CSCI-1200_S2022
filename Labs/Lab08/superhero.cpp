#include<iostream>
#include<string>

#include "superhero.h"

// CONSTRUCTORS:
Superhero::Superhero() {
	name = "NULLNM"; identity = "NULLID"; power = "NULLPWR"; alignment = true;
}
Superhero::Superhero(std::string aname, std::string aidentity, std::string apower) {
	name = aname; identity = aidentity; power = apower; alignment = true;
}

// GETTERS:
std::string Superhero::getName() const {return name;}

std::string Superhero::getTrueIdentity() const {return identity;}

std::string Superhero::getPower() const {return power;}

bool Superhero::isGood() const {return alignment;}


// SETTERS:
void Superhero::operator-() {
	if (alignment == true) {alignment = false;}
	else if (alignment == false) {alignment = true;}
}

// OTHERS:
bool Superhero::operator>(const Superhero& sh) {
	if (power=="Fire" && sh.getPower()=="Wood") {return true;}
	if (power=="Wood" && sh.getPower()=="Water") {return true;}
	if (power=="Water" && sh.getPower()=="Fire") {return true;}
	if (power=="Laser" && sh.getPower()=="Invisible") {return true;}
	if (power=="Invisible" && sh.getPower()=="Flying") {return true;}
	if (power=="Flying" && sh.getPower()=="Laser") {return true;}
	if (power=="Flexible" && sh.getPower()=="Speed") {return true;}
	if (power=="Speed") {
		if (sh.getPower()=="Speed" || sh.getPower()=="Flexible") {return false;}
		else {return true;}
	}
	return false;
}

bool Superhero::operator==(const std::string& guess) {
	if (identity == guess) {return true;}
	else {return false;}
}

bool Superhero::operator!=(const std::string& guess) {
	if (!(identity == guess)) {return true;}
	else {return false;}
}

std::ostream& operator<<(std::ostream& os, const Superhero& sh) {
	if (sh.isGood()) {
		os<<"Superhero "<<sh.getName()<<" has power "<<sh.getPower()<<std::endl;
	}
	else {
		os<<"Supervillain "<<sh.getName()<<" has power "<<sh.getPower()<<std::endl;
	}
	return os;
}