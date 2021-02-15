#include "catch.hpp"
#include "../src/ShipCollection.hpp"

TEST_CASE(" Default ship collection ctor works") {

	ShipCollection sc;
	auto& s = sc.Ships();

	REQUIRE(s.size() == 5);

	for (auto& sh : s) {
		if (sh.Name == "Carrier") REQUIRE(sh.Length == 5);
		else if (sh.Name == "Battleship") REQUIRE(sh.Length == 4);
		else if (sh.Name == "Cruiser") REQUIRE(sh.Length == 3);
		else if (sh.Name == "Submarine") REQUIRE(sh.Length == 3);
		else if (sh.Name == "Destroyer") REQUIRE(sh.Length == 2);
		else FAIL("Default ctor missing ship");
	}
}