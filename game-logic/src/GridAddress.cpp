#include <ctype.h>
#include <stdexcept>
#include <string>
#include "GridAddress.hpp"

std::map<char, int> GridAddress::row_map = {
	{'A', 0}, {'B', 1},	{'C', 2}, {'D', 3},	{'E', 4},
	{'F', 5}, {'G', 6},	{'H', 7}, {'I', 8},	{'J', 9}
};

std::vector<char> GridAddress::row_designators = {
	'A','B','C','D','E','F','G','H','I','J'
};

GridAddress::GridAddress()
{
	row_ = 'A';
	column_ = 1;
}

GridAddress::GridAddress(char row, int column)
{
	row_ = toupper(row);
	column_ = column;
	if (!CanCompileAddress(row_, column_)) throw std::invalid_argument("Invalid Address Input");
}

GridAddress::GridAddress(std::string s)
{
	if (!IsValidInput(s)) throw std::invalid_argument("Invalid Address Input");
	row_ = toupper(s[0]);
	column_ = std::stoi(s.substr(1));
}

GridAddress::GridAddress(int index)
{
	if (index < 0 || index > 99) throw std::invalid_argument("Invalid Address Input");
	row_ = row_designators[index / 10];
	column_ = (index % 10) + 1;
}

bool GridAddress::IsValidInput(std::string s)
{
	if (s.size() < 2) return false;
	char r = toupper(s[0]);
	int c = 0; 
	try {
		c = std::stoi(s.substr(1));
	}
	catch (const std::invalid_argument&) {
		return false;
	}
	return CanCompileAddress(r, c);
}

bool GridAddress::CanCompileAddress(char row, const int column)
{
	row = toupper(row);

	if (row_map.count(row) == 0) return false;
	if (column < 1 || column > 10) return false;

	return true;
}