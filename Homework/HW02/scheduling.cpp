/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Homework/HW02

COMPILE ALL FILES: g++ -Wall -std=c++11 -o scheduling.out *.cpp
COMPILE ALL FILES: g++ -Wall -std=c++11 -o scheduling.exe *.cpp
COMPILE MAIN FILE: g++ scheduling.cpp -o scheduling.out -Wall -Wextra

./scheduling.out simple2.txt out_simple2_room.txt room
./scheduling.out medium1.txt out_medium1_room.txt room
./scheduling.out empty.txt out_empty_room.txt room
./scheduling.out medium1.txt out_medium1_room_ACADMY_AUD.txt room ACADMY_AUD
./scheduling.out medium1.txt out_medium1_room_ACADMY_AUD.txt room JONSSN_3332
./scheduling.out medium1.txt out_empty_room_ROOM1234.txt room ROOM1234
./scheduling.out empty.txt out_empty_room_ACADMY_AUD.txt room ACADMY_AUD
./scheduling.out simple2.txt out_simple2_dept_ECSE.txt dept ECSE
./scheduling.out simple2.txt out_simple2_dept_FART.txt dept FART
./scheduling.out empty.txt out_empty_dept_ECSE.txt dept ECSE
./scheduling.out medium1.txt out_medium1_custom.txt custom
./scheduling.exe medium1.txt out_medium1_custom.txt custom

./scheduling.out RPI_Fall2018.txt out_RPIFallCat_room.txt room
*/


#include <cstdlib> // library with exit function
#include <iostream> // library for reading+writing from console/keyboard
#include <string> // library for strings
#include <vector> // library for vectors
#include <fstream> // library for reading, wrting, and creating files
#include <iomanip> // library for {HELP W/ PRINTING TO SIZE} ???
#include <algorithm> // library for searching, sorting, and manipulation ???

#include "course.h"


using namespace std; // no need for "std::" prefix





void debug() {
	cout<<"[----------CHECK----------]"<<endl;
	/*
	for (int i=0; i<courseObjVec.size(); i++) {cout<<(courseObjVec[i].getCRN())<<" "<<(courseObjVec[i].getdept())<<" "<<(courseObjVec[i].getCC())<<" "<<(courseObjVec[i].getname())<<" "<<(courseObjVec[i].getday())<<" "<<(courseObjVec[i].gettimeStart())<<" "<<(courseObjVec[i].gettimeEnd())<<" "<<(courseObjVec[i].getroom())<<endl;}
	debug();
	*/
}

vector<Course> objVec_creation(string inFileStr, string outFileStr) {
	ifstream inFile; inFile.open(inFileStr);

	vector<Course> courseObjVec;
	string fileLine; vector<string> fileLineVec;
	int i=0;
	while (inFile >> fileLine) {
		fileLineVec.push_back(fileLine);
		i++;
		if (i == 8) {
			for (int j=0; j<fileLineVec[4].size(); j++) {
				//for (int v=0; v<fileLineVec.size();v++) {cout<<fileLineVec[v]<<" ";} cout<<endl;
				string CRN = fileLineVec[0]; string dept = fileLineVec[1];
				string CC = fileLineVec[2]; string name = fileLineVec[3];
				char day = fileLineVec[4][j]; string timeStart = fileLineVec[5];
				string timeEnd = fileLineVec[6]; string room = fileLineVec[7];
			
				Course courseObj(CRN, dept, CC, name, day, timeStart, timeEnd, room);
				courseObjVec.push_back(courseObj);
			}
		i=0; fileLineVec.clear();
		}
	}
	inFile.close();

	return courseObjVec;
}

bool is_first_room_gen(const Course& c1, const Course& c2) {
	if (c1.getroom() < c2.getroom()) {return true;}
	else if (c1.getroom() == c2.getroom()){
		if (c1.dayCompare() < c2.dayCompare()) {return true;}
		else if (c1.dayCompare() == c2.dayCompare()){
			if (c1.timeStartCompare() < c2.timeStartCompare()) {return true;}
			else if (c1.timeStartCompare() == c2.timeStartCompare()) {
				if (c1.getCC() < c2.getCC()) {return true;}
				else if (c1.getCC() == c2.getCC()) {
					if (c1.getdept() < c2.getdept()) {return true;}
					else {return false;}
				} else {return false;}
			} else {return false;}
		} else {return false;}
	} else {return false;}
}

bool is_first_room(const Course& c1, const Course& c2) {
	if (c1.dayCompare() < c2.dayCompare()) {return true;}
	else if (c1.dayCompare() == c2.dayCompare()){
		if (c1.timeStartCompare() < c2.timeStartCompare()) {return true;}
		else if (c1.timeStartCompare() == c2.timeStartCompare()) {
			if (c1.getCC() < c2.getCC()) {return true;}
			else if (c1.getCC() == c2.getCC()) {
				if (c1.getdept() < c2.getdept()) {return true;}
				else {return false;}
			} else {return false;}
		} else {return false;}
	} else {return false;}
}

