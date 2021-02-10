#include "catch.hpp"
#include "../src/GridAddress.hpp"

TEST_CASE( "Default address is A1" ) {

	GridAddress ga;

	REQUIRE(ga.Row() == 'A');
	REQUIRE(ga.Column() == 1);
}