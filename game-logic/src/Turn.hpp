#ifndef GHOST_SHIPS_TURN_H
#define GHOST_SHIPS_TURN_H

#include "Grid.hpp"
#include "GridAddress.hpp"

class Turn {

public:

	Turn(int index, Grid& g);
	Turn(GridAddress ga, Grid& g) : Turn(ga.GridIndex(), g) {}

	bool IsHit() { return is_hit; }
	bool IsShipSunk() { return is_ship_sunk; }

private:

	bool is_hit;
	bool is_ship_sunk;

};

#endif