bool is_first_dept(const Course& c1, const Course& c2) {
	if (c1.getCC() < c2.getCC()) {return true;}
	else if (c1.getCC() == c2.getCC()){
		if (c1.dayCompare() < c2.dayCompare()) {return true;}
		else if (c1.dayCompare() == c2.dayCompare()) {
			if (!(c1.timeStartCompare() < c2.timeStartCompare())) {return true;}
			else {return false;}
		} else {return false;}
	} else {return false;}
}

bool is_first_cust(const Course& c1, const Course& c2) {
	if (c1.getname() < c2.getname()) {return true;}
	else if (c1.getname() == c2.getname()){
		if (c1.dayCompare() < c2.dayCompare()) {return true;}
		else if (c1.dayCompare() == c2.dayCompare()){
			if (c1.timeStartCompare() < c2.timeStartCompare()) {return true;}
			else if (c1.timeStartCompare() == c2.timeStartCompare()) {
				if (c1.getCC() < c2.getCC()) {return true;}
				else if (c1.getCC() == c2.getCC()) {
					if (c1.getdept() < c2.getdept()) {return true;}
					else {return false;}
				} else {return false;}
			} else {return false;}
		} else {return false;}
	} else {return false;}
}

int name_max_length(vector<Course> courseObjVec) {
	int name_max_len = 0;
	for (int i=0; i<courseObjVec.size(); i++) {
		int name_temp_len = courseObjVec[i].getname().size();
		name_max_len = max(name_max_len, name_temp_len);
		name_max_len = max(name_max_len, 11);
	}
	return name_max_len;
}

int day_max_length(vector<Course> courseObjVec) {
	int day_max_len = 0;
	for (int i=0; i<courseObjVec.size(); i++) {
		int day_temp_len = courseObjVec[i].getday().size();
		day_max_len = max(day_max_len, day_temp_len);
	}
	return day_max_len;
}

int CC_max_length(vector<Course> courseObjVec) {
	int CC_max_len = 0;
	for (int i=0; i<courseObjVec.size(); i++) {
		int CC_temp_len = courseObjVec[i].getCC().size();
		CC_max_len = max(CC_max_len, CC_temp_len);
		CC_max_len = max(CC_max_len, 9);
	}
	return CC_max_len;
}



void no_data(string outFileStr) {
	ofstream outFile; outFile.open(outFileStr);
	outFile<<"No data available."<<endl;
	outFile.close();
}


void room_output(vector<Course> courseObjVec, string outFileStr) {
	
	if (courseObjVec.size() <= 0) {no_data(outFileStr); return;}
	sort(courseObjVec.begin(),courseObjVec.end(), is_first_room_gen);
	
	ofstream outFile; outFile.open(outFileStr);
	int nml, dml, CCml; string courseBreak = courseObjVec[0].getroom(); vector<Course> tempVec;
	
	for (int i=0; i<courseObjVec.size(); i++) {
		if (courseObjVec[i].getroom() != courseBreak) {
			nml = name_max_length(tempVec); dml = day_max_length(tempVec); CCml = CC_max_length(tempVec);
			outFile<<"Room "<<courseBreak<<endl;
			outFile<<"Dept  Coursenum"<<"  "<<"Class Title"<<setw(nml-11+2)<<"  "<<"Day"<<setw(dml-3+2)<<"  "<<"Start Time  End Time"<<endl;
			outFile<<string(4, '-')<<"  "<<string(CCml, '-')<<"  "<<string(nml, '-')<<"  "<<string(dml, '-')<<"  "<<string(10, '-')<<"  "<<string(8, '-')<<endl;
			for (int j=0; j<tempVec.size();j++) {
				string dept = tempVec[j].getdept(); string CC = tempVec[j].getCC(); string name = tempVec[j].getname();
				string day = tempVec[j].getday(); string timeS = tempVec[j].gettimeStart(); string timeE = tempVec[j].gettimeEnd();
				outFile<<dept<<"  "<<CC<<setw(CCml-CC.size()+2)<<"  "<<name<<setw(nml-name.size()+2)<<"  "<<day<<setw(dml-day.size()+2)<<"  "<<timeS<<"     "<<timeE<<" "<<endl;
			}
			outFile<<tempVec.size()<<" entries"<<endl<<endl;
			courseBreak = courseObjVec[i].getroom();
			tempVec.clear();
		}
		tempVec.push_back(courseObjVec[i]);

	}
	nml = name_max_length(tempVec); dml = day_max_length(tempVec); CCml = CC_max_length(tempVec);
	outFile<<"Room "<<courseBreak<<endl;
	outFile<<"Dept  Coursenum"<<"  "<<"Class Title"<<setw(nml-11+2)<<"  "<<"Day"<<setw(dml-3+2)<<"  "<<"Start Time  End Time"<<endl;
	outFile<<string(4, '-')<<"  "<<string(CCml, '-')<<"  "<<string(nml, '-')<<"  "<<string(dml, '-')<<"  "<<string(10, '-')<<"  "<<string(8, '-')<<endl;
	for (int j=0; j<tempVec.size();j++) {
		string dept = tempVec[j].getdept(); string CC = tempVec[j].getCC(); string name = tempVec[j].getname();
		string day = tempVec[j].getday(); string timeS = tempVec[j].gettimeStart(); string timeE = tempVec[j].gettimeEnd();
		outFile<<dept<<"  "<<CC<<setw(CCml-CC.size()+2)<<"  "<<name<<setw(nml-name.size()+2)<<"  "<<day<<setw(dml-day.size()+2)<<"  "<<timeS<<"     "<<timeE<<" "<<endl;
	}
	outFile<<tempVec.size()<<" entries"<<endl<<endl;
	tempVec.clear();
	
	outFile.close();
}


