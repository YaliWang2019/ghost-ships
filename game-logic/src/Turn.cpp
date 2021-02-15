#include "Turn.hpp"

Turn::Turn(int index, Grid& g)
{
	if (g.CellStatus(index) == "Empty") {
		g.SetMiss(index);
		turn_outcome = "Miss";
	}
	if (g.CellStatus(index) == "Ship") {
		g.SetHit(index);
		turn_outcome = "Hit";

		// need to implement code here to query all instances
		// of cell w/ same ship name to update turn_outcome to
		// include the sinking of a ship that has been found
	}
}