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

private:
	std::vector<Ship> ships;
};

#endif