#include <iostream>
#include <string>

#ifndef Board_h_
#define Board_h_

class Board {
public:
	// CONSTRUCTORS:
	Board();																	// Default
	Board(std::string ap1, std::string ap2, std::string ablank);				// Default w/ params
	Board(const Board& classCopy);												// Copy
	~Board();																	// Destructor

	// ACCESSORS:
	std::string getBlank() const;
	std::string getPiece(unsigned int j, unsigned int i) const;
	int getcolCount() const;
	int getcolSize(unsigned int j) const;
	bool isEmpty(unsigned int colIndex) const;
	int numRows() const;
	int numColumns() const;
	int numTokensInRow(int rowIndex) const;
	int numTokensInColumn(int colIndex) const;

	// MODIFIERS:
	std::string insert(const int colIndex, const bool turn);
	Board operator=(const Board& classCopy);

	// OTHERS:
	void create(int newColCount);
	void clear();
	
private:
	void copy(const Board& classCopy);
	void push_back(const std::string& val, const unsigned int colIndex);		// Custom push_back function with unnique params

	std::string** m_data;
	int* colSizes;
	int colCount;

	std::string p1;
	std::string p2;
	std::string blank;

};

std::ostream& operator<<(std::ostream& os, const Board& board);

#endif