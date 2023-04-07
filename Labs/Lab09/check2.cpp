/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Labs/Lab09
g++ -g -Wall -std=c++11 check2.cpp -o check2.out
./check2.out input.txt
~/DrMemory-Linux-2.4.0-2/bin64/drmemory -brief -- check2.out input.txt
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

	while (inFile >> s) {
	    int i = stoi(s);
	    // find() returns itr to key-value in map if exists and map.end() if not
	    std::map<int, int>::iterator mItr = m.find(i);
	    if (mItr==m.end()) {   // if doesn't exist
	        m.insert(std::make_pair(i, 1));   // create a pair with count 1 already, add to map
	    }
	    else {  // if does exist
	        (mItr->second)++; // simply add to value
	    }
	}

	std::map<int, int>::const_iterator mItr;
    for (mItr = m.begin(); mItr != m.end(); ++mItr) {
        std::cout<<mItr->first<<"\t"<<mItr->second<<std::endl;
    }

    return 0;
}