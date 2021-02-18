#ifndef GHOST_SHIPS_SHIP_COLLECTION_H
#define GHOST_SHIPS_SHIP_COLLECTION_H

#include <string>
#include <vector>

struct Ship {
	std::string Name;
	int Length;
};

class ShipCollection {

public:

	ShipCollection();

	const std::vector<Ship>& Ships() const { return ships; }
	int TotalLength() const { return total_ship_length; }

private:

	std::vector<Ship> ships;
	int total_ship_length;
};

#endif