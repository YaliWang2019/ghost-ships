#include "catch.hpp"
#include "../src/GridAddress.hpp"

TEST_CASE( "Default address is A1" ) {

	GridAddress ga;

	REQUIRE(ga.Row() == 'A');
	REQUIRE(ga.Column() == 1);
}

TEST_CASE("Parameterized constructor functions") {

	char row = 'C';
	int col = 9;
	GridAddress ga(row, col);

	REQUIRE(ga.Row() == row);
	REQUIRE(ga.Column() == col);
}