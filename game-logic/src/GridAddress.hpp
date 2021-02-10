#ifndef GHOST_SHIPS_GRID_ADDRESS_H
#define GHOST_SHIPS_GRID_ADDRESS_H

#include <map>

class GridAddress {

public:

	GridAddress(char& row, int column);
	static bool CanCompileAddress(char& row, const int column);

	char Row() { return row_; }
	char Column() { return column_; }
	int GridIndex();

private:
	char row_;
	int column_;
	static std::map<char, int> row_map;
};

#endif
