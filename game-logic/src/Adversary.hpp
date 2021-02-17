#ifndef GHOST_SHIPS_ADVERSARY_H
#define GHOST_SHIPS_ADVERSARY_H

#include "Grid.hpp"
#include "Turn.hpp"

class Adversary {

public:

		Adversary();
		void NextTurn(Grid& target_board);
		void NextTurn(Grid& target_grid, int index); // for testing

private:

	bool last_shot_hit;
	bool currently_on_target;
	
	int ship_hit_start_index;
	bool next_target_set;
	int next_target;

	void EvaluateTurn(Turn current_turn, Grid target_board);
};

#endif