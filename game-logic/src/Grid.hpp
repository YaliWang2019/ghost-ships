#ifndef GHOST_SHIPS_GRID_H
#define GHOST_SHIPS_GRID_H

#include <array>
#include <map>
#include <ostream>
#include <string>
#include <vector>
#include "GridAddress.hpp"

class Grid {

public:

	Grid() {}

	std::string CellStatus(int index);
	std::string CellStatus(GridAddress add) { return CellStatus(add.GridIndex()); }

	// NOTES : now need to change SetShip as written to private; public metho will use
	//         an input Ship struct, and only return true if there is room to place ship;
	//         then need a function for outputting legitimate end-points to choose from;
	//         will also need a private function that calls SetShip for every cell the
	//         input vessel covers.

	bool SetShip(int index);
	bool SetShip(GridAddress ga) { return SetShip(ga.GridIndex()); }

	friend std::ostream& operator<<(std::ostream& output, const Grid& g);

private:

	std::array<int, 100> cell_status = std::array<int, 100>();
	static std::map<int, std::string> status_string;
};

#endif