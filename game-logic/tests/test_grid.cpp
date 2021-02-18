#include "catch.hpp"
#include <iostream>
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

TEST_CASE("Grid valid placement test") {

	Grid g;
	Ship s1{ "TestShip", 2 };
	GridAddress ga1{ "C3" };

	std::vector<ShipPlacement> places;
	bool result = g.ValidPlacements(s1, ga1, places);
	
	REQUIRE(result == true);
	REQUIRE(places.size() == 4);

	for (auto& p : places) {
		REQUIRE(p.Length() == s1.Length);
	}

	Ship s2{ "TestVessel",4 };
	GridAddress ga2{ "I9" };

	places.clear();
	result = g.ValidPlacements(s2, ga2, places);

	REQUIRE(result == true);
	REQUIRE(places.size() == 2);

	for (auto& p : places) {
		REQUIRE(p.Length() == s2.Length);
	}

	g.SetShip(GridAddress("I8"));
	g.SetShip(GridAddress("H9"));

	places.clear();
	result = g.ValidPlacements(s2, ga2, places);

	REQUIRE(result == false);
}

TEST_CASE("Grid place ship test") {

	int ship_length = 3;
	std::string ship_name = "vessel";
	GridAddress starting_point("B9");
	Ship s{ ship_name,ship_length };

	Grid g;
	std::vector<ShipPlacement> p;
	g.ValidPlacements(s, starting_point, p);	
	
	for (auto& pl : p) {
		g.PlaceShip(s, pl);
		for (int i = 0; i < pl.Length(); i++) {
			REQUIRE(g.CellStatus(pl[i]) == "Ship");
			REQUIRE(g.ShipName(pl[i]) == ship_name);
		}
	}
}

TEST_CASE("Valid placements should not overlap existing") {

	Grid g;
	g.SetShip(11); g.SetShip(21); g.SetShip(31); g.SetShip(30);

	Ship s{ "test_vessel",3 };

	std::vector<ShipPlacement> pl;
	bool result = g.ValidPlacements(s, 10, pl);
	REQUIRE(result == false);
	
	result = g.ValidPlacements(s, 20, pl);
	REQUIRE(result == true);
	REQUIRE(pl.size() == 1);
	
	pl.clear();

	result = g.ValidPlacements(s, 0, pl);
	REQUIRE(result == true);
	REQUIRE(pl.size() == 2);

	for (int num_tests = 0; num_tests < 50; num_tests++) {

		Grid g2;
		ShipCollection sc;
		g2.PlaceAuto(sc);

		int total_lengths = 0;
		for (auto& s : sc.Ships()) total_lengths += s.Length;

		int total_ship_spaces = 0;
		for (int i = 0; i < 100; i++) if (g2.CellStatus(i) == "Ship") total_ship_spaces++;
		REQUIRE(total_lengths == total_ship_spaces);
	}
}

TEST_CASE("Hard mode sets cells to miss") {

	Grid g;
	ShipCollection sc;
	g.PlaceAuto(sc);

	int number_cells_to_remove = 35;
	g.ActivateHardMode(35);

	int number_ship_cells = 0;
	int number_miss_cells = 0;

	for (int i = 0; i < 100; i++) {
		if (g.CellStatus(i) == "Ship") number_ship_cells++;
		else if (g.CellStatus(i) == "Miss") number_miss_cells++;
	}

	REQUIRE(number_ship_cells == sc.TotalLength());
	REQUIRE(number_miss_cells == number_cells_to_remove);
}