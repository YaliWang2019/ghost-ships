#include "catch.hpp"
#include "../src/Grid.hpp"
#include "../src/Turn.hpp"

TEST_CASE("Firing at ships produces correct outcomes") {

	int start_index = 11;

	Grid g;
	Ship s{ "Carrier",5 };
	ShipPlacement pl(start_index);
	for (int i = 1; i < s.Length; i++) {
		pl.Add(start_index + i);
	}
	pl.Finalize();
	g.PlaceShip(s, pl);

	Turn t(5, g);
	REQUIRE(t.IsHit() == false);
	REQUIRE(t.IsShipSunk() == false);
	REQUIRE(g.CellStatus(5) == "Miss");

	Turn t2(11, g);
	REQUIRE(t2.IsHit() == true);
	REQUIRE(t2.IsShipSunk() == false);
	REQUIRE(g.CellStatus(11) == "Hit");

	Turn t3(12, g);
	Turn t4(13, g);
	Turn t5(14, g);
	Turn t6(15, g);
	REQUIRE(t6.IsHit() == true);
	REQUIRE(t6.IsShipSunk() == true);
}