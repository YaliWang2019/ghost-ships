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

	bool moveUp = true;
	int temp_index = index;
	for (int i = 1; i < s.Length; i++) {
		temp_index -= 10;
		if (temp_index < 0 || CellStatus(temp_index) != "Empty") {
			moveUp = false;
			break;
		}
	}

	// to the right

	bool moveRight = true;
	temp_index = index;
	for (int i = 1; i < s.Length; i++) {
		temp_index++;
		if (temp_index < 99) {
			GridAddress new_address(temp_index);
			if (new_address.Row() != test_address.Row() || CellStatus(temp_index) != "Empty") {
				moveRight = false;
				break;
			}
		}
	}

	// downwards

	bool moveDown = true;
	temp_index = index;
	for (int i = 1; i < s.Length; i++) {
		temp_index += 10;
		if (temp_index > 99 || CellStatus(temp_index) != "Empty") {
			moveDown = false;
			break;
		}
	}

	// to the left

	bool moveLeft = true;
	temp_index = index;
	for (int i = 1; i < s.Length; i++) {
		temp_index--;
		if (temp_index > -1) {
			GridAddress new_address(temp_index);
			if (new_address.Row() != test_address.Row() || CellStatus(temp_index) != "Empty") {
				moveLeft = false;
				break;
			}
		}
	}

	return moveUp || moveRight || moveDown || moveLeft;
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