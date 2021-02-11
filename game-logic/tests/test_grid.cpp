#include "catch.hpp"
#include "../src/Grid.hpp"
#include "../src/GridAddress.hpp"

TEST_CASE("New grid reports all cells empty") {

	Grid g;

	for (int i = 0; i < 100; i++) {
		REQUIRE(g.CellStatus(i) == "Empty");
	}
}

TEST_CASE("Setting cell to ship status functions") {

	Grid g;
	GridAddress ga("B7");

	bool result = g.SetShip(ga);
	REQUIRE(result == true);
	REQUIRE(g.CellStatus(ga) == "Ship");
}