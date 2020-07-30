#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "Board.h"

class AIPlayer
{
public:
	AIPlayer(Board& b) : ref_board(b) {}
	bool can_move = false;
	bool move();
private:
	Board& ref_board;
};

#endif