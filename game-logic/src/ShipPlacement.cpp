#include "ShipPlacement.hpp"

ShipPlacement::ShipPlacement(int index)
{
	indices.push_back(index);
	start_ = GridAddress(index);
}