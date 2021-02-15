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

	s.clear();
	s += "ADDRESS";

	REQUIRE_THROWS_AS([&]() { GridAddress gb(s); }(), std::invalid_argument);
}

TEST_CASE("Index constructor functions") {

	std::vector<char> rows;
	rows.push_back('A'); rows.push_back('B'); rows.push_back('C'); rows.push_back('D'); rows.push_back('E');
	rows.push_back('F'); rows.push_back('G'); rows.push_back('H'); rows.push_back('I'); rows.push_back('J');

	int curr_index = 0;

	for (int i = 0; i < 10; i++) {
		for (int j = 1; j < 11; j++) {
			std::string s;
			s += rows[i]; s += std::to_string(j);
			GridAddress ga(curr_index);
			curr_index++;
			REQUIRE(ga.AsString() == s);
		}
	}

	REQUIRE(GridAddress::IsValidInput("anything_else") == false);
}

TEST_CASE("String verification of Address works") {
		
	std::vector<char> rows;
	rows.push_back('A'); rows.push_back('B'); rows.push_back('C'); rows.push_back('D'); rows.push_back('E');
	rows.push_back('F'); rows.push_back('G'); rows.push_back('H'); rows.push_back('I'); rows.push_back('J');

	for (int i = 0; i < 10; i++) {
		for (int j = 1; j < 11; j++) {
			std::string s;
			s += rows[i]; s += std::to_string(j);
			REQUIRE(GridAddress::IsValidInput(s) == true);
			s.clear();
			s += tolower(rows[i]); s += std::to_string(j);
			REQUIRE(GridAddress::IsValidInput(s) == true);
		}
	}

	REQUIRE(GridAddress::IsValidInput("anything_else") == false);
}

TEST_CASE("AsString output is correct") {

	std::vector<char> rows;
	rows.push_back('A'); rows.push_back('B'); rows.push_back('C'); rows.push_back('D'); rows.push_back('E');
	rows.push_back('F'); rows.push_back('G'); rows.push_back('H'); rows.push_back('I'); rows.push_back('J');

	for (int i = 0; i < 10; i++) {
		for (int j = 1; j < 11; j++) {
			std::string s;
			s += rows[i]; s += std::to_string(j);
			GridAddress ga(s);
			REQUIRE(ga.AsString() == s);
		}
	}
}