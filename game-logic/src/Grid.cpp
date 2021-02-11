#include <iostream>
#include <stdexcept>
#include "Grid.hpp"

std::map<int, std::string> Grid::status_string = {
	{0, "Empty"}, {1, "Ship"}, {2, "Hit"}, {3, "Miss"} };

std::string Grid::CellStatus(int index) {
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