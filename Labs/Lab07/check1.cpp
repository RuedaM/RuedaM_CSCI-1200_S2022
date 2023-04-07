/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Labs/Lab07
g++ -g -Wall -std=c++11 check1.cpp -o check1.out
./check1.out
~/DrMemory-Linux-2.4.0-2/bin64/drmemory -brief -- check1.out
*/

#include<iostream>
#include<string>
#include<vector>
#include<list>

//pathCount() - recursively finds total number of shortest
//				that can be taken back to origin - go down
//				every path by selecting every furthest
//				branch-off in order until total is found
int pathCount(int x, int y) {
	if ((x==0) || (y==0)) {return 1;}							// If one corrdinate is 0 (on an axis), return 1: only one way to go
	else {return (pathCount(x-1, y) + pathCount(x, y-1));}		// Else, recur. run pathCount() from closer location (minus x and y by 1)
}
/*
pathCount() Time Complexity: O(2^n) since the function is calling itelf twice - n is th length of the path itself
*/



int main() {
	
	int xCoord, yCoord;
	std::cout<<"Enter coordinate X: "; std::cin>>xCoord;
	std::cout<<"Enter coordinate Y: "; std::cin>>yCoord;
	std::cout<<"Coordinate: ("<<xCoord<<","<<yCoord<<")"<<std::endl;
	int result = pathCount(xCoord, yCoord);
	std::cout<<"Number of paths to (0,0) from ("
			 <<xCoord<<","<<yCoord<<"): "
			 <<result<<std::endl;

	return 0;
}