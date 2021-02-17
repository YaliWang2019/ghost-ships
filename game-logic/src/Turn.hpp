#ifndef GHOST_SHIPS_TURN_H
#define GHOST_SHIPS_TURN_H

#include "Grid.hpp"
#include "GridAddress.hpp"

class Turn {

public:

	Turn(int index, Grid& g);
	static Turn AutoFire(Grid& g);

	bool IsHit() { return is_hit; }
	bool IsShipSunk() { return is_ship_sunk; }

	GridAddress Target() { return GridAddress(target_index); }

private:

	int target_index;
	bool is_hit;
	bool is_ship_sunk;

};

#endif