void specroom_output(vector<Course> courseObjVec, string outFileStr, string specifier) {
	
	vector<Course> courseObjVecShort;
	for (int i=0; i<courseObjVec.size(); i++) {
		if (courseObjVec[i].getroom() == specifier) {courseObjVecShort.push_back(courseObjVec[i]);}
	}
	if (courseObjVecShort.size() <= 0) {no_data(outFileStr); return;}
	sort(courseObjVecShort.begin(),courseObjVecShort.end(), is_first_room);
	
	ofstream outFile; outFile.open(outFileStr);
	int nml = name_max_length(courseObjVecShort), dml = day_max_length(courseObjVecShort), CCml = CC_max_length(courseObjVecShort);
	
	outFile<<"Room "<<specifier<<endl;
	outFile<<"Dept  Coursenum"<<"  "<<"Class Title"<<setw(nml-11+2)<<"  "<<"Day"<<setw(dml-3+2)<<"  "<<"Start Time  End Time"<<endl;
	outFile<<string(4, '-')<<"  "<<string(CCml, '-')<<"  "<<string(nml, '-')<<"  "<<string(dml, '-')<<"  "<<string(10, '-')<<"  "<<string(8, '-')<<endl;
	for (int i=0; i<courseObjVecShort.size();i++) {
		string dept = courseObjVecShort[i].getdept(); string CC = courseObjVecShort[i].getCC(); string name = courseObjVecShort[i].getname();
		string day = courseObjVecShort[i].getday(); string timeS = courseObjVecShort[i].gettimeStart(); string timeE = courseObjVecShort[i].gettimeEnd();
		outFile<<dept<<"  "<<CC<<setw(CCml-CC.size()+2)<<"  "<<name<<setw(nml-name.size()+2)<<"  "<<day<<setw(dml-day.size()+2)<<"  "<<timeS<<"     "<<timeE<<" "<<endl;
	}
	outFile<<courseObjVecShort.size()<<" entries"<<endl<<endl;
	
	outFile.close();
}


void dept_output(vector<Course> courseObjVec, string outFileStr, string specifier) {

	vector<Course> courseObjVecShort;
	for (int i=0; i<courseObjVec.size(); i++) {
		if (courseObjVec[i].getdept() == specifier) {courseObjVecShort.push_back(courseObjVec[i]);}
	}
	if (courseObjVecShort.size() <= 0) {no_data(outFileStr); return;}
	sort(courseObjVecShort.begin(),courseObjVecShort.end(), is_first_dept);

	ofstream outFile; outFile.open(outFileStr);
	int nml = name_max_length(courseObjVecShort), dml = day_max_length(courseObjVecShort), CCml = CC_max_length(courseObjVecShort);
	
	outFile<<"Dept "<<specifier<<endl;
	outFile<<"Coursenum"<<"  "<<"Class Title"<<setw(nml-11+2)<<"  "<<"Day"<<setw(dml-3+2)<<"  "<<"Start Time  End Time"<<endl;
	outFile<<string(CCml, '-')<<"  "<<string(nml, '-')<<"  "<<string(dml, '-')<<"  "<<string(10, '-')<<"  "<<string(8, '-')<<endl;
	for (int i=0; i<courseObjVecShort.size();i++) {
		string CC = courseObjVecShort[i].getCC(); string name = courseObjVecShort[i].getname(); string day = courseObjVecShort[i].getday();
		string timeS = courseObjVecShort[i].gettimeStart(); string timeE = courseObjVecShort[i].gettimeEnd();
		outFile<<CC<<setw(CCml-CC.size()+2)<<"  "<<name<<setw(nml-name.size()+2)<<"  "<<day<<setw(dml-day.size()+2)<<"  "<<timeS<<"     "<<timeE<<" "<<endl;
	}
	outFile<<courseObjVecShort.size()<<" entries"<<endl<<endl;
	
	outFile.close();
}


