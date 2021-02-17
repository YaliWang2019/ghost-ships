#include <random>
#include "Turn.hpp"

Turn::Turn(int index, Grid& g)
{
	// need to pre-check user input of turn address to 
	// make sure they aren't trying using a repeat location

	target_index = index;
	is_hit = false;
	is_ship_sunk = false;

	if (g.CellStatus(index) == "Empty") {
		g.SetMiss(index);
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

Turn Turn::AutoFire(Grid& g)
{
	std::random_device rd;
	std::default_random_engine re(rd());
	std::uniform_int_distribution<int> index_dist(0, 99);

	int index = index_dist(re);
	while (!(g.CellStatus(index) == "Empty" || g.CellStatus(index) == "Ship")) {
		index = index_dist(re);
	}

	Turn t(index, g);
	return t;
}