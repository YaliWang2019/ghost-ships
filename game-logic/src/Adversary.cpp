#include <random>
#include "Adversary.hpp"

Adversary::Adversary()
{
	currently_on_target = false;
	next_target_set = false;
	reverse_count = 0;
}

Turn Adversary::NextTurn(Grid& target_board)
{
	if (next_target_set) {
		Turn next_turn(next_target, target_board);
		EvaluateTurn(next_turn, target_board);
		return next_turn;
	}
	else {
		Turn next_turn = Turn::AutoFire(target_board);		
		EvaluateTurn(next_turn, target_board);
		return next_turn;
	}
}

void Adversary::EvaluateTurn(Turn current_turn, Grid target_board)
{
	if (current_turn.IsHit()) {

		if (current_turn.IsShipSunk()) {
			currently_on_target = false;
			next_target_set = false;
			reverse_count = 0;
		}
		else {
			if (!currently_on_target) {

				// we have randomly chosen a place on the board and hit a ship - great!

				currently_on_target = true;
				ship_hit_start_index = current_turn.Target().GridIndex();
				last_hit_index = ship_hit_start_index;
				next_target_set = true;

				SetPossibleNextTarget(ship_hit_start_index, target_board);
			}
			else {
				// so we previously hit a ship, and have now hit it again -- need to
				// continue in this direction, or if we're at the end of the board, go
				// in the opposite direction past our first hit

				last_hit_index = current_turn.Target().GridIndex();
				int index_diff = current_turn.Target().GridIndex() - ship_hit_start_index;

				if (index_diff < -9) { // moving up
					next_target = current_turn.Target().GridIndex() - 10;
					if (next_target < 0 || target_board.CellFiredAt(next_target)) {
						// we hit a cell in row A and need to move down below our first hit
						next_target = ship_hit_start_index + 10;
						reverse_count++;
					}
				}
				else if (index_diff > -10 && index_diff < 0) { // moving to the left
					next_target = current_turn.Target().GridIndex() - 1;
					GridAddress next_add(next_target);
					if (next_target < 0 || next_add.Row() != current_turn.Target().Row()
						|| target_board.CellFiredAt(next_target)) {
						// we hit col1 and instead of continuing left need to move right of our first hit
						next_target = ship_hit_start_index + 1;
						reverse_count++;
					}
				}
				else if (index_diff < 10) { // moving to the right
					next_target = current_turn.Target().GridIndex() + 1;
					GridAddress next_add(next_target);
					if (next_target > 99 || next_add.Row() != current_turn.Target().Row()
						|| target_board.CellFiredAt(next_target)) {
						// we hit col10 and instead of continuing right need to move leftt of our first hit
						next_target = ship_hit_start_index - 1;
						reverse_count++;
					}
				}
				else { // moving down
					next_target = current_turn.Target().GridIndex() + 10;
					if (next_target > 99 || target_board.CellFiredAt(next_target)) {
						// we hit a cell in row J and need to move up above our first hit
						next_target = ship_hit_start_index - 10;
						reverse_count++;
					}
				}
			}
		}
	}
	else if (currently_on_target) {
		// we were previously hitting a ship but now missed; need to change directions
		if (last_hit_index == ship_hit_start_index) {
			SetPossibleNextTarget(ship_hit_start_index, target_board);
		}
		else if (reverse_count == 2) {
			// we previously had multiple hits in one direction, but now are 'lost'
			// example : two ships placed horizontally, one B2-B4, another C4-C7
			// we've hit B4 and C4 but have not sunk a vessel, but will find 'empty'
			// at A4 and D4 -- so we've already 'reversed' and checked both ends, time
			// to go back to first hit and re-initialize
			SetPossibleNextTarget(ship_hit_start_index, target_board);
		}
		else {

			// our previous hits followed a direction but now we missed; need to reverse
			int index_diff = current_turn.Target().GridIndex() - ship_hit_start_index;

			if (index_diff < -9) { // moving up
				next_target = ship_hit_start_index + 10;
				reverse_count++;
			}
			else if (index_diff > -10 && index_diff < 0) { // moving to the left
				next_target = ship_hit_start_index + 1;
				reverse_count++;
			}
			else if (index_diff < 10) { // moving to the right
				next_target = ship_hit_start_index - 1;
				reverse_count++;
			}
			else { // moving down
				next_target = ship_hit_start_index - 10;
				reverse_count++;
			}
		}
	}
}

Turn Adversary::NextTurn(Grid& target_board, int index) // for testing only, not gameplay
{
	Turn next_turn(index, target_board);
	EvaluateTurn(next_turn, target_board);
	return next_turn;
}

void Adversary::SetPossibleNextTarget(int target_index, Grid target_board)
{
	GridAddress target_address(target_index);

	std::random_device rd;
	std::default_random_engine re(rd());
	std::uniform_int_distribution<int> target_dist(0, 3);

	std::vector<int> possible_next_targets;

	// this will have some duplication of the ideas found in the placement code
	// likely could be generalized and placed into the grid or gridaddress --

	// cell above current target
	int test_index = target_index - 10;
	if (test_index > -1 && !target_board.CellFiredAt(test_index)) {
		possible_next_targets.push_back(test_index);
	}

	// cell to right of current target
	test_index = target_index + 1;
	if (test_index < 100 && !target_board.CellFiredAt(test_index)) {
		GridAddress test_add(test_index);
		if (test_add.Row() == target_address.Row()) {
			possible_next_targets.push_back(test_index);
		}
	}

	// cell below current target
	test_index = target_index + 10;
	if (test_index < 100 && !target_board.CellFiredAt(test_index)) {
		possible_next_targets.push_back(test_index);
	}

	// cell to left of current target
	test_index = target_index - 1;
	if (test_index > -1 && !target_board.CellFiredAt(test_index)) {
		GridAddress test_add(test_index);
		if (test_add.Row() == target_address.Row()) {
			possible_next_targets.push_back(test_index);
		}
	}

	int target_selection = 4;
	while (target_selection >= possible_next_targets.size()) {
		target_selection = target_dist(re);
	}

	next_target_set = true;
	next_target = possible_next_targets[target_selection];
}

