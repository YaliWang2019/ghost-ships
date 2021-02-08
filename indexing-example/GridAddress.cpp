#include <ctype.h>
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

GridAddress::GridAddress(char& row, int column)
{
	row = toupper(row);
	row_ = row;
	column_ = column;
}

bool GridAddress::CanCompileAddress(char& row, const int column)
{
	row = toupper(row);

	/*if (row != 'A' && row != 'B' && row != 'C' && row != 'D' && row != 'E' &&
		row != 'F' && row != 'G' && row != 'H' && row != 'I' && row != 'J') return false;*/
	if (row_map.count(row) == 0) return false;
	if (column < 1 || column > 10) return false;

	return true;
}

int GridAddress::GridIndex()
{
	return row_map[row_] *10 + column_ - 1;
}
