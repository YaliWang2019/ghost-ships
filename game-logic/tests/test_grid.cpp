#include "catch.hpp"
#include "../src/Grid.hpp"
#include "../src/GridAddress.hpp"
#include "../src/ShipCollection.hpp"

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

	result = g.SetShip(95);
	REQUIRE(result == true);
	REQUIRE(g.CellStatus(95) == "Ship");

	REQUIRE_THROWS_AS([&]() { g.SetShip(-1); }(), std::out_of_range);
}

TEST_CASE("Ship placement test functions") {

	Grid g;
	Ship s{ "Test_Ship", 4 };

	for (int i = 0; i < 99; i++) {
		REQUIRE(g.CanPlace(s, i) == true);
	}

	g.SetShip(2); g.SetShip(12); 
	g.SetShip(22); g.SetShip(21);

	REQUIRE(g.CanPlace(s, 11) == false);
}