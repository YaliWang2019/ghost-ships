#ifndef GHOST_SHIPS_GRID_H
#define GHOST_SHIPS_GRID_H

#include <array>
#include <map>
#include <ostream>
#include <string>
#include <vector>
#include "GridAddress.hpp"
#include "ShipCollection.hpp"
#include "ShipPlacement.hpp"

class Grid {

public:

	Grid() {}

	std::string CellStatus(int index) const;
	std::string CellStatus(GridAddress add) const { return CellStatus(add.GridIndex()); }

	bool SetShip(int index);                                              // using while testing;
	bool SetShip(GridAddress ga) { return SetShip(ga.GridIndex()); }      // using while testing;

	void SetHit(int index) { cell_status[index] = 2; }
	void SetMiss(int index) { cell_status[index] = 3; }

	bool ValidPlacements(Ship s, int index, std::vector<ShipPlacement>& placements) const;
	bool ValidPlacements(Ship s, GridAddress ga, std::vector<ShipPlacement>& placements) const 
	{ return ValidPlacements(s, ga.GridIndex(), placements); }

	void PlaceShip(Ship s, ShipPlacement p);
	std::string ShipName(int index) const { return ship_names.at(index); }

	void PlaceAuto(ShipCollection ships);

	friend std::ostream& operator<<(std::ostream& output, const Grid& g);

private:

	std::array<int, 100> cell_status = std::array<int, 100>();
	std::map<int, std::string> ship_names;
	static std::map<int, std::string> status_string;

	bool CanPlaceUp(Ship s, int index, ShipPlacement& placement) const;
	bool CanPlaceRight(Ship s, int index, ShipPlacement& placement) const;
	bool CanPlaceDown(Ship s, int index, ShipPlacement& placement) const;
	bool CanPlaceLeft(Ship s, int index, ShipPlacement& placement) const;
};

#endif