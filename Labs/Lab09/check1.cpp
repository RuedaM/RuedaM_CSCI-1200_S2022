/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Labs/Lab09
g++ -g -Wall -std=c++11 check1.cpp -o check1.out
./check1.out input.txt
~/DrMemory-Linux-2.4.0-2/bin64/drmemory -brief -- check1.out input.txt
*/

#include<iostream>
#include<fstream>
#include<string>
#include<map>

int main(int argc, char *argv[]) {
    std::string inFileStr = argv[1];
    std::string s;
    std::map<int, int> m; // map with key-value as int-int
    
    std::ifstream inFile; inFile.open(inFileStr, std::ios::in);

    /*
    int x;
    x = int();
    std::cout<<x<std::endl;
    */

    // read input, keeping track of each number + how often we see it
    while (inFile >> s) {
    	int i = stoi(s);
    	++m[i];
    }
    
    std::map<int, int>::const_iterator mItr;
    for (mItr = m.begin(); mItr != m.end(); ++mItr) {
        std::cout<<mItr->first<<"\t"<<mItr->second<<std::endl;
    }

    return 0;
}