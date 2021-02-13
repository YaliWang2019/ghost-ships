#ifndef GHOST_SHIPS_SHIP_PLACEMENT_H
#define GHOST_SHIPS_SHIP_PLACEMENT_H

#include "GridAddress.hpp"
#include "ShipCollection.hpp"

class ShipPlacement {

public:

	ShipPlacement(int index);
	~ShipPlacement() {}

	GridAddress StartPoint() const { return start_; }
	GridAddress EndPoint() const { return end_; }

	int Length() const { return indices.size(); }
	int& operator[](int index) { return indices[index]; }

	void Add(int index) { indices.push_back(index); }
	void Finalize() { end_ = GridAddress(indices.back()); }

private:

	GridAddress start_;
	GridAddress end_;
	std::vector<int> indices;
};

#endif