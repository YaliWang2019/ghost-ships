#ifndef GHOST_SHIPS_ADVERSARY_H
#define GHOST_SHIPS_ADVERSARY_H

#include "Grid.hpp"
#include "Turn.hpp"

class Adversary {

public:

		Adversary();
		Turn NextTurn(Grid& target_board);
		Turn NextTurn(Grid& target_grid, int index); // for testing

private:

	bool currently_on_target;	
	int ship_hit_start_index;
	int last_hit_index;
	int reverse_count;

	bool next_target_set;
	int next_target;

	void EvaluateTurn(Turn current_turn, Grid target_board);
	void SetPossibleNextTarget(int target_index, Grid target_board);
};

#endif