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

	void SetHit(int index);
	void SetMiss(int index) { cell_status[index] = 3; }

	int TotalHits() { return total_hits; }
	bool CellFiredAt(int index) { return CellStatus(index) == "Miss" || CellStatus(index) == "Hit"; }

	bool ValidPlacements(Ship s, int index, std::vector<ShipPlacement>& placements) const;
	bool ValidPlacements(Ship s, GridAddress ga, std::vector<ShipPlacement>& placements) const 
	{ return ValidPlacements(s, ga.GridIndex(), placements); }

	void PlaceShip(Ship s, ShipPlacement p);
	void PlaceAuto(ShipCollection ships);

	std::string ShipName(int index) const { return ships[ship_at_cell_index.at(index)].Name; }
	std::string ShipName(GridAddress ga) const { return ShipName(ga.GridIndex()); }
	const ShipPlacement& GetShipPlacement(int index) const { return ship_placements[ship_at_cell_index.at(index)]; }

	friend std::ostream& operator<<(std::ostream& output, const Grid& g);

private:

	std::array<int, 100> cell_status = std::array<int, 100>();
	
	int total_hits;

	std::map<int, int> ship_at_cell_index;	
	std::vector<Ship> ships;
	std::vector<ShipPlacement> ship_placements;

	static std::map<int, std::string> status_string;

	bool CanPlaceUp(Ship s, int index, ShipPlacement& placement) const;
	bool CanPlaceRight(Ship s, int index, ShipPlacement& placement) const;
	bool CanPlaceDown(Ship s, int index, ShipPlacement& placement) const;
	bool CanPlaceLeft(Ship s, int index, ShipPlacement& placement) const;
};

#endif