/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Homework/HW01
g++ -Wall -g image_processing.cpp -o image_processing.out

./image_processing.out input4.txt output4_replace.txt replace X O
./image_processing.out input4.txt output4_dilation.txt dilation X
./image_processing.out input4.txt output4_erosion.txt erosion X \.

string inFile, string outFile, string operation, char char1, char char2

char char1Arr[argv[3].length() + 1]; 
strcpy(arr, argv[3].c_str());
char char1 = char1Arr[0];
*/


#include <iostream> // library for reading+writing from the console/keyboard
#include <cstdlib> // library with the exit function
#include <string> // library to utilize strings
#include <fstream> // library for reading, wrting, and creating files
#include <vector> // library for creating and using vectors


using namespace std; // no need to add "std::" prefix to every std function


// Takes in the vector of lines from th input file and replaces all non-background characters with a replacement character
// Outputs vector with altered lines
vector<string> replace(vector<string> inFileLineVector, string char1, string char2) {

	for (int rowIndex = 0; rowIndex <= inFileLineVector.size()-1; rowIndex++) {
		for (int columnIndex = 0; columnIndex <= inFileLineVector[0].size()-1; columnIndex++) {
			if (inFileLineVector[rowIndex][columnIndex] == char1[0]) {
				inFileLineVector[rowIndex][columnIndex] = char2[0];
			}
		}
	}
return inFileLineVector;
}


// Takes in the vector of lines from th input file and increases the size of the shape
// Outputs vector with altered lines
vector<string> dilation(vector<string> inFileLineVector, string char1) {
	
	for (int rowIndex = 1; rowIndex < inFileLineVector.size()-1; rowIndex++) {
		for (int columnIndex = 1; columnIndex < inFileLineVector[0].size()-1; columnIndex++) {
			if (inFileLineVector[rowIndex][columnIndex] != char1[0]) {
				if ((inFileLineVector[rowIndex+1][columnIndex] == char1[0])
					 || (inFileLineVector[rowIndex-1][columnIndex] == char1[0])
					 || (inFileLineVector[rowIndex][columnIndex+1] == char1[0])
					 || (inFileLineVector[rowIndex][columnIndex-1] == char1[0])) {
						inFileLineVector[rowIndex][columnIndex] = '`';
				}
			}
		}
	}
	for (int rowIndex = 0; rowIndex <= inFileLineVector.size()-1; rowIndex++) {
		for (int columnIndex = 0; columnIndex <= inFileLineVector[0].size()-1; columnIndex++) {
			if (inFileLineVector[rowIndex][columnIndex] == '`') {
				inFileLineVector[rowIndex][columnIndex] = char1[0];
			}
		}
	}
return inFileLineVector;
}


// Takes in the vector of lines from th input file and decreases the size of the shape
// Outputs vector with altered lines
vector<string> erosion(vector<string> inFileLineVector, string char1, string charbg) {
	
	for (int rowIndex = 0; rowIndex <= inFileLineVector.size()-1; rowIndex++) {
		for (int columnIndex = 0; columnIndex <= inFileLineVector[0].size()-1; columnIndex++) {
			if (inFileLineVector[rowIndex][columnIndex] == char1[0]) {
				if ((inFileLineVector[rowIndex+1][columnIndex] == charbg[0])
				 || (inFileLineVector[rowIndex-1][columnIndex] == charbg[0])
				 || (inFileLineVector[rowIndex][columnIndex+1] == charbg[0])
				 || (inFileLineVector[rowIndex][columnIndex-1] == charbg[0])) {
					inFileLineVector[rowIndex][columnIndex] = '`';
				}
			}
		}
	}
	for (int rowIndex = 0; rowIndex <= inFileLineVector.size()-1; rowIndex++) {
		for (int columnIndex = 0; columnIndex <= inFileLineVector[0].size()-1; columnIndex++) {
			if (inFileLineVector[rowIndex][columnIndex] == '`') {
				inFileLineVector[rowIndex][columnIndex] = charbg[0];
			}
		}
	}
return inFileLineVector;
}





int main(int argc, char *argv[]) {
	// If there are 6 arguments eneterd in the command line, then it must be either erosion or replacement; otherwise, dilation
	if (argc == 6) {
		string inFileStr = argv[1];
		string outFileStr = argv[2];
		string operation = argv[3];
		string char1 = argv[4];
    	string char2 = argv[5];

		ifstream inFile;
		inFile.open(inFileStr);
		ofstream outFile;
		outFile.open(outFileStr);

		// Create vector of strings, each string is  line in the file
		vector<string> inFileLineVector;
		string fileLine;
		while (getline(inFile, fileLine)) {
			inFileLineVector.push_back(fileLine);
		}

		// Passes vector through corresponding function based on command line
		// Returned vector's contents are written to a new file
		if (operation == "replace") {
			vector<string> outFileLineVector = replace(inFileLineVector, char1, char2);
			for(int i = 0; i < outFileLineVector.size(); i++){
			outFile<<outFileLineVector[i]<<endl;
		}
		inFile.close();
		outFile.close();
		}
		else if (operation == "erosion") {
			vector<string> outFileLineVector = erosion(inFileLineVector, char1, char2);
			for(int i = 0; i < outFileLineVector.size(); i++){
			outFile<<outFileLineVector[i]<<endl;
		}
		inFile.close();
		outFile.close();
		}
	}
	else {
		string inFileStr = argv[1];
		string outFileStr = argv[2];
		string operation = argv[3];
		string char1 = argv[4];
    	
		ifstream inFile;
		inFile.open(inFileStr);
		ofstream outFile;
		outFile.open(outFileStr);
		
		// Create vector of strings, each string is  line in the file
		vector<string> inFileLineVector;
		string fileLine;
		while (getline(inFile, fileLine)) {
			inFileLineVector.push_back(fileLine);
		}


		// 5 arguments in command line indicates that dilation is the only option
		// Returned vector's contents are written to a new file
		vector<string> outFileLineVector = dilation(inFileLineVector, char1);
		for(int i = 0; i < outFileLineVector.size(); i++){
			outFile<<outFileLineVector[i]<<endl;
		}
		inFile.close();
		outFile.close();
	}

	return 0;
}