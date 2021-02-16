#ifndef GHOST_SHIPS_TURN_H
#define GHOST_SHIPS_TURN_H

#include "Grid.hpp"
#include "GridAddress.hpp"

class Turn {

public:

	Turn(int index, Grid& g);
	Turn(GridAddress ga, Grid& g) : Turn(ga.GridIndex(), g) {}

	std::string Outcome() const { return turn_outcome; }

private:

	std::string turn_outcome;
};

#endif