void custom_output(vector<Course> courseObjVec, string outFileStr) {

	if (courseObjVec.size() <= 0) {no_data(outFileStr); return;}
	sort(courseObjVec.begin(),courseObjVec.end(), is_first_cust);

	ofstream outFile; outFile.open(outFileStr);
	int nml, dml; char courseBreak = courseObjVec[0].getname()[0]; vector<Course> tempVec;
	
	for (int i=0; i<courseObjVec.size(); i++) {
		if (courseObjVec[i].getname()[0] != courseBreak) {
			nml = name_max_length(tempVec); dml = day_max_length(tempVec);
			outFile<<courseBreak<<endl;
			outFile<<"Dept  Coursenum"<<"  "<<"Class Title"<<setw(nml-11+2)<<"  "<<"Day"<<setw(dml-3+2)<<"  "<<"Start Time  End Time"<<endl;
			outFile<<string(4, '-')<<"  "<<string(9, '-')<<"  "<<string(nml, '-')<<"  "<<string(dml, '-')<<"  "<<string(10, '-')<<"  "<<string(8, '-')<<endl;
			for (int j=0; j<tempVec.size();j++) {
				string dept = tempVec[j].getdept(); string CC = tempVec[j].getCC(); string name = tempVec[j].getname();
				string day = tempVec[j].getday(); string timeS = tempVec[j].gettimeStart(); string timeE = tempVec[j].gettimeEnd();
				outFile<<dept<<"  "<<CC<<"    "<<name<<setw(nml-name.size()+2)<<"  "<<day<<setw(dml-day.size()+2)<<"  "<<timeS<<"     "<<timeE<<" "<<endl;
			}
			outFile<<tempVec.size()<<" entries"<<endl<<endl;
			courseBreak = courseObjVec[i].getname()[0];
			tempVec.clear();
		}
		tempVec.push_back(courseObjVec[i]);

	}
	nml = name_max_length(tempVec); dml = day_max_length(tempVec);
	outFile<<"Room "<<courseBreak<<endl;
	outFile<<"Dept  Coursenum"<<"  "<<"Class Title"<<setw(nml-11+2)<<"  "<<"Day"<<setw(dml-3+2)<<"  "<<"Start Time  End Time"<<endl;
	outFile<<string(4, '-')<<"  "<<string(9, '-')<<"  "<<string(nml, '-')<<"  "<<string(dml, '-')<<"  "<<string(10, '-')<<"  "<<string(8, '-')<<endl;
	for (int j=0; j<tempVec.size();j++) {
		string dept = tempVec[j].getdept(); string CC = tempVec[j].getCC(); string name = tempVec[j].getname();
		string day = tempVec[j].getday(); string timeS = tempVec[j].gettimeStart(); string timeE = tempVec[j].gettimeEnd();
		outFile<<dept<<"  "<<CC<<"    "<<name<<setw(nml-name.size()+2)<<"  "<<day<<setw(dml-day.size()+2)<<"  "<<timeS<<"     "<<timeE<<" "<<endl;
	}
	outFile<<tempVec.size()<<" entries"<<endl<<endl;
	tempVec.clear();
	
	outFile.close();
}





int main(int argc, char *argv[]) {

	if (argc == 4) {
		string inFileStr = argv[1]; string outFileStr = argv[2]; string operation = argv[3];

		vector<Course> courseObjVec = objVec_creation(inFileStr, outFileStr);
		if (courseObjVec.size() <= 0) {no_data(outFileStr); return 0;}

		
		if (operation == "room") {
   			room_output(courseObjVec, outFileStr);
   		}
		else if (operation == "custom") {
			custom_output(courseObjVec, outFileStr);
		}
   		else {cerr<<"ERROR: Invalid command input -- please re-enter command(s)"<<endl;}
	}
	else if (argc == 5) {
		string inFileStr = argv[1]; string outFileStr = argv[2]; string operation = argv[3]; string specifier = argv[4];

		vector<Course> courseObjVec = objVec_creation(inFileStr, outFileStr);
		if (courseObjVec.size() <= 0) {no_data(outFileStr); return 0;}


		if (operation == "room") {
			specroom_output(courseObjVec, outFileStr, specifier);
		}
		else if (operation == "dept") {
			dept_output(courseObjVec, outFileStr, specifier);
		}
		else {cerr<<"ERROR: Invalid command input -- please re-enter command(s)"<<endl;}
	}

	return 0;
}