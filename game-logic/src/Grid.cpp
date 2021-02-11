#include "Grid.hpp"

std::map<int, std::string> Grid::status_string = {
	{0, "Empty"}, {1, "Ship"}, {2, "Hit"}, {3, "Miss"} };

std::string Grid::CellStatus(int index) {
	return status_string[cell_status[index]];
}

bool Grid::SetShip(int index)
{
	if (cell_status[index] == 0) {
		cell_status[index] = 1;
		return true;
	}
	else return false;
}