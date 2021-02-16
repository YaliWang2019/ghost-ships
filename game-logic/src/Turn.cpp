#include "Turn.hpp"

Turn::Turn(int index, Grid& g)
{
	// need to pre-check user input of turn address to 
	// make sure they aren't trying using a repeat location

	if (g.CellStatus(index) == "Empty") {
		g.SetMiss(index);
		turn_outcome = "Miss.";
	}
	if (g.CellStatus(index) == "Ship") {
		g.SetHit(index);
		turn_outcome = "Hit!";

		ShipPlacement hit_ship_placement = g.GetShipPlacement(index);
		bool is_ship_sunk = true;
		for (int i = 0; i < hit_ship_placement.Length(); i++) {
			if (g.CellStatus(hit_ship_placement[i]) != "Hit") is_ship_sunk = false;
		}

		if (is_ship_sunk) turn_outcome += "\nThe " + g.ShipName(index) + " has been sunk!";
	}
}