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

TEST_CASE("String constructor functions") {

	std::string s("J9");
	GridAddress ga(s);
	char row = s[0];
	int col = std::stoi(s.substr(1));

	REQUIRE(ga.Row() == row);
	REQUIRE(ga.Column() == col);

	s.clear();
	s += "K9";

	REQUIRE_THROWS_AS([&]() { GridAddress gb(s); }(), std::invalid_argument);

	s.clear();
	s += "B11";

	REQUIRE_THROWS_AS([&]() { GridAddress gb(s); }(), std::invalid_argument);
}