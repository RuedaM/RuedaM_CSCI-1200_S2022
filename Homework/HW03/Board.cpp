#include <iostream>
#include <string>

#include "Board.h"



// INITIALIZERS
//Board() - If Board obj created with no params, hard-coded default
//			ones used - board created normally
Board::Board() {
	p1 = "NULL1"; p2 = "NULL2"; blank = "NULL_";
	create(4);
}


//Board([params]) - If Board obj created with correct number of params,
//					params passed as usable variables in class - board
//					created normally
Board::Board(std::string ap1, std::string ap2, std::string ablank) {
	p1 = ap1; p2 = ap2; blank = ablank;
	create(4);
}


//Board(BoardObj) - If wanting to make class a copy of another, use
//					this - in the syntax BoardB copy(BoardA): "BoardB
//					will be created to be a copy of BoardA"
Board::Board(const Board& classCopy) {
	copy(classCopy);
}


//~Board() - If wanting to delete class and all dynamic memory
//			 associated with it, use
Board::~Board() {
	for (int i=0 ; i<colCount ; ++i) {
		if (m_data[i] != NULL) {delete[] m_data[i];} //delete OR delete[] ???????????
	}
	delete[] m_data;
	delete[] colSizes;
}



// GETTERS
//getBlank() - returns blank char
std::string Board::getBlank() const {return blank;}


//getPiece() - returns specific  piece in specific column
std::string Board::getPiece(unsigned int j, unsigned int i) const {return m_data[j][i];} //asterisks????


//getcolCount() - returns colCount variable
int Board::getcolCount() const {return colCount;}


//getcolSize() - returns current size of specified column
int Board::getcolSize(unsigned int j) const {return colSizes[j];}


//isEmpty() - Checks if m_data has string-index pointer at an index
bool Board::isEmpty(unsigned int colIndex) const {
	if (m_data[colIndex] == NULL) {return true;}
	else {return false;}
}


//numRows() - loops through every column and returns the highest size,
//			  which is essentially the highest row
int Board::numRows() const {
	int maxRowSize = 0;														// Changing variable declared+initialized, used to track max
	for (int i=0 ; i<colCount ; ++i) {										// If current column is higher (has more rows), change to max
		if ((!isEmpty(i)) && (colSizes[i]>maxRowSize)) {
			maxRowSize = colSizes[i];
		}
	}
	return maxRowSize;
}


//numColumns() - returns colCount variable
int Board::numColumns() const {return colCount;}


//numTokensInRow() - returns count of how many tokens in column
int Board::numTokensInRow(int rowIndex) const {
	if (rowIndex>std::max((this->numRows()), 4)) {return -1;}					// Check if row exists (Note: 5 rows "exist" at start)
	else {
		unsigned int nTIR = 0;													// If column at least as tall as row index, token exists
		for (int i=0 ; i<colCount ; ++i) {
			if ((!isEmpty(i)) && (colSizes[i]>=rowIndex)) {
				nTIR+=1;															// Token existence couter +1 if column tall enough
			}
		}
		return nTIR;
	}
}


//numTokensInColumn() - returns count of how many tokens in column
int Board::numTokensInColumn(int colIndex) const {
	if (colIndex>=colCount) {return -1;}										// Check if column exists
	else {return colSizes[colIndex];}
}



