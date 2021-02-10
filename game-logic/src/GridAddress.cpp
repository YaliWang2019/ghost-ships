#include <ctype.h>
#include <stdexcept>
#include <string>
#include "GridAddress.hpp"

std::map<char, int> GridAddress::row_map = {
	{'A', 0},
	{'B', 1},
	{'C', 2},
	{'D', 3},
	{'E', 4},
	{'F', 5},
	{'G', 6},
	{'H', 7},
	{'I', 8},
	{'J', 9},
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
	row_ = toupper(s[0]);
	column_ = std::stoi(s.substr(1));
	if (!CanCompileAddress(row_, column_)) throw std::invalid_argument("Invalid Address Input");
}

bool GridAddress::IsValidInput(std::string s)
{
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

int GridAddress::GridIndex()
{
	return row_map[row_] *10 + column_ - 1;
}
