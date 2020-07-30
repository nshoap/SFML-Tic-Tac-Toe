#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class Board : public sf::Drawable, public sf::Transformable
{
	friend class AIPlayer;
public:
	Board();
	void update_board(const sf::Vector2i& board_index, const char& owner);
	bool move_available(const sf::Vector2i& board_index);
	bool victory();
	char get_victor();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	char winner = ' ';
	std::vector<std::vector<char>> board = {
	{' ', ' ', ' '},
	{' ', ' ', ' '},
	{' ', ' ', ' '}
	};

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
};

#endif