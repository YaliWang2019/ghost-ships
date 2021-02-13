#include <iostream>
#include <stdexcept>
#include "Grid.hpp"

std::map<int, std::string> Grid::status_string = {
	{0, "Empty"}, {1, "Ship"}, {2, "Hit"}, {3, "Miss"} };

std::string Grid::CellStatus(int index) const {
	if (index < 0 || index > 99) throw std::out_of_range("Index exceeds grid limits");
	return status_string[cell_status[index]];
}

bool Grid::SetShip(int index)
{
	if (index < 0 || index > 99) throw std::out_of_range("Index exceeds grid limits");
	if (cell_status[index] == 0) {
		cell_status[index] = 1;
		return true;
	}
	else return false;
}

bool Grid::CanPlace(Ship s, int index) const
{
	if (CellStatus(index) != "Empty") return false;
	
	GridAddress test_address(index);

	// to be refactored

	// upwards

	bool can_move_up = true;
	int temp_index = index;
	for (int i = 1; i < s.Length; i++) {
		temp_index -= 10;
		if (temp_index < 0 || CellStatus(temp_index) != "Empty") {
			can_move_up = false;
			break;
		}
	}

	// to the right

	bool can_move_right = true;
	temp_index = index;
	for (int i = 1; i < s.Length; i++) {
		temp_index++;
		if (temp_index < 99) {
			GridAddress new_address(temp_index);
			if (new_address.Row() != test_address.Row() || CellStatus(temp_index) != "Empty") {
				can_move_right = false;
				break;
			}
		}
	}

	// downwards

	bool can_move_down = true;
	temp_index = index;
	for (int i = 1; i < s.Length; i++) {
		temp_index += 10;
		if (temp_index > 99 || CellStatus(temp_index) != "Empty") {
			can_move_down = false;
			break;
		}
	}

	// to the left

	bool can_move_left = true;
	temp_index = index;
	for (int i = 1; i < s.Length; i++) {
		temp_index--;
		if (temp_index > -1) {
			GridAddress new_address(temp_index);
			if (new_address.Row() != test_address.Row() || CellStatus(temp_index) != "Empty") {
				can_move_left = false;
				break;
			}
		}
	}

	return can_move_up || can_move_right || can_move_down || can_move_left;
}

bool Grid::CanPlaceUp(Ship s, int index, ShipPlacement& placement) const
{
	bool can_move_up = true;
	for (int i = 1; i < s.Length; i++) {
		index -= 10;
		if (index < 0 || CellStatus(index) != "Empty") {
			can_move_up = false;
			break;
		}
		else placement.Add(index);
	}

	if (can_move_up) placement.Finalize();
	return can_move_up;
}

bool Grid::CanPlaceRight(Ship s, int index, ShipPlacement& placement) const
{
	bool can_move_right = true;
	GridAddress test_address(index);
	for (int i = 1; i < s.Length; i++) {
		index++;
		if (index < 99) {
			GridAddress new_address(index);
			if (new_address.Row() != test_address.Row() || CellStatus(index) != "Empty") {
				can_move_right = false;
				break;
			}
			else placement.Add(index);
		}
		else {
			can_move_right = false;
			break;
		}
	}
	
	if (can_move_right) placement.Finalize();
	return can_move_right;
}

bool Grid::CanPlaceDown(Ship s, int index, ShipPlacement& placement) const
{
	bool can_move_down = true;
	for (int i = 1; i < s.Length; i++) {
		index += 10;
		if (index > 99 || CellStatus(index) != "Empty") {
			can_move_down = false;
			break;
		}
		else placement.Add(index);
	}

	if (can_move_down) placement.Finalize();
	return can_move_down;
}

bool Grid::CanPlaceLeft(Ship s, int index, ShipPlacement& placement) const
{
	bool can_move_left = true;
	GridAddress test_address(index);
	for (int i = 1; i < s.Length; i++) {
		index--;
		if (index > -1) {
			GridAddress new_address(index);
			if (new_address.Row() != test_address.Row() || CellStatus(index) != "Empty") {
				can_move_left = false;
				break;
			}
			else placement.Add(index);
		}
		else {
			can_move_left = false;
			break;
		}
	}

	if (can_move_left) placement.Finalize();
	return can_move_left;
}

bool Grid::ValidPlacements(Ship s, int index, std::vector<ShipPlacement>& placements) const
{
	{
		ShipPlacement placement(index);
		if (CanPlaceUp(s, index, placement)) {
			placements.push_back(placement);
		}
	}

	{
		ShipPlacement placement(index);
		if (CanPlaceRight(s, index, placement)) {
			placements.push_back(placement);
		}
	}

	{
		ShipPlacement placement(index);
		if (CanPlaceDown(s, index, placement)) {
			placements.push_back(placement);
		}
	}

	{
		ShipPlacement placement(index);
		if (CanPlaceLeft(s, index, placement)) {
			placements.push_back(placement);
		}
	}

	return placements.size() > 0;
}


std::ostream& operator<<(std::ostream& output, const Grid& g)
{
	int curr_cell = 0;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			std::cout << " " <<g.cell_status[curr_cell] << " ";
			curr_cell++;
		}
		std::cout << "\n";
	}

	return output;
}