// SETTERS
//insert() - inserts token at specific index - follows certain conditions
//			 if the column exists and there are token there already, if
//			 the column exsts and there are no tokens yet, or if the column
//			 does not yet exist - then, win conditions are checked and
//			 certain output will be given based on different conditions
std::string Board::insert(const int colIndex, const bool turn) {
	if (colIndex<colCount) {													// If inputted column exists in m_data, here
		if (isEmpty(colIndex)) {													// If no pointer/array at index, create new one
			m_data[colIndex] = new std::string[1];
			if (turn) {m_data[colIndex][0] = p1;}										// Place either p1 or p2 depending on param
			else {m_data[colIndex][0] = p2;}
			colSizes[colIndex] = 1;
		}
		else {																		// If pointer/array at index, simply push back
			if (turn) {push_back(p1, colIndex);}
			else {push_back(p2, colIndex);}
		}
	}
	else {																		// If column(s) doesn't exist yet, here
		std::string** temp_m_data = new std::string*[(colIndex+1)];					// Make temp_m_data that will have exact same info
		int* temp_colSizes = new int[(colIndex+1)];
		for (int i=0 ; i<(colIndex+1) ; ++i) {
			temp_m_data[i] = NULL; temp_colSizes[i] = 0;
		}

		for (int i=0 ; i<colCount ; ++i) {											// Every single elem of m_data's arrays copied over
			temp_m_data[i] = new std::string[colSizes[i]];
			for (int j=0 ; j<colSizes[i] ; ++j) {
				temp_m_data[i][j] = m_data[i][j];
			}
			temp_colSizes[i] = colSizes[i];											// Column sizes also copied over simultaneously
		}

		temp_m_data[colIndex] = new std::string[1];									// Create new array at specified index
		if (turn) {temp_m_data[colIndex][0] = p1;}									// Place either p1 or p2 depending on param
		else {temp_m_data[colIndex][0] = p2;}
		temp_colSizes[colIndex] = 1;

		for (int i=0 ; i<colCount ; ++i) {											// Loop through old m_data, delete any pointers/arrays
			if (m_data[i] != NULL) {delete[] m_data[i];}
		}
		delete[] m_data; delete[] colSizes;

		m_data = temp_m_data; colSizes = temp_colSizes; colCount = colIndex+1;		// All temporary values/pointers are made official
	}

	
	//Win Conditions
	//Vertical Win Cndition
	for (int i=0 ; i<colCount ; ++i) {												// Loop through every column w/ 4+ pieces
		if (colSizes[i]>=4) {
			for (int j=0 ; j<=(colSizes[i]-4) ; ++j) {									// Loop through column indeces (size-4 read frame)
				if ((m_data[i][j] == m_data[i][j+1])									// If 4 consec. pieces match...
				 && (m_data[i][j+1] == m_data[i][j+2])
				 && (m_data[i][j+2] == m_data[i][j+3])) {
					if (m_data[i][j] == p1) {return p1;}									// ...provide winner based on 1st piece 
					else if (m_data[i][j] == p2) {return p2;}
				}
			}
		}
	}
	//Horizontal Win Cindition
	for (int i=0 ; i<=(colCount-4) ; ++i) {											// Loop through every column w/ 3 adjacent columns
		if ((!isEmpty(i)) && (!isEmpty(i+1))										//	(4 consec. cols = 1 valid row)
		 && (!isEmpty(i+2)) && (!isEmpty(i+3))) {
			int minColSize = 1000;														// Sets min col height - only read cols as high
			for (int j=0 ; j<4 ; ++j) {
				if (colSizes[j+i]<minColSize) {
					minColSize = colSizes[j+i];
				}
			}
			for (int j=0 ; j<minColSize ; ++j) {										// Loop through indeces as high as minColSize
				if ((m_data[i][j] == m_data[i+1][j])										// If 4 consec. pieces match...
				 && (m_data[i+1][j] == m_data[i+2][j])
				 && (m_data[i+2][j] == m_data[i+3][j])) {
					if (m_data[i][j] == p1) {return p1;}										// ...provide winner based on 1st piece 
					else if (m_data[i][j] == p2) {return p2;}
				}
			}
		}	
	}
	return blank;																// If no win conditions met, return blank char
}


