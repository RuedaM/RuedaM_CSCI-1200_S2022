/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Homework/HW06
g++ -g -Wall -std=c++11 -o starbattle.out *.cpp
in-/output file: sporcle1.txt
stars per zone: 1, 2, 3
output mode: count, print
solution mode: one_solution, all_solutions
./starbattle.out [input file] [output file] [stars per zone] [output mode] [solution mode]
./starbattle.out sporcle1.txt sporcle1.out 1 count one_solution
~/DrMemory-Linux-2.4.0-2/bin64/drmemory -brief -- ./starbattle.out sporcle1.txt sporcle1.out 1 print one_solution
~/DrMemory-Linux-2.4.0-2/bin64/drmemory -brief -- ./starbattle.out custom1.txt custom1.out 1 print one_solution
~/DrMemory-Linux-2.4.0-2/bin64/drmemory -brief -- ./starbattle.out custom1.txt custom1.out 1 print all_solutions
*/

/*
Each zone EXACTLY S stars
No two stars can be adjacent
Each row CAN have up to S stars in it
Each column CAN have up to S stars in it
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cassert>

#include "zone.h"



typedef unsigned int unint;
typedef std::vector<std::vector<char>> chargrid;


// zoneSort()
// Helper function to sort zones from smallest to largest
bool zoneSort(const Zone& z1, const Zone& z2) {return (z1.getArea()<z2.getArea());}


// print()
// Print inputted board
void print(const chargrid& grid) {
    for (unint i=0 ; i<grid.size() ; ++i) {
        for (unint j=0 ; j<grid[i].size() ; ++j) {
            outfile<<grid[i][j];
        }
        outfile<<std::endl;
    }
}


// create()
// Function that will parse through input file and obtain relevant info
//  Vector of vectors of chars displayGrid returned to be used to display answers
//  Also "pseudo-returning" (passing main code variables as reference so that
//   they change) variables numRows, numCols, and zoneVec (and zoneVecSize)
chargrid create(const std::string& inFileStr, int& numRows, int& numCols,
                std::vector<Zone>& zoneVec) {
    // FILE CREATION:
    std::ifstream inFile; inFile.open(inFileStr, std::ios::in);
    assert(inFile.is_open());

    // VARIABLES:
    // These will change as code parses file
    std::string fileVal;
    char charToAdd;
    int counter=0, zoneCounter=0, colCoord, rowCoord;
    chargrid displayGrid;

    // FILE PARSING + VARIABLE SETTING/INITIALIZATION:
    // Iterate through every alphanumeric character
    while(inFile>>fileVal) {
        // 0th char in file is row count - set as such
        if (counter==0) {numRows = stoi(fileVal);}

        // 1st char in file is col count - set as such
        else if (counter==1) {
            numCols = stoi(fileVal);
            // Using numRows and numCols, create temp board
            std::vector<char> gridRow;
            for (int i=0 ; i<numRows ; ++i) {
                for (int j=0 ; j<numCols ; ++j) {gridRow.push_back('~');}
                displayGrid.push_back(gridRow);
                gridRow.clear();
            }
        }

        // 2nd char in file is a zone char - set as such
        else if (counter==2) {charToAdd = fileVal[0];}

        // 3rd char in file is zone size - add all info to object
        else if (counter==3) {
            // Add semi-completed Zone object to vector
            zoneVec.push_back(Zone(charToAdd, stoi(fileVal)));
        }

        // 4th char in file is a colCoord - set as such
        else if (counter==4) {colCoord = stoi(fileVal);}

        // 5th char in file is a rowCoord - set as such
        else if (counter==5) {
            rowCoord = stoi(fileVal);
            // Make displayGrid coordinate the current charToAdd
            displayGrid[rowCoord][colCoord] = charToAdd;
            // One coord. of latest zone created - note thhis
            zoneCounter+=1;
            // Add coord. to latest zone object
            zoneVec[zoneVec.size()-1].addCoord(rowCoord, colCoord);
            // If no more coords. to add, reset counter to 2 to start new zone
            //  Else, resent counter to 2 to add more coords.
            if (zoneCounter==zoneVec[zoneVec.size()-1].getArea()) {
                zoneCounter = 0;
                counter = 2; continue;
            }
            else {counter = 4; continue;}
        }
        counter+=1;
    }
    inFile.close();
    return displayGrid;
}


// placement()
// Function that will check if a star can be placed in the editGrid
//  based on previous star placement - return true if star can be
//  placed, false if not
bool placement(const chargrid& editGrid, unint& rCoord, unint& cCoord, const unint& S) {
    // CHECK FOR ADJACENT
    // For each, first check if adjacent side exists, then check if it has star
    if ((rCoord>0) && (cCoord>0)) { //top-left
        if (editGrid[rCoord-1][cCoord-1]=='@') {return false;}
    }
    if ((rCoord>0) && (cCoord<editGrid[0].size()-1)) { //top-right
        if (editGrid[rCoord-1][cCoord+1]=='@') {return false;}
    }
    if ((rCoord<editGrid.size()-1) && (cCoord<editGrid[0].size()-1)) { //bottom-right
        if (editGrid[rCoord+1][cCoord+1]=='@') {return false;}
    }
    if ((rCoord<editGrid.size()-1) && (cCoord>0)) { //bottom-left
        if (editGrid[rCoord+1][cCoord-1]=='@') {return false;}
    }
    if (rCoord>0) { //top
        if (editGrid[rCoord-1][cCoord]=='@') {return false;}
    }
    if (cCoord<editGrid[0].size()-1) { //right
        if (editGrid[rCoord][cCoord+1]=='@') {return false;}
    }
    if (rCoord<editGrid.size()-1) { //bottom
        if (editGrid[rCoord+1][cCoord]=='@') {return false;}
    }
    if (cCoord>0) { //left
        if (editGrid[rCoord][cCoord-1]=='@') {return false;}
    }

    // CHECK FOR HORIZONTALS/VERTICALS
    // Iterate through coord's horiz./vert. line to check for stars
    unint cnt = 0;
    for (unint i=0 ; i<editGrid.size() ; ++i) { //vertical
        if (editGrid[i][cCoord]=='@') {
            cnt++;
            if (cnt>=S) {return false;}
        }
    }
    cnt = 0;
    for (unint i=0 ; i<editGrid[0].size() ; ++i) { //horizontal
        if (editGrid[rCoord][i]=='@') {
            cnt++;
            if (cnt>=S) {return false;}
        }
    }
    return true;
}


/*--------------------------------------------------------------------------------------------------------------------------------------*/
// solve()
// Recursive function that returns an integer that ___
//  Stars are placed in the pseudo-grid editGrid
bool solve(chargrid& editGrid, const std::vector<Zone>& zoneVec,
            const unint& S, unint curS, unint znIdx, unint crdIdx,
            std::vector<chargrid>& solGridVec) {
    
    bool bFlag = false;
    while (true) {
        // Create usable coordVec and current coord. in recursive call
        std::cout<<"entered while"<<std::endl;//--------------------
        std::cout<<"Zone: "<<zoneVec[znIdx].getChar()<<std::endl;//--------------------
        std::vector<Coord> coordVec = zoneVec[znIdx].getCoords();
        Coord curCord = coordVec[crdIdx];
        std::cout<<"curCoord: ("<<curCord.r<<","<<curCord.c<<")"<<std::endl;//--------------------
        // If star can be placed on editGrid, add
        if (placement(editGrid, curCord.r, curCord.c, S)) {
            std::cout<<"can place"<<std::endl;//--------------------
            editGrid[curCord.r][curCord.c] = '@';
            print(editGrid);//--------------------
            curS++;
            // If the current # of stars in zone reaches max possible # of stars...
            if (curS>=S) {
                curS = 0;
                std::cout<<"enough stars placed"<<std::endl;//--------------------
                // If next zone is not last zone of grid...
                if ((znIdx+1)!=zoneVec.size()-1) {
                    //~std::cout<<"next zone is not last - recurse"<<std::endl;//--------------------
                    // If next step leads to correct solution, move to next coord
                    //  to check fore more solutions
                    if (solve(editGrid, zoneVec, S, 0, znIdx+1, 0, solGridVec)) {
                        std::cout<<"move to next, find another solution"<<std::endl;//--------------------
                        editGrid[curCord.r][curCord.c] = '~';
                        crdIdx++;
                        // If at end of coordVec, break and return 0
                        if (crdIdx>=coordVec.size()) {
                            std::cout<<"no more coords to read - break"<<std::endl;//--------------------
                            break;} 
                        else {continue;}
                    }
                    else {break;}
                }
                // Else, if next zone is last zone...
                else {
                    std::cout<<"next zone is last - special condition"<<std::endl;//--------------------
                    // Go through every coord in last zone + check star placement
                    std::vector<Coord> coordVec = zoneVec[znIdx+1].getCoords();
                    std::cout<<"Zone: "<<zoneVec[znIdx+1].getChar()<<std::endl;//--------------------
                    unint lastCurS = 0;
                    for (unint i=0 ; i<coordVec.size() ; ++i) {
                        std::cout<<"curCoord: ("<<curCord.r<<","<<curCord.c<<")"<<std::endl;//--------------------
                        Coord lastCurCord = coordVec[i];
                        std::cout<<"lastCurCoord: ("<<lastCurCord.r<<","<<lastCurCord.c<<")"<<std::endl;//--------------------
                        if (placement(editGrid, lastCurCord.r, lastCurCord.c, S)) {
                            //~std::cout<<"can place in last"<<std::endl;//--------------------
                            editGrid[lastCurCord.r][lastCurCord.c] = '@';
                            lastCurS++;
                            // If enough stars correctly placed, return 1 complete solution
                            if (lastCurS>=S) {
                                lastCurS = 0;
                                std::cout<<"solution reached+added"<<std::endl;//--------------------
                                print(editGrid);//--------------------
                                solGridVec.push_back(editGrid);
                                editGrid[lastCurCord.r][lastCurCord.c] = '~';
                                // If at end of coordVec, break and return 0
                                if (i>=coordVec.size()-1) {
                                    std::cout<<"no more last coords to read - break"<<std::endl;//--------------------
                                    editGrid[curCord.r][curCord.c] = '~';
                                    print(editGrid);//--------------------
                                    crdIdx++;
                                    bFlag = true;
                                    break;} 
                            }
                        }
                    }
                    // If at end of coordVec and no solution, break and return 0
                    if (bFlag) {bFlag = false; continue;}
                    if (lastCurS<S) {
                        std::cout<<"end vec, no more coords to read - break"<<std::endl;//--------------------
                        break;}
                }
            }
            // Else, move to next coord to add next star
            else {
                std::cout<<"move to next, add another star"<<std::endl;//--------------------
                crdIdx++;
                // If at end of coordVec, break and return 0
                if (crdIdx>=coordVec.size()) {
                    std::cout<<"no more coords to read - break"<<std::endl;//--------------------
                    break;} 
                else {continue;}
            }
        }
        // Else, move into next coord of zone
        else {
            std::cout<<"cannot place - move to next"<<std::endl;//--------------------
            crdIdx++;
            // If at end of coordVec, break and return 0
            if (crdIdx>=coordVec.size()) {
                std::cout<<"no more coords to read - break"<<std::endl;//--------------------
                break;} 
            else {continue;}
        }
    }
    return false;
}
/*--------------------------------------------------------------------------------------------------------------------------------------*/


