#include <iostream>
#include <random>
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

bool Grid::CanPlaceUp(Ship s, int index, ShipPlacement& placement) const
{
	bool can_move_up = true;
	for (int i = 1; i < s.Length; i++) {
		index -= 10;
		if (index < 0 || cell_status[index] != 0) {
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
			if (new_address.Row() != test_address.Row() || cell_status[index] != 0) {
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
		if (index > 99 || cell_status[index] != 0) {
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
			if (new_address.Row() != test_address.Row() || cell_status[index] != 0) {
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
	if (cell_status[index] != 0) return false;
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

void Grid::PlaceShip(Ship s, ShipPlacement p)
{
	ships.push_back(s);
	ship_placements.push_back(p);

	for (int i = 0; i < p.Length(); i++) {
		cell_status[p[i]] = 1;
		ship_at_cell_index.emplace(p[i], ships.size() - 1);
	}
}

void Grid::PlaceAuto(ShipCollection ships)
{
	// 01 per ship, choose random index 0 - 99
	// 02 per valid orientations, choose random
	//    [ if none, choose new index ]

	std::random_device rd;
	std::default_random_engine re(rd());
	std::uniform_int_distribution<int> index_dist(0, 99);
	std::uniform_int_distribution<int> placement_dist(0, 3);

	for (auto& s : ships.Ships()) {
		
		int index;
		std::vector<ShipPlacement> placements;

		bool can_use = false;
		while (!can_use) {

			index = index_dist(re);
			can_use = true;
			placements.clear();

			if (cell_status[index] == 1) can_use = false;
			if (!ValidPlacements(s, index, placements)) can_use = false;
		}

		int placement_selection = 4;
		while (placement_selection >= placements.size()) {
			placement_selection = placement_dist(re);
		}

		PlaceShip(s, placements[placement_selection]);
	}
}

std::ostream& operator<<(std::ostream& output, const Grid& g)
{
	int curr_cell = 0;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			//std::cout << " " <<g.cell_status[curr_cell] << " ";
			if (g.cell_status[curr_cell] == 0) std::cout << " .. ";
			else if (g.cell_status[curr_cell] == 1) {
				std::cout << " " << g.ShipName(curr_cell).substr(0,2) << " ";
			}
			// add hit / miss output here once implemented
			curr_cell++;
		}
		std::cout << "\n";
	}

	return output;
}