#include <random>
#include "Adversary.hpp"

Adversary::Adversary()
{
	last_shot_hit = false;
	currently_on_target = false;
	next_target_set = false;
}

void Adversary::NextTurn(Grid& target_board)
{
	if (next_target_set) {
		Turn next_turn(next_target, target_board);
	}
	else {
		Turn next_turn = Turn::AutoFire(target_board);		
	}
}

void Adversary::EvaluateTurn(Turn current_turn, Grid target_board)
{

	if (current_turn.IsHit()) {

		if (current_turn.IsShipSunk()) {
			currently_on_target = false;
			next_target_set = false;
		}
		else {
			if (!last_shot_hit) {
				last_shot_hit = true;
				ship_hit_start_index = current_turn.Target().GridIndex();


				std::random_device rd;
				std::default_random_engine re(rd());
				std::uniform_int_distribution<int> placement_dist(0, 3);


			}
			else {

			}
		}
	}
}

void Adversary::NextTurn(Grid& target_board, int index)
{

	// defined for testing w/ pre-determined targets

	// if last shot was hit, need to try 'next' to it in one direction until another hit is found



	// need to end this cycle once turn.sunk returns true
}