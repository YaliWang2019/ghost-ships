#ifndef GHOST_SHIPS_GRID_ADDRESS_H
#define GHOST_SHIPS_GRID_ADDRESS_H

#include <map>
#include <vector>

class GridAddress {

public:

	GridAddress();
	GridAddress(char row, int column);
	GridAddress(std::string s);
	GridAddress(int index);

	char Row() { return row_; }
	char Column() { return column_; }
	int GridIndex() { return row_map[row_] * 10 + column_ - 1; }
	std::string AsString() { return row_ + std::to_string(column_); }

	static bool IsValidInput(std::string s);
	static bool CanCompileAddress(char row, const int column);

private:
	char row_;
	int column_;
	static std::map<char, int> row_map;
	static std::vector<char> row_designators;
};

#endif
