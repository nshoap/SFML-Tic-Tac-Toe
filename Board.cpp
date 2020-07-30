#include "Board.h"

Board::Board()
{
	m_tileset.loadFromFile("Art\\Tilemap.png");
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(36);
}

bool Board::victory()
{
	std::vector<sf::Vector2i> winning_move;

	// Check for horizontal victory
	for (int y = 0; y != 3; ++y)
	{
		winning_move.clear();
		int count = 0;
		const char& control = board[y][0];
		winning_move.push_back(sf::Vector2i(0, y));
		if (control != ' ')
		{
			count = 1;
			for (int x = 1; x != 3; ++x)
			{
				if (board[y][x] == control)
				{
					winning_move.push_back(sf::Vector2i(x, y));
					++count;
				}
				else
					break;
			}
		}

		if (count == 3)
		{
			for (const auto& ref : winning_move)
			{
				std::cout << ref.x << ',' << ref.y << ' ';
			}
			std::cout << std::endl;
			winner = control;
			return true;
		}
	}

	winning_move.clear();

	// Check for vertical victory
	for (int x = 0; x != 3; ++x)
	{
		winning_move.clear();
		int count = 0;
		const char& control = board[0][x];
		winning_move.push_back(sf::Vector2i(x, 0));
		if (control != ' ')
		{
			count = 1;
			for (int y = 1; y != 3; ++y)
			{
				if (board[y][x] == control)
				{
					winning_move.push_back(sf::Vector2i(x, y));
					++count;
				}
				else
				{
					break;
				}
			}
		}
		if (count == 3)
		{
			for (const auto& ref : winning_move)
			{
				std::cout << ref.x << ',' << ref.y << ' ';
			}
			std::cout << std::endl;
			winner = control;
			return true;
		}
	}

	// Check for diagnol victory
	const char& control = board[1][1];
	if (control != ' ')
	{
		if ((board[0][0] == control && board[2][2] == control))
		{
			std::cout << "0,0" << " 1,1 " << " 2, 2" << std::endl;
			winner = control;
			return true;
		}

		if (board[0][2] == control && board[2][0] == control)
		{
			std::cout << "2,0" << " 1,1 " << " 0, 2" << std::endl;
			winner = control;
			return true;
		}
	}


	return false;
}

char Board::get_victor()
{
	return winner;
}

bool Board::move_available(const sf::Vector2i& board_index)
{
	return (board[board_index.y][board_index.x] == ' ');
}

void Board::update_board(const sf::Vector2i& pos, const char& owner)
{
	board[pos.y][pos.x] = owner;

	for (unsigned int y = 0; y != 3; ++y)
	{
		for (unsigned int x = 0; x != 3; ++x)
		{
			sf::Vertex* quad = &m_vertices[((y + x * 3) * 4)];
			quad[0].position = sf::Vector2f(x * 128, y * 128);
			quad[1].position = sf::Vector2f((x + 1) * 128, y * 128);
			quad[2].position = sf::Vector2f((x + 1) * 128, (y + 1) * 128);
			quad[3].position = sf::Vector2f(x * 128, (y + 1) * 128);

			int tile_number = -1;
			if (board[y][x] == 'X')
			{
				tile_number = 0;
			}
			else if (board[y][x] == 'O')
			{
				tile_number = 1;
			}

			quad[0].texCoords = sf::Vector2f(tile_number * 128, 0);
			quad[1].texCoords = sf::Vector2f((tile_number + 1) * 128, 0);
			quad[2].texCoords = sf::Vector2f((tile_number + 1) * 128,  128);
			quad[3].texCoords = sf::Vector2f(tile_number * 128,  128);
		}
	}
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &m_tileset;
	target.draw(m_vertices, states);
}