//push_back() - custom push_back() function only accessible by the
//				class - instead takes in 2 params: the token and the
//				column at which the token is being placed
void Board::push_back(const std::string& val, const unsigned int colIndex) {
	std::string* tempCol = new std::string[colSizes[colIndex]+1];				// Make temporary "column" with 1 additional index

	for (int i=0 ; i<colSizes[colIndex] ; ++i) {								// All elems. of original column placed in temp column
		tempCol[i] = m_data[colIndex][i];
	}
	colSizes[colIndex]+=1;														// Column size tracker increased by 1
	tempCol[colSizes[colIndex]-1] = val;										// Added value placed at last index of new array
	delete[] m_data[colIndex];													// Old pointer and array deleted 
	m_data[colIndex] = tempCol;													// m_data[colIndex] now points to where tempCol points
}


//operator=() - assigns right-side class obj to left-side class
//				obj - clears the left-side obj and assigns all
//				values of right-side obj to left-side
Board Board::operator=(const Board& classCopy) {
	clear();
	copy(classCopy);
	return *this;																// Returns memory address
}



// OTHERS
//copy() - function that is used by copy contructor + assignment operator
void Board::copy(const Board& classCopy) {
	this->colCount = classCopy.colCount;										// All member variables of original class copied to new
	this->m_data = new std::string*[this->colCount];							//  class
	this->colSizes = new int[this->colCount];
	this->p1 = classCopy.p1;
	this->p2 = classCopy.p2;
	this->blank = classCopy.blank;

	for (int i=0 ; i<(this->colCount) ; ++i) {									// Every single elem of m_data's arrays copied over
			this->colSizes[i] = classCopy.colSizes[i];							// Column sizes copied over simultaneously
			this->m_data[i] = classCopy.m_data[i];								// Copies all pointers
			this->m_data[i] = new std::string[this->colSizes[i]];				// Copies all data
			for (int j=0 ; j<(this->colSizes[i]) ; ++j) {
				this->m_data[i][j] = classCopy.m_data[i][j];
			}
		}
}

//create() - creates dynamic memory array for string-array pointers
//			 to be placed in
void Board::create(int newColCount) {
	colCount = newColCount;														// colCount updated to whatever new size
	m_data = new std::string*[colCount];										// m_data now points o new array of string pointers
	for (int i=0 ; i<colCount ; ++i) {m_data[i] = NULL;}						// all values in m_data are NULL - no pointers in them
	colSizes = new int[colCount];												// colSizes array created - tracks sizes of all columns
	for (int i=0 ; i<colCount ; ++i) {colSizes[i] = 0;}							// Since nothing there, all set to 0 for now
}


//clear() - deletes all data and recreates board using create()
//			again - pointers in m_data are deleted, so all
//			string-arrays are deleted - then, m_data and colSizes
//			are deleted
void Board::clear() {
	for (int i=0 ; i<colCount ; ++i) {											// If pointer/array exists at index of m_data, delete
		if (m_data[i] != NULL) {delete[] m_data[i];}
	}
	delete[] m_data; delete[] colSizes;	colCount = 0;							// Once all string-arrays deleted, delete larger arrays
	create(4);																	// Recreate/Reset board, as per instructions 
}


//operator<< - prints board in specific format as per homework
//			   instructions - always prints 5 rows and 4 columns
//			   unless tokens exceed these values - prints top-down
std::ostream& operator<<(std::ostream& os, const Board& board) {
	for (int i=std::max((board.numRows()-1), 4) ; i>=0 ; --i) {					// If numRows() > 4, print that many rows; else, 4 rows
		for (int j=0 ; j<board.getcolCount() ; ++j) {								// Print as many columns as there are
			if (board.getcolSize(j)<=i && j!=board.getcolCount()-1) {				// If "col. not as high as current row", blank
				os<<board.getBlank()<<" ";
			}
			else if (board.getcolSize(j)<=i && j==board.getcolCount()-1) {
				os<<board.getBlank();
			}
			else if (board.getcolSize(j)>i && j!=board.getcolCount()-1) {				// Else, print token in that column
				os<<board.getPiece(j, i)<<" ";
			}
			else if (board.getcolSize(j)>i && j==board.getcolCount()-1) {
				os<<board.getPiece(j, i);
			}
		}
		os<<std::endl;
	} 
	return os;
}