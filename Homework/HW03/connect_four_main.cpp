/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Homework/HW03

g++ -g -Wall -std=c++11 -o connect_four_main.out *.cpp

./connect_four_main.out

~/DrMemory-Linux-2.4.0-2/bin64/drmemory -brief -- connect_four_main.out
*/

#include <iostream>
#include <string>
#include <cassert>
#include "Board.h"

void SimpleTest(); //Some basic tests
void StudentTest(); //Write your own test cases here

int main(){
	SimpleTest();
	std::cout << "Completed all simple tests." << std::endl;

	StudentTest();
	std::cout << "Completed all student tests." << std::endl;

	return 0;
}

//
// Do not modify this function - a fresh copy will be used on Submitty
void SimpleTest(){
	Board b("R","Y",".");

	std::cout << "Initial board:" << std::endl << b << std::endl;
	std::cout << "Row 0 has " << b.numTokensInRow(0) << std::endl;
	std::cout << "Row 4 has " << b.numTokensInRow(4) << std::endl;
	std::cout << "Row 5 has " << b.numTokensInRow(5) << std::endl;
	std::cout << "Column 0 has " << b.numTokensInColumn(0) << std::endl;
	std::cout << "Column 3 has " << b.numTokensInColumn(3) << std::endl;
	std::cout << "Column 4 has " << b.numTokensInColumn(4) << std::endl;

	b.insert(0,true);
	std::cout << "Second handout figure" << std::endl << b << std::endl;

	b.insert(1,false);
	b.insert(2,true);
	b.insert(3,true);
	std::cout << "Third handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	b.insert(1,true);
	b.insert(1,false);
	b.insert(1,true);
	b.insert(1,false);
	b.insert(1,true);
	std::cout << "Fourth handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	b.insert(4,true);
	std::cout << "Fifth handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	//Looks ugly if we don't make all tokens the same length, but not required
	Board b2("Puppy","Kitty","-----"); 
	std::string result;
	std::cout << "Starting a new board!" << std::endl;
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
}
//

////////STUDENT CODE////////

