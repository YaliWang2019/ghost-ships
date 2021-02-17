#ifndef GHOST_SHIPS_ADVERSARY_H
#define GHOST_SHIPS_ADVERSARY_H

#include "Grid.hpp"

class Adversary {

public:

		Adversary();
		void NextTurn(Grid& target_board);

private:

	bool last_shot_hit;
	int last_hit_index;

};

#endif