int main(int argc, char *argv[]) {
    // USER INPUT:
    std::string inFileStr = argv[1]; std::string outFileStr = argv[2];
    std::string Stemp = argv[3]; unint S = stoi(Stemp);
    std::string outMode = argv[4]; std::string solMode = argv[5];
    // assert() that user input is valid
    assert(outMode == "count" || outMode == "print");
    assert(solMode == "one_solution" || solMode == "all_solutions");
    /*---------------------------------------------------------------------------------------------TESTS: \/ \/*/
    std::cout<<"inFileStr: "<<inFileStr<<std::endl; std::cout<<"outFileStr: "<<outFileStr<<std::endl;
    std::cout<<"S: "<<S<<std::endl; std::cout<<"outMode: "<<outMode<<std::endl;
    std::cout<<"solMode: "<<solMode<<std::endl<<std::endl;
    /*---------------------------------------------------------------------------------------------TESTS: /\ /\*/


    // VARIABLES:
    // Variable declared here to be used in functions
    //  Some will be passed as reference so that they will be changed
    int numRows, numCols, numSol = 0;
    std::vector<Zone> zoneVec;
    std::vector<Coord> coordVec;
    chargrid displayGrid, editGrid;
    std::vector<chargrid> solGridVec;


    // INITIALIZE DISPLAY GRID + OTHER VARIABLES:
    // While initializing numRows, numCols, and zoneVec,
    //  create() will also properly return a grid that can be changed/displayed
    displayGrid = create(inFileStr, numRows, numCols, zoneVec);
    /*---------------------------------------------------------------------------------------------TESTS: \/ \/*/
    print(displayGrid);
    std::cout<<"numRows: "<<numRows<<std::endl;
    std::cout<<"numCols: "<<numCols<<std::endl;
    for (unint i=0 ; i<zoneVec.size() ; ++i) {
        std::cout<<zoneVec[i].getChar()<<": ";
        std::vector<Coord> coordVec = zoneVec[i].getCoords();
        std::cout<<coordVec.size()<<": ";
        for (unint j=0 ; j<coordVec.size() ; ++j) {std::cout<<"("<<coordVec[j].r<<","<<coordVec[j].c<<") ";}
        std::cout<<std::endl;
    }
    /*---------------------------------------------------------------------------------------------TESTS: /\ /\*/
    // Sort vectors from smallest area to largest
    sort(zoneVec.begin(), zoneVec.end(), zoneSort);


    // INITIALIZE EDITING GRID:
    // Rather then outright changing/checking grdVec, create pseudo-grid to place stars in
    //  Star locations here will be used when printing solutions
    for (int i=0 ; i<numRows ; ++i) {
        std::vector<char> gridRow;
        for (int j=0 ; j<numCols ; ++j) {gridRow.push_back('~');}
        editGrid.push_back(gridRow);
    }


    std::cout<<"ENTERING RECURSION..."<<std::endl;
    //RECURSION:
    // Using the recursive function, return total number of solutions
    // Additionally, pass solGridVec as reference so that when recursion
    //  is done solGridVec may (not) be full of solutions to use
    solve(editGrid, zoneVec, S, 0, 0, 0, solGridVec);
    numSol = solGridVec.size();
    std::cout<<"out of recursion"<<std::endl;//--------------------


    // OUTPUT & SOLUTION MODES:
    // Always print out number of solutions
    std::ofstream outFile; outFile.open(outFileStr);
    assert(outFile.is_open());

    outfile<<"Number of solutions: "<<numSol<<std::endl<<std::endl;
    if (numSol<=0) {
    }
    else {
        if (outMode == "print") {
            outfile<<"printing"<<std::endl;//--------------------
            if (solMode == "one_solution") {
                outfile<<"one sol printing"<<std::endl;//--------------------
                outfile<<"Solution 1:"<<std::endl;
                chargrid displayGridCopy = displayGrid, editGridCopy = solGridVec[0];
                for (unint i=0 ; i<editGridCopy.size() ; ++i) {
                    for (unint j=0 ; j<editGridCopy[i].size() ; ++j) {
                        if (editGridCopy[i][j]=='@') {
                            displayGridCopy[i][j] = '@';
                        }
                    }
                }
                print(displayGridCopy);
            }
            else if (solMode == "all_solutions") {
                outfile<<"all sol printing"<<std::endl;//--------------------
                for (int i=0 ; i<numSol ; ++i) {
                    outfile<<"Solution "<<(i+1)<<":"<<std::endl;
                    chargrid displayGridCopy = displayGrid, editGridCopy = solGridVec[i];
                    for (unint j=0 ; j<editGridCopy.size() ; ++j) {
                        for (unint k=0 ; k<editGridCopy[j].size() ; ++k) {
                            if (editGridCopy[j][k]=='@') {
                                displayGridCopy[j][k] = '@';
                            }
                        }
                    }
                    print(displayGridCopy);
                    outfile<<std::endl;
                }
            }
        }
    }
    outFile.close();
    return 0;
}