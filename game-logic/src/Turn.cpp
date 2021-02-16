#include "Turn.hpp"

Turn::Turn(int index, Grid& g)
{
	// need to pre-check user input of turn address to 
	// make sure they aren't trying using a repeat location

	is_ship_sunk = false;

	if (g.CellStatus(index) == "Empty") {
		g.SetMiss(index);
		is_hit = false;
	}
	if (g.CellStatus(index) == "Ship") {
		g.SetHit(index);
		is_hit = true;

		ShipPlacement hit_ship_placement = g.GetShipPlacement(index);
		is_ship_sunk = true;
		for (int i = 0; i < hit_ship_placement.Length(); i++) {
			if (g.CellStatus(hit_ship_placement[i]) != "Hit") is_ship_sunk = false;
		}
	}
}