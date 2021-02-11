
#include "ShipCollection.hpp";

ShipCollection::ShipCollection() {

	ships.push_back(Ship{ "Carrier", 5 });
	ships.push_back(Ship{ "Battleship", 4 });
	ships.push_back(Ship{ "Cruiser", 3 });
	ships.push_back(Ship{ "Submarine", 3 });
	ships.push_back(Ship{ "Destroyer", 2 });
}