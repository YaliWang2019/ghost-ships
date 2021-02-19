#include <iostream>
#include <string>
#include <vector>
#include "Adversary.hpp"
#include "Grid.hpp"
#include "GridAddress.hpp"
#include "ShipCollection.hpp"
#include "Turn.hpp"

void PrintBoards(Grid g1, Grid g2) {

	std::cout << "\n\n      01 02 03 04 05 06 07 08 09 10       01 02 03 04 05 06 07 08 09 10\n\n";
	
	int curr_index = 0;
	for (int i = 0; i < 10; i++) {
		
		std::cout << "    " << GridAddress::RowAtIndex(curr_index);		
		for (int j = 0; j < 10; j++) {
			std::cout << " ";
			if (g1.CellStatus(curr_index) == "Empty") std::cout << "..";
			else if (g1.CellStatus(curr_index) == "Ship") {
				std::cout << g1.ShipName(curr_index).substr(0, 2);
			}
			else if (g1.CellStatus(curr_index) == "Miss") std::cout << "..";
			else if (g1.CellStatus(curr_index) == "Hit") std::cout << "xx";

			curr_index++;
		}

		curr_index -= 10;

		std::cout << "     " << GridAddress::RowAtIndex(curr_index);
		for (int j = 0; j < 10; j++) {
			std::cout << " ";
			if (g2.CellStatus(curr_index) == "Empty" || g2.CellStatus(curr_index) == "Ship") std::cout << "..";
			else if (g2.CellStatus(curr_index) == "Miss") std::cout << "[]";
			else if (g2.CellStatus(curr_index) == "Hit") std::cout << "xx";
			curr_index++;
		}

		std::cout << "\n\n";
	}
}

void PrintMessage(std::string s) {
	std::cout << "\n    " << s << "\n    ";
}

std::string GetString() {
	std::string input;
	std::cout << "\r    ";
	std::cin >> input;
	return input;
}

GridAddress GetAddress() {
	std::string address_string;
	while (!GridAddress::IsValidInput(address_string)) { address_string = GetString(); }
	GridAddress ga(address_string);
	return ga;
}

int main()
{
	ShipCollection sc;          // classic 5 ships; may be customized in future
	Grid player_grid;
	Grid pc_grid;
	pc_grid.PlaceAuto(sc);
	Adversary pc;
	PrintBoards(player_grid, pc_grid);

	// let user select mode
	PrintMessage("Choose Mode : [1] Easy  [2] Hard  [3] Very Hard");
	std::string mode;
	while (mode != "1" && mode != "2" && mode != "3") {
		mode = GetString();
	}

	// have user place their ships
	for (auto& s : sc.Ships()) {

		bool can_place = false;
		std::vector<ShipPlacement> placements;

		while (!can_place) {

			PrintMessage("Enter start position for " + s.Name + ":");
			GridAddress start_add = GetAddress();
			if (player_grid.ValidPlacements(s, start_add, placements)) can_place = true;
		}

		std::vector<std::string> valid_opts;
		for (int i = 0; i < placements.size(); i++) valid_opts.push_back(std::to_string(i + 1));
		std::string selected_opt;

		can_place = false;
		while (!can_place) {
			std::string end_opts = "Choose endpoint:";
			for (int i = 0; i < placements.size(); i++) {
				end_opts += " [" + std::to_string(i + 1) + "] for " + placements[i].EndPoint().AsString();
			}

			PrintMessage(end_opts);
			selected_opt = GetString();
			can_place = find(valid_opts.begin(), valid_opts.end(), selected_opt) != valid_opts.end();
		}

		int choice = stoi(selected_opt) - 1;
		player_grid.PlaceShip(s, placements[choice]);

		PrintBoards(player_grid, pc_grid);
	}

	// if a harder play mode selected, update player_grid
	if (mode == "2") player_grid.ActivateHardMode(30);
	if (mode == "3") player_grid.ActivateHardMode(55);

	int number_of_turns = 0;

	// commence turns until pc or player sinks all ships
	while (player_grid.TotalHits() != sc.TotalLength() && pc_grid.TotalHits() != sc.TotalLength()) {

		number_of_turns++;

		PrintMessage("Choose target to fire at:");
		GridAddress target;
		bool valid_target = false;
		while (!valid_target) {
			GridAddress ga = GetAddress();
			if (!pc_grid.CellFiredAt(ga.GridIndex())) {
				target = ga;
				valid_target = true;
			}
		}

		Turn player_turn(target.GridIndex(), pc_grid);
		std::string turn_result;

		if (player_turn.IsHit()) {
			turn_result = "Hit!";
			if (player_turn.IsShipSunk()) turn_result += " You sunk the PC's " + pc_grid.ShipName(target) + "!";
			PrintBoards(player_grid, pc_grid);
			PrintMessage(turn_result);
		}
		else {
			turn_result = "Miss!";
			PrintBoards(player_grid, pc_grid);
			PrintMessage(turn_result);
		}

		PrintMessage("Press enter to continue...");
		std::cin.ignore(1, '\n');
		std::cin.get();

		Turn pc_turn = pc.NextTurn(player_grid);

		if (pc_turn.IsHit()) {
			turn_result = "PC Hit! (" + pc_turn.Target().AsString() + ")";
			if (pc_turn.IsShipSunk()) turn_result += " The PC sunk your " + player_grid.ShipName(pc_turn.Target()) + "!";
			PrintBoards(player_grid, pc_grid);
			PrintMessage(turn_result);
		}
		else {
			turn_result = "PC Miss!";
			PrintBoards(player_grid, pc_grid);
			PrintMessage(turn_result);
		}
	}

	if (pc_grid.TotalHits() == sc.TotalLength()) {

		PrintMessage("Congratulations, you've won!");
	}
	else {
		PrintMessage("You've lost, try again -- ");
	}

	//PrintMessage("Total number of Turns : " + number_of_turns);
	PrintMessage("Player Accuracy : " + std::to_string((float)pc_grid.TotalHits() / number_of_turns));
	PrintMessage("PC Accuracy : " + std::to_string((float)player_grid.TotalHits() / number_of_turns));

	std::cin.ignore(1, '\n');
	std::cin.get();
}