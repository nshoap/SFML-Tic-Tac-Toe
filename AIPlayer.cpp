#include "AIPlayer.h"

bool AIPlayer::move()
{
	if (can_move)
	{
		std::cout << 'i' << std::endl;
		can_move = false;
		std::vector<sf::Vector2i> available_moves;
		sf::Vector2i best_move;

		// Get blank spots
		for (int y = 0; y != 3; ++y)
		{
			for (int x = 0; x != 3; ++x)
			{
				if (ref_board.board[y][x] == ' ')
				{
					available_moves.push_back(sf::Vector2i(x, y));
				}
			}
		}

		int best_potential = 0;
		for (auto it = available_moves.begin(); it != available_moves.end(); ++it)
		{
			int potential = 0;
			std::vector<sf::Vector2i> surrounding;
			auto& vec = *it;

			auto left = vec, right = vec;
			--left.x, ++right.x;

			auto up = vec, down = vec;
			--up.y, ++down.y;

			auto bottom_left = vec, bottom_right = vec;
			--bottom_left.x, ++bottom_left.y;
			++bottom_right.x, ++bottom_right.y;

			auto top_left = vec, top_right = vec;
			--top_left.x, --top_left.y;
			++top_right.x, --top_right.y;

			surrounding.push_back(left);
			surrounding.push_back(right);
			surrounding.push_back(up);
			surrounding.push_back(down);
			surrounding.push_back(top_left);
			surrounding.push_back(top_right);
			surrounding.push_back(bottom_left);
			surrounding.push_back(bottom_right);

			for (auto s = surrounding.begin(); s != surrounding.end(); ++s)
			{
				auto& deref = *s;
				if ((deref.x > -1 && deref.x < 3) && (deref.y > -1 && deref.y < 3))
				{
					if (ref_board.board[deref.y][deref.x] == 'O')
					{
						++potential;
					}
				}
			}

			if (potential > best_potential)
			{
				best_move = vec;
				best_potential = potential;
			}

		}

		if (best_potential == 0)
		{
			if (available_moves.size() > 0)
			{
				best_move = available_moves.at(0);
			}
		}

		std::cout << "best move: " << best_move.x << ',' << best_move.y << std::endl;
		ref_board.update_board(best_move, 'O');

		return true;
	}

	return true;
}