//Write your own test cases here
void StudentTest(){
	
	std::cout<<"TEST 1: Basic Board Creation and Insertion Test"<<std::endl;
	Board testBoard("X", "O", "*");
	std::cout<<testBoard<<std::endl;
	testBoard.insert(0,true);
	std::cout<<testBoard<<std::endl;
	std::cout<<"numTokensInRow0: "<<testBoard.numTokensInRow(0)<<std::endl;
	std::cout<<"numTokensInRow1: "<<testBoard.numTokensInRow(1)<<std::endl;
	std::cout<<"numTokensInColumn0: "<<testBoard.numTokensInColumn(0)<<std::endl;
	std::cout<<"numTokensInColumn1: "<<testBoard.numTokensInColumn(1)<<std::endl;
	std::cout<<std::endl<<std::endl;


	std::string result;

	std::cout<<"TEST 2: Row Match Scenario"<<std::endl;
	Board testBoard2("Y", "Z", "*");
	std::cout<<testBoard2<<std::endl;

	testBoard2.insert(0,true);
	testBoard2.insert(0,false);
	testBoard2.insert(1,true);
	testBoard2.insert(2,true);
	result = testBoard2.insert(3,true);
	std::cout<<testBoard2<<std::endl;

	if(result == "*") {std::cout<<"No win"<<std::endl;}
	else {std::cout <<"Win: "<<result<<std::endl;}
	std::cout<<std::endl<<std::endl;


	std::cout<<"TEST 3: Column Match Scenario"<<std::endl;
	Board testBoard3("A", "B", "*");
	std::cout<<testBoard3<<std::endl;

	testBoard3.insert(0,true);
	testBoard3.insert(1,false);
	testBoard3.insert(0,true);
	testBoard3.insert(0,true);
	result = testBoard3.insert(0,true);
	std::cout<<testBoard3<<std::endl;

	if(result == "*") {std::cout<<"No win"<<std::endl;}
	else {std::cout <<"Win: "<<result<<std::endl<<std::endl;}
	std::cout<<std::endl<<std::endl;


	std::cout<<"TEST 4: Expansive Row Scenario"<<std::endl;
	Board testBoard4("+", "-", "*");
	std::cout<<testBoard4<<std::endl;

	testBoard4.insert(0,true); testBoard4.insert(1,false); testBoard4.insert(2,true);
	testBoard4.insert(3,false); testBoard4.insert(4,true); testBoard4.insert(5,false);
	testBoard4.insert(6,true); testBoard4.insert(7,false); testBoard4.insert(8,true);
	result = testBoard4.insert(12,true);
	std::cout<<testBoard4<<std::endl;

	if(result == "*") {std::cout<<"No win"<<std::endl;}
	else {std::cout <<"Win: "<<result<<std::endl<<std::endl;}
	std::cout<<std::endl<<std::endl;


	std::cout<<"TEST 5: Board Copying"<<std::endl;
	Board testBoard5("X", "%", "*");
	std::cout<<testBoard5<<std::endl;

	testBoard5.insert(0,true); testBoard5.insert(0,true); testBoard5.insert(1,true);
	testBoard5.insert(2,false); testBoard5.insert(3,false); testBoard5.insert(3,false);
	testBoard5.insert(4,true); testBoard5.insert(4,true); testBoard5.insert(5,true);
	
	std::cout<<testBoard5<<std::endl;
	Board testBoard5Copy(testBoard5);
	std::cout<<testBoard5Copy<<std::endl;

	if(result == "*") {std::cout<<"No win"<<std::endl;}
	else {std::cout <<"Win: "<<result<<std::endl<<std::endl;}
	std::cout<<std::endl<<std::endl;


	std::cout<<"TEST 6: Corner Cases + Clearing"<<std::endl;
	Board testBoard6("-", "=", "*");
	std::cout<<testBoard6<<std::endl;

	testBoard6.insert(0,true); testBoard6.insert(0,true); testBoard6.insert(0,true);
	result = testBoard6.insert(0,true);
	std::cout<<testBoard6<<std::endl;
	if(result == "*") {std::cout<<"No win"<<std::endl;}
	else {std::cout <<"Win: "<<result<<std::endl<<std::endl;}
	testBoard6.clear();

	testBoard6.insert(0,true); testBoard6.insert(1,true); testBoard6.insert(2,true);
	result = testBoard6.insert(3,true);
	std::cout<<testBoard6<<std::endl;
	if(result == "*") {std::cout<<"No win"<<std::endl;}
	else {std::cout <<"Win: "<<result<<std::endl<<std::endl;}
	testBoard6.clear();

	testBoard6.insert(10,true); testBoard6.insert(11,true); testBoard6.insert(12,true);
	result = testBoard6.insert(13,true);
	std::cout<<testBoard6<<std::endl;
	if(result == "*") {std::cout<<"No win"<<std::endl;}
	else {std::cout <<"Win: "<<result<<std::endl<<std::endl;}
	testBoard6.clear();

	testBoard6.insert(13,true); testBoard6.insert(13,true); testBoard6.insert(13,true);
	result = testBoard6.insert(13,true);
	std::cout<<testBoard6<<std::endl;
	if(result == "*") {std::cout<<"No win"<<std::endl;}
	else {std::cout <<"Win: "<<result<<std::endl<<std::endl;}
	testBoard6.clear();

	testBoard6.insert(0,true); testBoard6.insert(1,false);
	testBoard6.insert(2,true); testBoard6.insert(3,false);
	testBoard6.insert(0,false); testBoard6.insert(1,true);
	testBoard6.insert(2,false); testBoard6.insert(3,true);
	testBoard6.insert(0,true); testBoard6.insert(1,false);
	testBoard6.insert(2,true); testBoard6.insert(3,false);
	testBoard6.insert(0,false); testBoard6.insert(1,true);
	testBoard6.insert(2,false); testBoard6.insert(3,true);
	testBoard6.insert(0,true); testBoard6.insert(1,false);
	testBoard6.insert(2,true); testBoard6.insert(3,false);
	testBoard6.insert(0,false); testBoard6.insert(1,true);
	testBoard6.insert(2,false); testBoard6.insert(3,true);
	testBoard6.insert(0,true); testBoard6.insert(1,false);
	testBoard6.insert(2,true); testBoard6.insert(3,false);
	testBoard6.insert(0,false); testBoard6.insert(1,true);
	testBoard6.insert(2,false); testBoard6.insert(3,true);
	testBoard6.insert(0,true); testBoard6.insert(1,true); testBoard6.insert(2,true);
	result = testBoard6.insert(3,true);
	std::cout<<testBoard6<<std::endl;
	if(result == "*") {std::cout<<"No win"<<std::endl;}
	else {std::cout <<"Win: "<<result<<std::endl<<std::endl;}
	testBoard6.clear();

	testBoard6.insert(0,true); testBoard6.insert(0,false);
	testBoard6.insert(0,true); testBoard6.insert(0,false);
	testBoard6.insert(0,true); testBoard6.insert(0,false);
	testBoard6.insert(0,true); testBoard6.insert(0,false);
	testBoard6.insert(0,true); testBoard6.insert(0,true); testBoard6.insert(0,true);
	result = testBoard6.insert(0,true);
	std::cout<<testBoard6<<std::endl;
	if(result == "*") {std::cout<<"No win"<<std::endl;}
	else {std::cout <<"Win: "<<result<<std::endl;}
	testBoard6.clear();

	testBoard6.insert(13,true); testBoard6.insert(13,false);
	testBoard6.insert(13,true); testBoard6.insert(13,false);
	testBoard6.insert(13,true); testBoard6.insert(13,false);
	testBoard6.insert(13,true); testBoard6.insert(13,false);
	testBoard6.insert(13,true); testBoard6.insert(13,true); testBoard6.insert(13,true);
	result = testBoard6.insert(13,true);
	std::cout<<testBoard6<<std::endl;
	if(result == "*") {std::cout<<"No win"<<std::endl;}
	else {std::cout <<"Win: "<<result<<std::endl;}
	testBoard6.clear();

	testBoard6.insert(10,true); testBoard6.insert(11,false);
	testBoard6.insert(12,true); testBoard6.insert(13,false);
	testBoard6.insert(10,false); testBoard6.insert(11,true);
	testBoard6.insert(12,false); testBoard6.insert(13,true);
	testBoard6.insert(10,true); testBoard6.insert(11,false);
	testBoard6.insert(12,true); testBoard6.insert(13,false);
	testBoard6.insert(10,false); testBoard6.insert(11,true);
	testBoard6.insert(12,false); testBoard6.insert(13,true);
	testBoard6.insert(10,true); testBoard6.insert(11,false);
	testBoard6.insert(12,true); testBoard6.insert(13,false);
	testBoard6.insert(10,false); testBoard6.insert(11,true);
	testBoard6.insert(12,false); testBoard6.insert(13,true);
	testBoard6.insert(10,true); testBoard6.insert(11,false);
	testBoard6.insert(12,true); testBoard6.insert(13,false);
	testBoard6.insert(10,false); testBoard6.insert(11,true);
	testBoard6.insert(12,false); testBoard6.insert(13,true);
	testBoard6.insert(10,true); testBoard6.insert(11,true); testBoard6.insert(12,true);
	result = testBoard6.insert(13,true);
	std::cout<<testBoard6<<std::endl;
	if(result == "*") {std::cout<<"No win"<<std::endl;}
	else {std::cout <<"Win: "<<result<<std::endl<<std::endl;}
	testBoard6.clear();
	std::cout<<std::endl<<std::endl;


	std::cout<<"TEST 7: Assignment Operator Testing"<<std::endl;
	Board testBoard7("@", "#", "*");
	std::cout<<testBoard7<<std::endl;

	testBoard7.insert(0,false); testBoard7.insert(0,true); testBoard7.insert(0,true);
	testBoard7.insert(0,true); testBoard7.insert(0,false); testBoard7.insert(1,true);
	testBoard7.insert(1,false); testBoard7.insert(1,false); testBoard7.insert(1,false);
	testBoard7.insert(1,true); testBoard7.insert(2,true); testBoard7.insert(2,false);
	testBoard7.insert(2,false); testBoard7.insert(2,false); testBoard7.insert(2,true);
	testBoard7.insert(3,false); testBoard7.insert(3,true); testBoard7.insert(3,true);
	testBoard7.insert(3,true); testBoard7.insert(3,false);
	std::cout<<testBoard7<<std::endl;

	Board testBoard7a = testBoard7;
	std::cout<<testBoard7a<<std::endl;	
}


/*
- Create assignment operator
- Create more student testing
- Fill in O-notation + testing/debugging procedure
*/