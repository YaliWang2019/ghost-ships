#ifndef GHOST_SHIPS_GRID_H
#define GHOST_SHIPS_GRID_H

#include <array>
#include <map>
#include <string>
#include <vector>
#include "GridAddress.hpp"

class Grid {

public:

	Grid() {}

	std::string CellStatus(int index);

private:

	std::array<int, 100> cell_status = std::array<int, 100>();
	static std::map<int, std::string> status_string;
};

#endif